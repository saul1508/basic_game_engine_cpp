//* \file vhronoTimer.h */
#pragma once
#include "timer.h"

namespace Engine {
	//* \class ChronoTimer */
	class ChronoTimer : public Timer {
		public:
			inline void start() override { m_startPoint = std::chrono::high_resolution_clock::now(); }
			inline void reset() override { m_startPoint = std::chrono::high_resolution_clock::now(); }
			float getElapsedTimeMilli() {
				m_endPoint = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint; // Calculates the difference
				return elapsed.count(); // Returns elapsed time in milliseconds
			}
			float getElapsedTimeSec() {
				m_endPoint = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint; // Calculates the difference
				return elapsed.count() / 1000.f; // Returns elapsed time in seconds
			}
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint;
	};
}
