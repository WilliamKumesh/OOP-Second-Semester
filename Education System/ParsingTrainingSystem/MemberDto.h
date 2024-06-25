#pragma once
#include <string>
#include <utility>
#include <vector>

class MemberDto final
{
	std::string id;
	std::string member_name;
	std::vector<std::string> attributes;
public:
	MemberDto(std::string id, std::string member_name, std::vector<std::string> attributes) :
	id(std::move(id)), member_name(std::move(member_name)), attributes(std::move(attributes)){}

	[[nodiscard]]const std::string& get_member_id() const noexcept
	{
		return id;
	}

	[[nodiscard]]const std::vector<std::string>& get_attributes() const noexcept
	{
		return attributes;
	}

	[[nodiscard]] const std::string& get_member_name() const noexcept
	{
		return member_name;
	}
};
