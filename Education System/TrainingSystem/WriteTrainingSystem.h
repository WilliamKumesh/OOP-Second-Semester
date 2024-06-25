#pragma once
#include "TypingClasses.h"

class UniversitySystemWrite
{
protected:
	~UniversitySystemWrite() = default;
public:

	virtual void add_student(Student student) = 0;
	virtual void add_teacher(Teacher teacher) = 0;
	virtual void add_course(Course course) = 0;

	virtual void add_student_to_course(const Student& student, const Course& course) = 0;
	virtual void add_teacher_to_course(const Teacher& teacher, const Course& course) = 0;
	virtual void add_course_to_student(const Course& course, const Student& student) = 0;
	virtual void add_course_to_teacher(const Course& course, const Teacher& teacher) = 0;

	virtual [[nodiscard]] bool erase_student(const Student& student) = 0;
	virtual [[nodiscard]] bool erase_teacher(const Teacher& teacher) = 0;
	virtual [[nodiscard]] bool erase_course(const Course& course) = 0;
	//virtual void add_student_with_courses(Student student, std::unordered_set<CourseId, HashId<CourseId>> courses) = 0;
	//virtual void add_teacher_with_courses(Teacher teacher, std::unordered_set<CourseId, HashId<CourseId>> courses) = 0;
	//virtual void add_course_with_teachers_and_students(Course course, std::unordered_set<StudentId, HashId<StudentId>> students, std::unordered_set<TeacherId, HashId<TeacherId>> teachers) = 0;
};
