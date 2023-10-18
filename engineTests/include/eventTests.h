#pragma once
#include <gtest/gtest.h>

#include "events/eventHandler.h"

namespace EventTests
{
	std::shared_ptr<Engine::EventHandler> handler;

	std::array<bool, 12> callbackChecks;

	void init()
	{
		if (!handler)
		{
			for (auto& b : callbackChecks) { b = false; }

			handler.reset(new Engine::EventHandler);

			handler->setOnWindowClose([](Engine::WindowCloseEvent& e) {callbackChecks[0] = true; e.handle(true); });
			handler->setOnWindowResize([](Engine::WindowResizeEvent& e) {callbackChecks[1] = true; e.handle(true); });
			handler->setOnWindowFocus([](Engine::WindowFocusEvent& e) {callbackChecks[2] = true; e.handle(true); });
			handler->setOnWindowLose([](Engine::WindowLoseFocusEvent& e) {callbackChecks[3] = true; e.handle(true); });

			handler->setOnKeyPress([](Engine::KeyPressEvent& e) {callbackChecks[4] = true; e.handle(true); });
			handler->setOnKeyRelease([](Engine::KeyReleaseEvent& e) {callbackChecks[5] = true; e.handle(true); });
			handler->setOnKeyType([](Engine::KeyTypeEvent& e) {callbackChecks[6] = true; e.handle(true); });

			handler->setOnMouseButtonPress([](Engine::MouseButtonPressEvent& e) {callbackChecks[7] = true; e.handle(true); });
			handler->setOnMouseButtonRelease([](Engine::MouseButtonReleaseEvent& e) {callbackChecks[8] = true; e.handle(true); });
			handler->setOnMouseMove([](Engine::MouseMoveEvent& e) {callbackChecks[9] = true; e.handle(true); });
			handler->setOnMouseScroll([](Engine::MouseScrollEvent& e) {callbackChecks[10] = true; e.handle(true); });
		}
	}
}