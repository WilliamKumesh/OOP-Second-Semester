#pragma once
#include "TypingClasses.h"
#include <ranges>
#include <functional>

class UniversitySystemRead
{
protected:
	~UniversitySystemRead() = default;
public:
	virtual [[nodiscard]] std::vector<Course> get_teacher_courses(const Teacher& teacher) const = 0;
	virtual [[nodiscard]] std::vector<Course> get_student_courses(const Student& student) const = 0;
	virtual [[nodiscard]] std::vector<Student> get_course_students(const Course& course) const = 0;
	virtual [[nodiscard]] std::vector<Teacher> get_course_teachers(const Course& course) const = 0;
};
