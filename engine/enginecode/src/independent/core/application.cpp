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

		// Start systems

		// Start logger
		m_log.reset(new Log);
		m_log->start();

		//Start random number system
		m_randNumSystem.reset(new RandNumGenerator);
		m_randNumSystem->start();

		// Start timer system
//#ifdef NG_PLATFORM_WINDOWS
//		m_timer.reset(new WinTimer);
//#else
		m_timer.reset(new ChronoTimer);
//#endif
		m_timer->start();

		// Start glfw system
		m_glfwSystem.reset(new GLFWSystem);
		m_glfwSystem->start();

	
		m_eventHandler.setOnWindowClose([this](WindowCloseEvent& e) {this->onWindowClose(e);});

	}

	Application::~Application()
	{
		// Stop systems

		//Stop random number system
		m_randNumSystem->stop();
		//Stop logger
		m_log->stop();
		//Stop glfw system
		m_glfwSystem->stop();
	}

	void Application::onWindowClose(WindowCloseEvent& e) {
		Log::trace("Closing application");
		m_running = false;
		e.handle(true);
	}
	void Application::onWindowResize(WindowResizeEvent& e) {
		Log::trace("Resized window to {0} by {1}", e.getWidth(), e.getHeight());
	}
	void Application::onWindowFocus(WindowFocusEvent& e) {
		Log::trace("Focussed window");
	}
	void Application::onWindowLoseFocus(WindowLoseFocusEvent& e) {
		Log::trace("Unfocussed window");
	}
	void Application::onWindowMove(WindowMoveEvent& e) {
		Log::trace("Moved window to x:{0}, y:{1}", e.getNewXPos(), e.getNewYPos());
	}

	void Application::onKeyPress(KeyPressEvent& e) {
		Log::trace("{0} key pressed {1} times", e.getKeyCode(), e.getRepeatCount());
	}
	void Application::onKeyRelease(KeyReleaseEvent& e) {
		Log::trace("{0} key released", e.getKeyCode());
	}
	void Application::onKeyType(KeyTypeEvent& e) {
		Log::trace("{0} key typed", e.getKeyCode());
	}

	void Application::onMouseButtonPress(MouseButtonPressEvent& e) {
		Log::trace("Mouse button {0} pressed", e.getButton());
	}
	void Application::onMouseButtonRelease(MouseButtonReleaseEvent& e) {
		Log::trace("Mouse button {0} released", e.getButton());
	}
	void Application::onMouseScroll(MouseScrollEvent& e) {
		Log::trace("Mouse scrolled to an offset of {0}", e.getOffset());
	}
	void Application::onMouseMove(MouseMoveEvent& e) {
		Log::trace("Mouse moved to x:{0} y:{1}", e.getNewXPos(), e.getNewYPos());
	}


	void Application::run()
	{
		float timeStep = 0.f;
		float accumulatedTime = 0.0f;

		while (m_running)
		{
			timeStep = m_timer->getElapsedTime();
			m_timer->reset();

			accumulatedTime += timeStep;


			//Log::trace("Hello World! {0} {1}", 42, "I am a string");
			//Log::trace("FPS {0} {1}", 1.0f / timeStep,  accumulatedTime);
			//Log::trace("{0}", RandNumGenerator::normalInt(10.f, 2.5f));
			//Log::trace("{0}", RandNumGenerator::uniformIntBetween(-10, 10));
			if (accumulatedTime > 3000.0f) {

				WindowCloseEvent close;

				auto& callback = m_eventHandler.getOnWindowClose();
				WindowCloseEvent wce;

				callback(wce);

			}

		};
	}


}
