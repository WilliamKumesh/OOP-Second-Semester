#pragma once
#include <cstddef>
#include <algorithm>
#include <numeric>

namespace Variant_
{
	template<typename T, typename... Args>
	struct max_type_size
	{
		static const size_t value = sizeof(T) > max_type_size<Args...>::value ? sizeof(T) : max_type_size<Args...>::value;
	};

	template<typename T>
	struct max_type_size<T>
	{
		static const size_t value = sizeof(T);
	};

	template<size_t N, class T, class... Types>
	struct get_index_by_type
	{
		static constexpr size_t value = -1;
	};

	template<size_t N, class T, class Head, class... Tail>
	struct get_index_by_type<N, T, Head, Tail...>
	{
		static const size_t value = std::is_same_v<T, Head> ? N :
			get_index_by_type<N + 1, T, Tail...>::value;
	};

	template <size_t index, typename T, typename... Args>
	struct get_type_by_index
	{
		using type = typename get_type_by_index<index - 1, Args...>::type;
	};

	template <typename T, typename... Args>
	struct get_type_by_index<0, T, Args...>
	{
		using type = T;
	};

	template<class Head>
	void destroy(std::byte(&memory)[], size_t index)
	{
		static_cast<Head*>(static_cast<void*>(memory))->~Head();
	}

	template<class Head, class... Tail>
	requires (sizeof...(Tail) > 0)
	void destroy(std::byte(&memory)[], size_t index)
	{
		if (index > 0)
		{
			return destroy<Tail...>(memory, index - 1);
		}
		static_cast<Head*>(static_cast<void*>(memory))->~Head();
	}

	template<class Head>
	void reset(size_t index, const std::byte(&right_obj_memory)[], std::byte(&current_memory)[])
	{
		destroy<Head>(current_memory, index);
		new (current_memory) Head(*static_cast<const Head*>(static_cast<const void*>(right_obj_memory)));
	}

	template<class Head, class... Tail>
	requires (sizeof...(Tail) > 0)
	void reset(size_t index, const std::byte(&right_obj_memory)[], std::byte(&current_memory)[])
	{
		if (index > 0)
		{
			return reset<Tail...>(index - 1, right_obj_memory, current_memory);
		}
		destroy<Head, Tail...>(current_memory, index);
		new (current_memory) Head(*static_cast<const Head*>(static_cast<const void*>(right_obj_memory)));
	}

	template<class Head>
	std::partial_ordering compare(size_t index, const std::byte(&right_obj_memory)[], const std::byte(&current_memory)[])
	{
		return static_cast<std::partial_ordering>(std::compare_three_way{}(
			*static_cast<const Head*>(static_cast<const void*>(current_memory)),
			*static_cast<const Head*>(static_cast<const void*>(right_obj_memory))));
	}

	template<class Head, class... Tail>
	requires (sizeof...(Tail) > 0)
	std::partial_ordering compare(size_t index, const std::byte(&right_obj_memory)[], const std::byte(&current_memory)[])
	{
		if (index > 0)
		{
			return compare<Tail...>(index - 1, right_obj_memory, current_memory);
		}
		return static_cast<std::partial_ordering>(std::compare_three_way{}(
			*static_cast<const Head*>(static_cast<const void*>(current_memory)),
			*static_cast<const Head*>(static_cast<const void*>(right_obj_memory))));
	}

	template<class Head>
	void reset_move(size_t index, std::byte* right_obj_memory, std::byte(&current_memory)[])
	{
		destroy<Head>(current_memory, index);
		new (current_memory) Head(std::move(*static_cast<Head*>(static_cast<void*>(right_obj_memory))));
	}

	template<class Head, class... Tail>
	requires (sizeof...(Tail) > 0)
	void reset_move(size_t index, std::byte* right_obj_memory, std::byte(&current_memory)[])
	{
		if (index > 0)
		{
			return reset_move<Tail...>(index - 1, right_obj_memory, current_memory);
		}
		destroy<Head, Tail...>(current_memory, index);
		new (current_memory) Head(std::move(*static_cast<Head*>(static_cast<void*>(right_obj_memory))));
	}
}

