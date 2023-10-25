/** \file winTimer */
#pragma once

#include <Windows.h>
#include "core/timer.h"

namespace Engine {
	/** \class WinTimer
	* Timer specific to Windows which uses queryPerformanceCount
	*/

	class WinTimer : public Timer {
		public:
			virtual void start() {
				QueryPerformanceFrequency(&m_frequency);
				QueryPerformanceCounter(&m_startTime);
			};
			virtual inline void reset() override { QueryPerformanceCounter(&m_startTime); }; //!< Start time in CPU ticks

			virtual float getElapsedTime() override {
				QueryPerformanceCounter(&m_endTime);
				float result = (m_endTime.QuadPart - m_startTime.QuadPart) * 1000.0 / m_frequency.QuadPart;
				return result;
			}

		private:
			LARGE_INTEGER m_startTime; //!< Start time
			LARGE_INTEGER m_endTime; //!< End time
			LARGE_INTEGER m_frequency; //!< Ticks per second of the CPU
	};
}