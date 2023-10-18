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

/** \class ApplicationFundemental class of the engine. A singleton which runs the game loop infinitely. */

namespace Engine {
	class Application
	{
	protected:
		Application(); //!< Constructor for Application
		std::shared_ptr<Timer> m_timer; //!< Timer system attribute
		std::shared_ptr<Log> m_log; //!< Log system attribute
		std::shared_ptr<RandNumGenerator> m_randNumSystem; //!< Random number generator system attribute

		EventHandler m_eventHandler; //!< Event Handler sttribute
		void onWindowClose(WindowCloseEvent& e); //!< Method for when the window is closed
		void onWindowResize(WindowResizeEvent& e); //!< Method for when the window is resized
		void onWindowFocus(WindowFocusEvent& e); //!< Method for when the window is focussed
		void onWindowLoseFocus(WindowLoseFocusEvent& e); //!< Method for when the window is unfocussed
		void onWindowMove(WindowMoveEvent& e); //!< Method for when the window is moved
		void onKeyPress(KeyPressEvent& e); //!< Method for when a key is pressed
		void onKeyRelease(KeyReleaseEvent& e); //!< Method for when a key is released
		void onKeyType(KeyTypeEvent& e); //!< Method for when a key is typed
		void onMouseButtonPress(MouseButtonPressEvent& e); //!< Method for when a mouse button is pressed
		void onMouseButtonRelease(MouseButtonReleaseEvent& e); //!< Method for when a mouse button is released
		void onMouseMove(MouseMoveEvent& e); //!< Method for when the mouse is moved
		void onMouseScroll(MouseScrollEvent& e); //!< Method for when the mouse wheel is scrolled

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Attribute to denote whether the application running?
	public:
		virtual ~Application(); //!< Deconstructor for Application
		inline static Application& getInstance() { return *s_instance; } //!< Inline getter method for singleton pattern
		void run(); //!< Method for main loop

	};

	Application* startApplication(); //!< Function definition which provides an entry hook
}