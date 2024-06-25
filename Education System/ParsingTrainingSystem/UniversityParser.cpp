#include "UniversityParser.h"
#include <sstream>

[[nodiscard]] MemberDto UniversityParser::parsing_member_dto(const std::string& input_str)
{
	std::string id{};
	std::string member_name{};
	std::vector<std::string> attributes{};

	std::stringstream str_stream(input_str);

	str_stream >> id;
	str_stream >> member_name;

	std::string temp_str;
	while(str_stream >> temp_str)
	{
		attributes.push_back(temp_str);
	}

	return {id, member_name, attributes};
}
