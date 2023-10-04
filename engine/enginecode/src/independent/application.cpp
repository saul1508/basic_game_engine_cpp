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
		//m_timer.reset(new ChronoTimer);
		//m_timer->start();
	
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
			Log::info("Hello World! {0} {1}", 42, "I am a string");
			//timeStep = m_timer->getElapsedTimeMilli();
			//m_timer->reset();
		};
	}

}
