#pragma once
#include <stdexcept>
#include <string>

class StudentId final
{
	std::string id;
public:
	StudentId(std::string id) : id(std::move(id))
	{}

	const std::string& get_id() const noexcept
	{
		return id;
	}

	auto operator<=>(const StudentId& student_id) const = default;
};

class Student final
{
	std::string name;
	StudentId id;
public:
	Student(std::string name, StudentId id): name(std::move(name)), id(std::move(id))
	{
		if (this->name.empty())
		{
			throw std::invalid_argument("Empty Student name");
		}
	}

	bool operator==(const Student& right) const
	{
		return id == right.get_id();
	}

	[[nodiscard]] const std::string& get_name() const noexcept;

	const StudentId& get_id() const;
};