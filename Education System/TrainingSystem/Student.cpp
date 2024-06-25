#include "Student.h"

const std::string& Student::get_name() const noexcept
{
	return name;
}

const StudentId& Student::get_id() const
{
	return id;
}
