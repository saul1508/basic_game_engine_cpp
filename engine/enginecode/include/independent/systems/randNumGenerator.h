/** \file randNumGenerator */
#pragma once

#include <random>
#include "system.h"

namespace Engine {
	/** \class RandNumGenerator */
	class RandNumGenerator : public System {
		public:
			virtual void start(SystemSignal init = SystemSignal::None, ...) override; //!< Start the generator
			virtual void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Stop the generator

			static int32_t uniformIntBetween(int32_t lower, int32_t upper); //!< Get an integer i so that lower <= i <= upper
			static float uniformFloatBetween(float lower, float upper); //!< Get a float i so that lower <= i <= upper
			static int32_t normalInt(float c, float sigma); //!< Get an integer from a normal distribution created from c and sigma
			static float normalFloat(float c, float sigma); //!< Get a float from a normal distribution created from c and sigma
		private:
			static std::shared_ptr<std::mt19937> s_generator; //!< Random number engine
			static std::uniform_int_distribution<int32_t> s_uniformInt; //!< Uniform integer distribution
			static std::uniform_real_distribution<float> s_uniformFloat; //!< Uniform float distribution
			static float s_intRange; //!< Range of an int32_t
			static float s_floatRange; //!< Range of a float

	};
}
