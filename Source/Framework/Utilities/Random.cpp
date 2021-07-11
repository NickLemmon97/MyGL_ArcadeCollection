#include "FrameworkPCH.h"
#include "Random.h"

static std::mt19937 _sMersenneTwister{ std::random_device{}() };


int Random::RandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(_sMersenneTwister);
}

float Random::RandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(_sMersenneTwister);
}
