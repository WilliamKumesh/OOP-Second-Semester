#include "SaveTrainingSystem.h"
#include <ostream>

namespace 
{
	const std::string teacher_naming_id = "teacher";
	const std::string student_naming_id = "student";
	const std::string course_naming_id = "course";
}

void SaveUniversity::save_to_ostream(std::ostream& out, const UniversitySystem& system)
{
	for (const auto& course : system.get_all_courses())
	{
		out << course_naming_id << ' ';
		out << course.get_id().get_id() << ' ' << course.get_name() << ' ';

		auto teachers = system.get_course_teachers(course);
		out << teachers.size() << ' ';

		for (const auto& teacher : teachers)
		{
			out << teacher.get_id().get_id() << ' ';
		}

		auto students = system.get_course_students(course);

		for (const auto& student : students)
		{
			out << student.get_id().get_id() << ' ';
		}
		out << '\n';
	}

	for (const auto& student : system.get_all_students())
	{
		out << student_naming_id << ' ';
		out << student.get_id().get_id() << ' ' << student.get_name() << ' ';

		auto courses = system.get_student_courses(student);

		for (const auto& course : courses)
		{
			out << course.get_id().get_id() << ' ';
		}
		out << '\n';
	}

	for (const auto& teacher : system.get_all_teachers())
	{
		out << teacher_naming_id << ' ';
		out << teacher.get_id().get_id() << ' ' << teacher.get_name() << ' ' << teacher.get_experience() << ' ';

		auto courses = system.get_teacher_courses(teacher);

		for (const auto& course : courses)
		{
			out << course.get_id().get_id() << ' ';
		}
		out << '\n';
	}
}
