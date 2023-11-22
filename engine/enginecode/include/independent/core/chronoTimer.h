//* \file chronoTimer.h */
#pragma once
#include "timer.h"

namespace Engine {
	//* \class ChronoTimer */
	class ChronoTimer : public Timer {
		public:
			inline void start() override { m_startPoint = std::chrono::high_resolution_clock::now(); } //!< Overriden start method to start the ChronoTimer
			inline void reset() override { m_startPoint = std::chrono::high_resolution_clock::now(); } //!< Overriden reset method to reset the ChronoTimer
			float getElapsedTime() { //!< Getter method for the time elapsed since start
				m_endPoint = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> elapsed = m_endPoint - m_startPoint; // Calculates the difference
				return elapsed.count(); // Returns elapsed time in milliseconds
			}
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint; //!< Attribute for the start time
			std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint; //!< Attribute for the end time
	};
}
