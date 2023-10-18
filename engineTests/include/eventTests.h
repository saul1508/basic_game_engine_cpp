/** \file eventTests.h */
#pragma once

#include <gtest/gtest.h>
#include "events/eventHandler.h"

namespace EventTests
{
	std::shared_ptr<Engine::EventHandler> handler; //!< EventHandler object

	std::array<bool, 12> callbackChecks; //!< Array of callback checks

	void init()
	{
		if (!handler)
		{
			for (auto& b : callbackChecks) { b = false; } //!< Sets all callback checks to false

			handler.reset(new Engine::EventHandler); //!< Reset the EventHandler instance

			handler->setOnWindowClose([](Engine::WindowCloseEvent& e) {callbackChecks[0] = true; e.handle(true); }); //!< Handles the window close event
			handler->setOnWindowResize([](Engine::WindowResizeEvent& e) {callbackChecks[1] = true; e.handle(true); }); //!< Handles the window resize event
			handler->setOnWindowFocus([](Engine::WindowFocusEvent& e) {callbackChecks[2] = true; e.handle(true); }); //!< Handles the window focus event
			handler->setOnWindowLose([](Engine::WindowLoseFocusEvent& e) {callbackChecks[3] = true; e.handle(true); }); //!< Handles the window lose-focus event

			handler->setOnKeyPress([](Engine::KeyPressEvent& e) {callbackChecks[4] = true; e.handle(true); }); //!< Handles the key press event
			handler->setOnKeyRelease([](Engine::KeyReleaseEvent& e) {callbackChecks[5] = true; e.handle(true); }); //!< Handles the key release event
			handler->setOnKeyType([](Engine::KeyTypeEvent& e) {callbackChecks[6] = true; e.handle(true); }); //!< Handles the key type event

			handler->setOnMouseButtonPress([](Engine::MouseButtonPressEvent& e) {callbackChecks[7] = true; e.handle(true); }); //!< Handles the mouse button press event
			handler->setOnMouseButtonRelease([](Engine::MouseButtonReleaseEvent& e) {callbackChecks[8] = true; e.handle(true); }); //!< Handles the mouse button release event
			handler->setOnMouseMove([](Engine::MouseMoveEvent& e) {callbackChecks[9] = true; e.handle(true); }); //!< Handles the mouse move event
			handler->setOnMouseScroll([](Engine::MouseScrollEvent& e) {callbackChecks[10] = true; e.handle(true); }); //!< Handles the mouse scroll event
		}
	}
}