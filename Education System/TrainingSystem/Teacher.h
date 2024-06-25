#pragma once
#include <stdexcept>
#include <string>
#include <utility>

class TeacherId final
{
	std::string id;
public:
	TeacherId(std::string id) : id(std::move(id))
	{}

	const std::string& get_id() const noexcept
	{
		return id;
	}

	auto operator<=>(const TeacherId& teacher_id) const = default;
};

class Teacher final
{
	std::string name;
	TeacherId id;
	unsigned short int experience{};
public:
	Teacher(std::string name, const unsigned short experience, TeacherId id): name(std::move(name)),
	id(std::move(id)), experience(experience)
	{
		if (this->name.empty())
		{
			throw std::invalid_argument("Empty Teacher name");
		}
	}

	bool operator==(const Teacher& right) const
	{
		return id == right.get_id();
	}

	[[nodiscard]] unsigned short int get_experience() const noexcept;

	[[nodiscard]] const std::string& get_name() const noexcept;

	const TeacherId& get_id() const;
};