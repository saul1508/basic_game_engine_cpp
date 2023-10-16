/** \file eventHandler.h */
#pragma once
#include "event.h"
#include "windowEvents.h"
#include "keyEvents.h"
#include "mouseEvents.h"
#include <functional>

namespace Engine {
	/** \class EventHandler */
	class EventHandler {
		public:
			void setOnWindowClose(const std::function<void(const WindowCloseEvent& e)>& fn) { m_onWindowClose = fn; };
			void setOnWindowResize(const std::function<void(const WindowResizeEvent& e)>& fn) { m_onWindowResize = fn; };
			void setOnWindowFocus(const std::function<void(const WindowFocusEvent& e)>& fn) { m_onWindowFocus = fn; };
			void setOnWindowLose(const std::function<void(const WindowLoseFocusEvent& e)>& fn) { m_onWindowLoseFocus = fn; };
			void setOnWindowMove(const std::function<void(const WindowMoveEvent& e)>& fn) { m_onWindowMove = fn; };
			void setOnKeyPress(const std::function<void(const KeyPressEvent& e)>& fn) { m_onKeyPress = fn; };
			void setOnKeyRelease(const std::function<void(const KeyReleaseEvent& e)>& fn) { m_onKeyRelease = fn; };
			void setOnKeyType(const std::function<void(const KeyTypeEvent& e)>& fn) { m_onKeyType = fn; };
			void setOnMouseButtonPress(const std::function<void(const MouseButtonPressEvent& e)>& fn) { m_onMouseButtonPress = fn; };
			void setOnMouseButtonRelease(const std::function<void(const MouseButtonReleaseEvent& e)>& fn) { m_onMouseButtonRelease = fn; };
			void setOnMouseMove(const std::function<void(const MouseMoveEvent& e)>& fn) { m_onMouseMove = fn; };
			void setOnMouseScroll(const std::function<void(const MouseScrollEvent& e)>& fn) { m_onMouseScroll = fn; };

			std::function<void(const WindowCloseEvent& e)>& getOnWindowClose() { return m_onWindowClose; }
			std::function<void(const WindowResizeEvent& e)>& getOnWindowResize() { return m_onWindowResize; }
			std::function<void(const WindowFocusEvent& e)>& getOnWindowFocus() { return m_onWindowFocus; }
			std::function<void(const WindowLoseFocusEvent& e)>& getOnWindowLoseFocus() { return m_onWindowLoseFocus; }
			std::function<void(const WindowMoveEvent& e)>& getOnWindowMove() { return m_onWindowMove; }
			std::function<void(const KeyPressEvent& e)>& getOnKeyPress() { return m_onKeyPress; }
			std::function<void(const KeyReleaseEvent& e)>& getOnKeyRelease() { return m_onKeyRelease; }
			std::function<void(const KeyTypeEvent& e)>& getOnKeyType() { return m_onKeyType; }
			std::function<void(const MouseButtonPressEvent& e)>& getOnMouseButtonPress() { return m_onMouseButtonPress; }
			std::function<void(const MouseButtonReleaseEvent& e)>& getOnMouseButtonRelease() { return m_onMouseButtonRelease; }
			std::function<void(const MouseMoveEvent& e)>& getOnMouseMove() { return m_onMouseMove; }
			std::function<void(const MouseScrollEvent& e)>& getOnMouseScroll() { return m_onMouseScroll; }

		private:
			std::function<void(const WindowCloseEvent& e)> m_onWindowClose = [](const WindowCloseEvent& e) {};
			std::function<void(const WindowResizeEvent& e)> m_onWindowResize = [](const WindowResizeEvent& e) {};
			std::function<void(const WindowFocusEvent& e)> m_onWindowFocus = [](const WindowFocusEvent& e) {};
			std::function<void(const WindowLoseFocusEvent& e)> m_onWindowLoseFocus = [](const WindowLoseFocusEvent& e) {};
			std::function<void(const WindowMoveEvent& e)> m_onWindowMove = [](const WindowMoveEvent& e) {};
			std::function<void(const KeyPressEvent& e)> m_onKeyPress = [](const KeyPressEvent& e) {};
			std::function<void(const KeyReleaseEvent& e)> m_onKeyRelease = [](const KeyReleaseEvent& e) {};
			std::function<void(const KeyTypeEvent& e)> m_onKeyType = [](const KeyTypeEvent& e) {};
			std::function<void(const MouseButtonPressEvent& e)> m_onMouseButtonPress = [](const MouseButtonPressEvent& e) {};
			std::function<void(const MouseButtonReleaseEvent& e)> m_onMouseButtonRelease = [](const MouseButtonReleaseEvent& e) {};
			std::function<void(const MouseMoveEvent& e)> m_onMouseMove = [](const MouseMoveEvent& e) {};
			std::function<void(const MouseScrollEvent& e)> m_onMouseScroll = [](const MouseScrollEvent& e) {};
	};
}

