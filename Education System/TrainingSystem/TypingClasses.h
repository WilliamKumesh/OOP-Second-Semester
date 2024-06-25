#pragma once
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include <unordered_map>
#include <unordered_set>
#include "Course.h"

template<class Member>
class HashMember final
{
public:
	size_t operator()(const Member& member) const noexcept
	{
		return std::hash<std::string>{}(member.get_id().get_id());
	}
};

template<class IdType>
class HashId final
{
public:
	size_t operator()(const IdType& id) const noexcept
	{
		return std::hash<std::string>{}(id.get_id());
	}
};

class CourseMembers final
{
	std::unordered_set<TeacherId, HashId<TeacherId>> teachers;
	std::unordered_set<StudentId, HashId<StudentId>> students;
public:
	CourseMembers() = default;

	CourseMembers(std::unordered_set<StudentId, HashId<StudentId>> students, std::unordered_set<TeacherId, HashId<TeacherId>> teachers) :
	teachers(std::move(teachers)), students(std::move(students))
	{}

	[[nodiscard]] const std::unordered_set<StudentId, HashId<StudentId>>& get_students() const
	{
		return students;
	}

	[[nodiscard]] const std::unordered_set<TeacherId, HashId<TeacherId>>& get_teachers() const
	{
		return teachers;
	}

	void add_teacher(TeacherId teacher_id)
	{
		teachers.emplace(std::move(teacher_id));
	}

	void add_student(StudentId student_id)
	{
		students.emplace(std::move(student_id));
	}
};