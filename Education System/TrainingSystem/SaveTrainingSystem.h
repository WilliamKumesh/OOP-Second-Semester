#pragma once
#include "TrainingSystem.h"

class SaveUniversity
{
public:
	SaveUniversity() = delete;

	static void save_to_ostream(std::ostream& out, const UniversitySystem& system);
};