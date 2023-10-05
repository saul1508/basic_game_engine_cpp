/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
	#include "platforms/windows/winTimer.h"
#endif

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
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer);
#else
		m_timer.reset(new ChronoTimer);
#endif
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
			timeStep = m_timer->getElapsedTime();
			//Log::trace("Hello World! {0} {1}", 42, "I am a string");
			m_timer->reset();
			Log::trace("FPS {0}", 1.0f / timeStep);
			
		};
	}

}
