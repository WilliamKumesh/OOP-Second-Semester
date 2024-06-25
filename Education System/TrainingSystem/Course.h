#pragma once
#include <string>
#include "Teacher.h"

class CourseId final
{
	std::string id;
public:
	CourseId(std::string id) : id(std::move(id))
	{}

	const std::string& get_id() const noexcept
	{
		return id;
	}

	auto operator<=>(const CourseId& course_id) const = default;
};

class Course final
{
	std::string name;
	CourseId id;
public:
	Course(std::string name, CourseId id);

	bool operator==(const Course& right) const
	{
		return id == right.get_id();
	}

	[[nodiscard]] const std::string& get_name() const noexcept;

	const CourseId& get_id() const;
};