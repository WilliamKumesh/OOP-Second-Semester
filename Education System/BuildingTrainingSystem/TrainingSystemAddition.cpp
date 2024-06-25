#include "TrainingSystemAddition.h"
#include "CourseCreator.h"
#include "MemberCreator.h"
#include "UniversityParser.h"

namespace
{
	const std::string teacher_naming_id = "teacher";
	const std::string student_naming_id = "student";
	const std::string course_naming_id = "course";

	const std::string invalid_name_to_insert = "example";
}

void TrainingSystemAddition::insert_course(const MemberDto& dto, UniversitySystem& university)
{
	const Course course(dto.get_member_name(), CourseId(dto.get_member_id()));
	university.add_course(course);

	std::stringstream ss(*dto.get_attributes().begin());
	std::size_t teacher_num;
	ss >> teacher_num;

	size_t i = 0;

	for (auto it = dto.get_attributes().begin(); it != dto.get_attributes().end(); ++it)
	{
		if(i < teacher_num)
		{
			i++;
			university.add_teacher_to_course(Teacher(invalid_name_to_insert, 0, TeacherId(*it)), course);
			continue;
		}
		university.add_student_to_course(Student(invalid_name_to_insert, StudentId(*it)), course);
	}
}

void TrainingSystemAddition::insert_member(const MemberDto& dto, UniversitySystem& university, const std::string& naming_id)
{
	Student student(invalid_name_to_insert, invalid_name_to_insert);
	Teacher teacher(invalid_name_to_insert, 0, invalid_name_to_insert);

	if (naming_id == student_naming_id)
	{
		student = Student(dto.get_member_name(), StudentId(dto.get_member_id()));
		university.add_student(student);
	}

	if (naming_id == teacher_naming_id)
	{
		const unsigned short exp = static_cast<unsigned short>(std::stoi(*dto.get_attributes().begin()));
		teacher = Teacher(dto.get_member_name(), exp, TeacherId(dto.get_member_id()));
		university.add_teacher(teacher);
	}

	for (auto it = dto.get_attributes().begin(); it != dto.get_attributes().end(); ++it)
	{
		if (naming_id == student_naming_id)
		{
			university.add_course_to_student(Course(invalid_name_to_insert, *it), student);
		}

		if (naming_id == teacher_naming_id && it != dto.get_attributes().begin())
		{
			university.add_course_to_teacher(Course(invalid_name_to_insert, *it), teacher);
		}
	}
}

void TrainingSystemAddition::complement_training_system(std::istream& input_stream, UniversitySystem& university)
{
	std::string stream_string;

	while (std::getline(input_stream, stream_string, '\n'))
	{
		const auto pos = stream_string.find(' ');
		std::string naming_id = stream_string.substr(0, pos);
		stream_string.erase(0, pos + 1);

		if (naming_id == course_naming_id)
		{
			insert_course(UniversityParser::parsing_member_dto(stream_string), university);
		}

		if (naming_id == student_naming_id || naming_id == teacher_naming_id)
		{
			insert_member(UniversityParser::parsing_member_dto(stream_string), university, naming_id);
		}
	}
}