template<class ...Types>
class Variant final
{
	static_assert(sizeof...(Types) > 0);
	std::byte memory[Variant_::max_type_size<Types...>::value]{};
	size_t current = static_cast<size_t>(-1);

public:
	constexpr Variant() noexcept = default;

	constexpr Variant(const Variant& other) noexcept
	{
		current = other.current;
		Variant_::reset<Types...>(current, other.memory, memory);
	}

	constexpr Variant(Variant&& other) noexcept
	{
		current = other.current;
		Variant_::reset_move<Types...>(current, std::forward<std::byte*>(other.memory), memory);
		other.current = std::numeric_limits<size_t>::max();
	}

	template<class T>
	requires (!std::is_same_v<std::remove_cvref_t<T>, Variant>)
	constexpr explicit Variant(T&& value) noexcept
	{
		current = Variant_::get_index_by_type<0, T, Types...>::value;
		new (memory) std::remove_cvref_t<T>(std::forward<T>(value));
	}

	template<class T>
	Variant& operator=(T&& value)
	{
		Variant_::destroy<Types...>(memory, current);
		current = Variant_::get_index_by_type<0, T, Types...>::value;
		new (memory) T(std::forward<T>(value));

		return *this;
	}

	constexpr Variant& operator=(const Variant& rhs)
	{
		if(this == &rhs)
		{
			return *this;
		}

		current = rhs.current;
		reset<Types...>(current, rhs.memory, memory);

		return *this;
	}

	[[nodiscard]] constexpr size_t index() const noexcept
	{
		return current;
	}

	[[nodiscard]] constexpr bool valueless_by_exception() const noexcept
	{
		return current != std::numeric_limits<size_t>::max();
	}

	template<class T>
	[[nodiscard]] constexpr  bool holds_alternative() const
	{
		return Variant_::get_index_by_type<0, T, Types...>::value == current;
	}

	template<typename T>
	[[nodiscard]]const T& get() const
	{
		if(current != Variant_::get_index_by_type<0,T,Types...>::value)
		{
			throw std::invalid_argument("No data by type");
		}
		return *static_cast<const T*>(static_cast<const void*>(memory));
	}

	template<std::size_t Index>
	[[nodiscard]] typename Variant_::get_type_by_index<Index, Types...>::type get() const
	{
		if(Index != current)
		{
			throw std::invalid_argument("Index out of range");
		}
		return *static_cast<const typename Variant_::get_type_by_index<Index, Types...>::type*>(static_cast<const void*>(memory));
	}

	template<typename T>
	[[nodiscard]] constexpr T* get_if() noexcept
	{
		if(current != Variant_::get_index_by_type<0, T, Types...>::value)
		{
			return nullptr;
		}
		return static_cast<T*>(static_cast<void*>(memory));
	}

	template<std::size_t Index>
	[[nodiscard]]constexpr typename Variant_::get_type_by_index<Index, Types...>::type* get_if() noexcept
	{
		if(Index != current)
		{
			return nullptr;
		}
		return static_cast<typename Variant_::get_type_by_index<Index, Types...>::type*>(static_cast<void*>(memory));
	}

	template <class T, class... Args>
	requires(Variant_::get_index_by_type<0, T, Types...>::value <= sizeof...(Types) - 1)
	constexpr void emplace(Args&& ...args)
	{
		Variant_::destroy<Types...>(memory, current);
		current = Variant_::get_index_by_type<0, T, Types...>::value;
		new (memory) T(std::forward<Args>(args)...);
	}

	[[nodiscard]]bool operator==(const Variant& rhs) const
	{
		if (current == rhs.current)
		{
			return Variant_::compare<Types...>(current, rhs.memory, memory) == nullptr;
		}
		return current == rhs.current;
	}

	std::partial_ordering operator<=>(const Variant& rhs) const
	{
		if (current == rhs.current)
		{
			return Variant_::compare<Types...>(current, rhs.memory, memory);
		}
		return static_cast<std::partial_ordering>(current <=> rhs.current);
	}

	friend void swap(Variant& lhs, Variant& rhs) noexcept
	{
		std::swap(lhs.memory, rhs.memory);
		std::swap(lhs.current, rhs.current);
	}

	~Variant()
	{
		Variant_::destroy<Types...>(memory, current);
	}
};