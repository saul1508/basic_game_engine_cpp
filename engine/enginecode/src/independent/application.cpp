/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		//Start systems

		//Start logger
		m_log.reset(new Log);
		m_log->start();

		//Reset timer
		m_timer.reset(new ChronoTimer);
		m_timer->start();
	
	}

	Application::~Application()
	{
		// Stop systems

		//Stop logger
		m_log->stop();
	}


	void Application::run()
	{
		float timeStep = 0.f;

		while (m_running)
		{
			timeStep = m_timer->getElapsedTimeSec();
			Log::trace("Hello World! {0} {1}", 42, "I am a string");
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timeStep);
			
		};
	}

}
