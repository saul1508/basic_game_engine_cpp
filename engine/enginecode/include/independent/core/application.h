/** \file application.h */
#pragma once
#include "systems/log.h"
#include "systems/randNumGenerator.h"
#include "core/timer.h"
#include "core/chronoTimer.h"
#include "platforms/windows/winTimer.h"
#include "events/event.h"
#include "events/windowEvents.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
#include "events/eventDispatcher.h"

/** \class ApplicationFundemental class of the engine. A singleton which runs the game loop infinitely. */

namespace Engine {
	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<Timer> m_timer;
		std::shared_ptr<Log> m_log;
		std::shared_ptr<RandNumGenerator> m_randNumSystem; //!< Random number generator system#
		bool onWindowClose(WindowCloseEvent& e); //!< On window close event
		bool onWindowResize(WindowResizeEvent& e); //!< On window resize event
		bool onWindowFocus(WindowFocusEvent& e); //!< On window focus event
		bool onWindowLostFocus(WindowLostFocusEvent& e); //!< On window lost focus event
		bool onWindowMove(WindowMovedEvent& e); //!< On window move event
		bool onKeyPressed(KeyPressedEvent& e); //!< On key pressed event
		bool onKeyReleased(KeyReleasedEvent& e); //!< On key released event
		bool onKeyTyped(KeyTypedEvent& e); //!< On key typed event
		bool onMouseButtonPressed(MouseButtonPressedEvent& e); //!< On mouse button pressed event
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e); //!< On mouse button released event
		bool onMouseMoved(MouseMovedEvent& e); //!< On mouse button moved event
		bool onMouseScrolled(MouseScrolledEvent& e); //!< On mouse scrolled event
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void onEvent(Event& e); //!> Called when an event happends
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}