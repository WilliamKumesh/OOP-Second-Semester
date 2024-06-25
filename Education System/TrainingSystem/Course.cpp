#include "Course.h"
#include <stdexcept>

Course::Course(std::string name, CourseId id) : name(std::move(name)), id(std::move(id))
{
	if(this->name.empty())
	{
		throw std::invalid_argument("Empty Course name");
	}
}

const std::string& Course::get_name() const noexcept
{
	return name;
}

const CourseId& Course::get_id() const
{
	return id;
}
