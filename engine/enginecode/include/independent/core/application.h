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
#include "events/eventHandler.h"
#include <functional>

/** \class ApplicationFundemental class of the engine. A singleton which runs the game loop infinitely. */

namespace Engine {
	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<Timer> m_timer; //!< Timer system
		std::shared_ptr<Log> m_log; //!< Log system
		std::shared_ptr<EventHandler> m_eventHandler; //!< Event Handler
		std::shared_ptr<RandNumGenerator> m_randNumSystem; //!< Random number generator system
		void onWindowClose(WindowCloseEvent& e); //!< Run when the window is closed
		void onWindowResize(WindowResizeEvent& e); //!< Run when the window is resized
		void onWindowFocus(WindowFocusEvent& e); //!< Run when the window is focussed
		void onWindowLoseFocus(WindowLoseFocusEvent& e); //!< Run when the window is unfocussed
		void onWindowMove(WindowMoveEvent& e); //!< Run when the window is moved
		void onKeyPress(KeyPressEvent& e); //!< Run when a key is pressed
		void onKeyRelease(KeyReleaseEvent& e); //!< Run when a key is released
		void onKeyType(KeyTypeEvent& e); //!< Run when a key is typed
		void onMouseButtonPress(MouseButtonPressEvent& e); //!< Run when a mouse button is pressed
		void onMouseButtonRelease(MouseButtonReleaseEvent& e); //!< Run when a mouse button is released
		void onMouseMove(MouseMoveEvent& e); //!< Run when the mouse is moved
		void onMouseScroll(MouseScrollEvent& e); //!< Run when the mouse wheel is scrolled

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void onEvent(Event& e); //!> Called when an event happends
		void run(); //!< Main loop
		void onWindowClose(const WindowCloseEvent& e); //!< Run when the window closes

	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}