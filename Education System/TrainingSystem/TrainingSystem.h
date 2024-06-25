#pragma once
#include "ReadTrainingSystem.h"
#include "WriteTrainingSystem.h"
#include <ranges>
#include "Course.h"
#include "Teacher.h"
#include "Student.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>  

class UniversitySystem final : public UniversitySystemWrite, public UniversitySystemRead
{
	std::unordered_map<Teacher, std::unordered_set<CourseId, HashId<CourseId>>, HashMember<Teacher>> teacher_courses;
	std::unordered_map<Student, std::unordered_set<CourseId, HashId<CourseId>>, HashMember<Student>> student_courses;
	std::unordered_map<Course, CourseMembers, HashMember<Course>> course_members;
public:
	UniversitySystem() = default;
	
	//void add_course_with_teachers_and_students(Course course, std::unordered_set<StudentId, HashId<StudentId>> students, std::unordered_set<TeacherId, HashId<TeacherId>> teachers) override;
	//void add_student_with_courses(Student student, std::unordered_set<CourseId, HashId<CourseId>> courses) override;
	//void add_teacher_with_courses(Teacher teacher, std::unordered_set<CourseId, HashId<CourseId>> courses) override;

	void add_course(Course course) override;
	void add_student(Student student) override;
	void add_teacher(Teacher teacher) override;

	void add_course_to_student(const Course& course, const Student& student) override;
	void add_course_to_teacher(const Course& course, const Teacher& teacher) override;
	void add_student_to_course(const Student& student, const Course& course) override;
	void add_teacher_to_course(const Teacher& teacher, const Course& course) override;

	[[nodiscard]] bool erase_course(const Course& course) noexcept override;
	[[nodiscard]] bool erase_student(const Student& student) noexcept override;
	[[nodiscard]] bool erase_teacher(const Teacher& teacher) noexcept override;

	[[nodiscard]] std::vector<Teacher> get_course_teachers(const Course& course) const noexcept override;
	[[nodiscard]] std::vector<Student> get_course_students(const Course& course) const noexcept override;
	[[nodiscard]] std::vector<Course> get_student_courses(const Student& student) const noexcept override;
	[[nodiscard]] std::vector<Course> get_teacher_courses(const Teacher& teacher) const noexcept override;

	template<class IdType>
	[[nodiscard]] IdType generate_id()
	{
		if(std::is_same_v<IdType, CourseId> || std::is_same_v<IdType, StudentId> || std::is_same_v<IdType, TeacherId>)
		{
			const boost::uuids::uuid uuid = boost::uuids::random_generator()();
			return IdType(boost::lexical_cast<std::string>(uuid));
		}

		throw std::invalid_argument("No such IdType");
	}

	[[nodiscard]] std::vector<Student> get_all_students() const noexcept;
	[[nodiscard]] std::vector<Teacher> get_all_teachers() const noexcept;
	[[nodiscard]] std::vector<Course> get_all_courses() const noexcept;

	//[[nodiscard]] auto teacher_iterator_begin() const
	//{
	//	return teacher_courses.cbegin();
	//}
	//[[nodiscard]] auto teacher_iterator_end() const
	//{
	//	return teacher_courses.cend();
	//}
	//[[nodiscard]] auto student_iterator_begin() const
	//{
	//	return student_courses.cbegin();
	//}
	//[[nodiscard]] auto student_iterator_end() const
	//{
	//	return student_courses.cend();
	//}
	//[[nodiscard]] auto course_iterator_begin() const
	//{
	//	return course_members.cbegin();
	//}
	//[[nodiscard]] auto course_iterator_end() const
	//{
	//	return course_members.cend();
	//}
};