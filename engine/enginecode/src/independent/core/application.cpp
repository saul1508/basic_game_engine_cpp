/** \file application.cpp */

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

		//Start random number system
		m_randNumSystem.reset(new RandNumGenerator);
		m_randNumSystem->start();

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

		//Stop random number system
		m_randNumSystem->stop();
		//Stop logger
		m_log->stop();
	}

	bool Application::onWindowClose(WindowCloseEvent& e) {
		Log::trace("Closing application");
		m_running = false;
		return true;
	}
	bool Application::onWindowResize(WindowResizeEvent& e) {
		Log::trace("Resized window to {0} by {1}", e.getWidth(), e.getHeight());
		return true;
	}
	bool Application::onWindowFocus(WindowFocusEvent& e) {
		Log::trace("Focussed window");
		return true;
	}
	bool Application::onWindowLostFocus(WindowLostFocusEvent& e) {
		Log::trace("Unfocussed window");
		return true;
	}
	bool Application::onWindowMove(WindowMovedEvent& e) {
		Log::trace("Moved window to x:{0}, y:{1}", e.getNewXPos(), e.getNewYPos());
		return true;
	}

	bool Application::onKeyPressed(KeyPressedEvent& e) {
		Log::trace("{0} key pressed {1} times", e.getKeyCode(), e.getRepeatCount());
		return true;
	}
	bool Application::onKeyReleased(KeyReleasedEvent& e) {
		Log::trace("{0} key released", e.getKeyCode());
		return true;
	}
	bool Application::onKeyTyped(KeyTypedEvent& e) {
		Log::trace("{0} key typed", e.getKeyCode());
		return true;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressedEvent& e) {
		Log::trace("Mouse button {0} pressed", e.getButton());
		return true;
	}
	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent& e) {
		Log::trace("Mouse button {0} released", e.getButton());
		return true;
	}
	bool Application::onMouseScrolled(MouseScrolledEvent& e) {
		Log::trace("Mouse scrolled to an offset of {0}", e.getOffset());
		return true;
	}
	bool Application::onMouseMoved(MouseMovedEvent& e) {
		Log::trace("Mouse moved to x:{0} y:{1}", e.getNewXPos(), e.getNewYPos());
		return true;
	}


	void Application::run()
	{
		float timeStep = 0.f;
		float accumulatedTime = 0.0f;

		while (m_running)
		{
			timeStep = m_timer->getElapsedTime();
			accumulatedTime += timeStep;
			m_timer->reset();
			//Log::trace("Hello World! {0} {1}", 42, "I am a string");
			//Log::trace("FPS {0}", 1.0f / timeStep);
			//Log::trace("{0}", RandNumGenerator::normalInt(10.f, 2.5f));
			//Log::trace("{0}", RandNumGenerator::uniformIntBetween(-10, 10));
			if (accumulatedTime > 10.0f) {
				WindowResizeEvent e1(1024, 720);
				onEvent(e1);
				WindowCloseEvent e2;
				onEvent(e2);
			}

		};
	}

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));
	}

}
