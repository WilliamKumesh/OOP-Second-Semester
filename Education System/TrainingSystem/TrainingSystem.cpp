#include "TrainingSystem.h"

void UniversitySystem::add_course(Course course)
{
	//if(course_members.contains(course))
	//{
	//	throw std::invalid_argument("Course already exist");
	//}
	course_members.emplace(std::move(course), CourseMembers());
}

void UniversitySystem::add_student(Student student)
{
	//if (student_courses.contains(student))
	//{
	//	throw std::invalid_argument("Student already exist");
	//}
	student_courses.emplace(std::move(student), std::unordered_set<CourseId, HashId<CourseId>>());
}

void UniversitySystem::add_teacher(Teacher teacher)
{
	//if (teacher_courses.contains(teacher))
	//{
	//	throw std::invalid_argument("Teacher already exist");
	//}
	teacher_courses.emplace(std::move(teacher), std::unordered_set<CourseId, HashId<CourseId>>());
}

void UniversitySystem::add_course_to_student(const Course& course, const Student& student)
{
	const auto student_it = student_courses.find(student);

	if (student_it == student_courses.end())
	{
		throw std::invalid_argument("No such student");
	}

	student_it->second.emplace(course.get_id());
}

void UniversitySystem::add_course_to_teacher(const Course& course, const Teacher& teacher)
{
	const auto teacher_it = teacher_courses.find(teacher);

	if (teacher_it == teacher_courses.end())
	{
		throw std::invalid_argument("No such teacher");
	}

	teacher_it->second.emplace(course.get_id());
}

void UniversitySystem::add_student_to_course(const Student& student, const Course& course)
{
	const auto course_it = course_members.find(course);

	if (course_it == course_members.end())
	{
		throw std::invalid_argument("No such course");
	}

	course_it->second.add_student(student.get_id());
}

void UniversitySystem::add_teacher_to_course(const Teacher& teacher, const Course& course)
{
	const auto course_it = course_members.find(course);

	if (course_it == course_members.end())
	{
		throw std::invalid_argument("No such course");
	}

	course_it->second.add_teacher(teacher.get_id());
}

bool UniversitySystem::erase_course(const Course& course) noexcept
{
	if (!course_members.contains(course))
	{
		return false;
	}
	course_members.erase(course);
	return true;
}

bool UniversitySystem::erase_student(const Student& student) noexcept
{
	if (!student_courses.contains(student))
	{
		return false;
	}
	student_courses.erase(student);
	return true;
}

bool UniversitySystem::erase_teacher(const Teacher& teacher) noexcept
{
	if (!teacher_courses.contains(teacher))
	{
		return false;
	}
	teacher_courses.erase(teacher);
	return true;
}

std::vector<Teacher> UniversitySystem::get_course_teachers(const Course& course) const noexcept
{
	auto arr = teacher_courses | std::views::keys | std::views::filter([&](const Teacher& key) {return
		course_members.at(course).get_teachers().contains(key.get_id()); });

	return { arr.begin(), arr.end() };
}

std::vector<Student> UniversitySystem::get_course_students(const Course& course) const noexcept
{
	auto arr = student_courses | std::views::keys | std::views::filter([&](const Student& key) {return
		course_members.at(course).get_students().contains(key.get_id()); });

	return { arr.begin(), arr.end() };
}

std::vector<Course> UniversitySystem::get_student_courses(const Student& student) const noexcept
{
	auto arr = course_members | std::views::keys | std::views::filter([&](const Course& key) {return
		student_courses.at(student).contains(key.get_id()); });

	return { arr.begin(), arr.end() };
}

std::vector<Course> UniversitySystem::get_teacher_courses(const Teacher& teacher) const noexcept
{
	auto arr = course_members | std::views::keys | std::views::filter([&](const Course& key) {return
		teacher_courses.at(teacher).contains(key.get_id()); });

	return { arr.begin(), arr.end() };
}

std::vector<Course> UniversitySystem::get_all_courses() const noexcept
{
	auto arr = course_members | std::views::keys;

	return { arr.begin(), arr.end() };
}

std::vector<Student> UniversitySystem::get_all_students() const noexcept
{
	auto arr = student_courses | std::views::keys;

	return { arr.begin(), arr.end() };
}

std::vector<Teacher> UniversitySystem::get_all_teachers() const noexcept
{
	auto arr = teacher_courses | std::views::keys;

	return { arr.begin(), arr.end() };
}
//void UniversitySystem::add_course_with_teachers_and_students(Course course, std::unordered_set<StudentId, HashId<StudentId>> students, std::unordered_set<TeacherId, HashId<TeacherId>> teachers)
//{
//	course_members.insert(std::make_pair(std::move(course), CourseMembers(std::move(students), std::move(teachers))));
//}
//
//void UniversitySystem::add_student_with_courses(Student student, std::unordered_set<CourseId, HashId<CourseId>> courses)
//{
//	student_courses.insert(std::make_pair(std::move(student), std::move(courses)));
//}
//
//void UniversitySystem::add_teacher_with_courses(Teacher teacher, std::unordered_set<CourseId, HashId<CourseId>> courses)
//{
//	teacher_courses.insert(std::make_pair(std::move(teacher), std::move(courses)));
//}