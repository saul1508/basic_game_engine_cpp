/** \file application.h */
#pragma once
#include "systems/log.h"
#include "systems/timer.h"
#include "systems/chronoTimer.h"


/** \class ApplicationFundemental class of the engine. A singleton which runs the game loop infinitely. */

namespace Engine {
	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<Timer> m_timer;
		std::shared_ptr<Log> m_log;
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}