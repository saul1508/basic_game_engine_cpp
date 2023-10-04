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

		//Reset timer
		m_timer.reset(new ChronoTimer);
		m_timer->start();
	
	}

	Application::~Application()
	{
	}


	void Application::run()
	{
		float timeStep = 0.f;

		while (m_running)
		{
			timeStep = m_timer->getElapsedTimeMilli();
			m_timer->reset();
		};
	}

}
