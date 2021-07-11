#pragma once
#include <random>

namespace Random
{
	[[nodiscard("Let's use the random number we generated")]]
	int FrameworkAPI RandomInt(int min, int max);
	[[nodiscard("Let's use the random number we generated")]]
	float FrameworkAPI RandomFloat(float min = 0.0f, float max = 1.0f);
};

