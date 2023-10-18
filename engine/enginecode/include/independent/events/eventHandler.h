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
			void setOnWindowClose(const std::function<void(WindowCloseEvent& e)>& fn) { m_onWindowClose = fn; };
			void setOnWindowResize(const std::function<void( WindowResizeEvent& e)>& fn) { m_onWindowResize = fn; };
			void setOnWindowFocus(const std::function<void( WindowFocusEvent& e)>& fn) { m_onWindowFocus = fn; };
			void setOnWindowLose(const std::function<void(WindowLoseFocusEvent& e)>& fn) { m_onWindowLoseFocus = fn; };
			void setOnWindowMove(const std::function<void(WindowMoveEvent& e)>& fn) { m_onWindowMove = fn; };
			void setOnKeyPress(const std::function<void(KeyPressEvent& e)>& fn) { m_onKeyPress = fn; };
			void setOnKeyRelease(const std::function<void(KeyReleaseEvent& e)>& fn) { m_onKeyRelease = fn; };
			void setOnKeyType(const std::function<void(KeyTypeEvent& e)>& fn) { m_onKeyType = fn; };
			void setOnMouseButtonPress(const std::function<void(MouseButtonPressEvent& e)>& fn) { m_onMouseButtonPress = fn; };
			void setOnMouseButtonRelease(const std::function<void(MouseButtonReleaseEvent& e)>& fn) { m_onMouseButtonRelease = fn; };
			void setOnMouseMove(const std::function<void(MouseMoveEvent& e)>& fn) { m_onMouseMove = fn; };
			void setOnMouseScroll(const std::function<void(MouseScrollEvent& e)>& fn) { m_onMouseScroll = fn; };

			std::function<void(WindowCloseEvent& e)>& getOnWindowClose() { return m_onWindowClose; }
			std::function<void(WindowResizeEvent& e)>& getOnWindowResize() { return m_onWindowResize; }
			std::function<void(WindowFocusEvent& e)>& getOnWindowFocus() { return m_onWindowFocus; }
			std::function<void(WindowLoseFocusEvent& e)>& getOnWindowLoseFocus() { return m_onWindowLoseFocus; }
			std::function<void(WindowMoveEvent& e)>& getOnWindowMove() { return m_onWindowMove; }
			std::function<void(KeyPressEvent& e)>& getOnKeyPress() { return m_onKeyPress; }
			std::function<void(KeyReleaseEvent& e)>& getOnKeyRelease() { return m_onKeyRelease; }
			std::function<void(KeyTypeEvent& e)>& getOnKeyType() { return m_onKeyType; }
			std::function<void(MouseButtonPressEvent& e)>& getOnMouseButtonPress() { return m_onMouseButtonPress; }
			std::function<void(MouseButtonReleaseEvent& e)>& getOnMouseButtonRelease() { return m_onMouseButtonRelease; }
			std::function<void(MouseMoveEvent& e)>& getOnMouseMove() { return m_onMouseMove; }
			std::function<void(MouseScrollEvent& e)>& getOnMouseScroll() { return m_onMouseScroll; }

		private:
			std::function<void(WindowCloseEvent& e)> m_onWindowClose = [](WindowCloseEvent& e) {};
			std::function<void(WindowResizeEvent& e)> m_onWindowResize = [](WindowResizeEvent& e) {};
			std::function<void(WindowFocusEvent& e)> m_onWindowFocus = [](WindowFocusEvent& e) {};
			std::function<void(WindowLoseFocusEvent& e)> m_onWindowLoseFocus = [](WindowLoseFocusEvent& e) {};
			std::function<void(WindowMoveEvent& e)> m_onWindowMove = [](WindowMoveEvent& e) {};
			std::function<void(KeyPressEvent& e)> m_onKeyPress = [](KeyPressEvent& e) {};
			std::function<void(KeyReleaseEvent& e)> m_onKeyRelease = [](KeyReleaseEvent& e) {};
			std::function<void(KeyTypeEvent& e)> m_onKeyType = [](KeyTypeEvent& e) {};
			std::function<void(MouseButtonPressEvent& e)> m_onMouseButtonPress = [](MouseButtonPressEvent& e) {};
			std::function<void(MouseButtonReleaseEvent& e)> m_onMouseButtonRelease = [](MouseButtonReleaseEvent& e) {};
			std::function<void(MouseMoveEvent& e)> m_onMouseMove = [](MouseMoveEvent& e) {};
			std::function<void(MouseScrollEvent& e)> m_onMouseScroll = [](MouseScrollEvent& e) {};
	};
}

