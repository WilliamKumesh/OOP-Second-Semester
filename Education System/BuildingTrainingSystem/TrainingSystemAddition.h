#pragma once
#include "MemberDto.h"
#include "TrainingSystem.h"


class TrainingSystemAddition final
{
	static void insert_member(const MemberDto& dto, UniversitySystem& university, const std::string& naming_id);
	static void insert_course(const MemberDto& dto, UniversitySystem& university);
public:
	TrainingSystemAddition() = delete;
	static void complement_training_system(std::istream& input_stream, UniversitySystem& university);
};