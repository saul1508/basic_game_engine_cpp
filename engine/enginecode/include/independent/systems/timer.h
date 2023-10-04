//* \file timer.h */
#pragma once
#include <chrono>

/**
\class Time - interface class for the timer class
*/

namespace Engine {
	
	class Timer {
		public:
			virtual void start() = 0; //<! Start timer
			virtual void reset() = 0; //<! Reset timer
			virtual float getElapsedTimeMilli() = 0; //<! Returns the time elapsed in milliseconds since last start or restart of timer
			virtual float getElapsedTimeSec() = 0; //<! Returns the time elapsed in seconds since last start or restart of timer
	};

}

