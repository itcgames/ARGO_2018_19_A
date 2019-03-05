#include "stdafx.h"
#include "Random.h"

std::random_device app::util::Random::s_randomDevice = std::random_device();
std::default_random_engine app::util::Random::s_randomEngine = std::default_random_engine(app::util::Random::s_randomDevice());
std::uniform_int_distribution<std::int32_t> app::util::Random::s_intDistribution = std::uniform_int_distribution<std::int32_t>();
std::uniform_real_distribution<float> app::util::Random::s_realDistribution = std::uniform_real_distribution<float>();

std::int32_t app::util::Random::gen(std::int32_t const & start, std::int32_t const & end)
{
	if (s_intDistribution.min() != start || s_intDistribution.max() != end)
	{
		s_intDistribution = std::uniform_int_distribution<std::int32_t>(start, end);
	}
	return s_intDistribution(s_randomEngine);
}

float app::util::Random::gen(float const & start, float const & end)
{
	if (s_realDistribution.min() != start || s_realDistribution.max() != end)
	{
		s_realDistribution = std::uniform_real_distribution<float>(start, end);
	}
	return s_realDistribution(s_randomEngine);
}
