//* \file timer.h */
#pragma once
#include <chrono>

/**
\class Time - interface class for the timer class
*/

namespace Engine {
	
	class Timer {
		public:
			virtual void start() = 0; //<! Start timer attribute
			virtual void reset() = 0; //<! Reset timer attribute
			virtual float getElapsedTime() = 0; //<! Getter method to returns the time elapsed in milliseconds since last start or restart of timer
	};

}

