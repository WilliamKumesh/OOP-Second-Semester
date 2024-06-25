#pragma once
#include <string>
#include "MemberDto.h"

class UniversityParser final
{
public:
	UniversityParser() = delete;

	[[nodiscard]] static MemberDto parsing_member_dto(const std::string& input_str);
};