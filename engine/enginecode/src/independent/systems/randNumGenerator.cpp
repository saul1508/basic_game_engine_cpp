/** \file randNumGenerator.cpp */

#include "engine_pch.h"
#include "systems/randNumGenerator.h"
#include <chrono>

namespace Engine {

	std::shared_ptr<std::mt19937> RandNumGenerator::s_generator = nullptr; 
	std::uniform_int_distribution<int32_t> RandNumGenerator::s_uniformInt = std::uniform_int_distribution<int32_t>(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
	std::uniform_real_distribution<float> RandNumGenerator::s_uniformFloat = std::uniform_real_distribution<float>(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
	float RandNumGenerator::s_intRange = static_cast<float>(std::numeric_limits<int32_t>::max() - (float)std::numeric_limits<int32_t>::min());
	float RandNumGenerator::s_floatRange = std::numeric_limits<float>::max() - std::numeric_limits<float>::min();
	
	void Engine::RandNumGenerator::start(SystemSignal init, ...)
	{
		auto now = std::chrono::high_resolution_clock::now();
		s_generator.reset(new std::mt19937(now.time_since_epoch().count())); //Integer since time began
	}

	void Engine::RandNumGenerator::stop(SystemSignal close, ...)
	{
		s_generator.reset();
	}

	int32_t Engine::RandNumGenerator::uniformIntBetween(int32_t lower, int32_t upper)
	{
		
		float t = (static_cast<float>(s_uniformInt(*s_generator) / s_intRange)) + 0.5f; 
		return lower + static_cast<uint32_t>(t * static_cast<float>(upper - lower)); // Generates a random integer between min and max

	}

	float Engine::RandNumGenerator::uniformFloatBetween(float lower, float upper)
	{
		float t = (s_uniformFloat(*s_generator) / s_floatRange); ////
		return lower + t * static_cast<float>(upper - lower); // Generates a random float between min and max

	}
	int32_t RandNumGenerator::normalInt(float c, float sigma)
	{
		std::normal_distribution<float> distribution(c, sigma);
		return static_cast<int32_t>(distribution(*s_generator));
	}
	float RandNumGenerator::normalFloat(float c, float sigma)
	{
		std::normal_distribution<float> distribution(c, sigma);
		return distribution(*s_generator);
	}
}

