#include "Teacher.h"

unsigned short Teacher::get_experience() const noexcept
{
	return experience;
}

const std::string& Teacher::get_name() const noexcept
{
	return name;
}

const TeacherId& Teacher::get_id() const
{
	return id;
}
