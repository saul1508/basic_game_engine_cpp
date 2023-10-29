/** \file window.cpp */
#include "engine_pch.h"
#include "platforms/glfw/window.h"
#include "systems/log.h"

namespace Engine {
	Window::Window(const WindowProperties& properties)
	{
		if (properties.isFullScreen) {
			m_native = glfwCreateWindow(properties.width, properties.height, properties.title, glfwGetPrimaryMonitor(), NULL);
		} else {
			m_native = glfwCreateWindow(properties.width, properties.height, properties.title, NULL, NULL);
		}
		
		if(!m_native) {
			Log::error("Window not created");
		}
		setVSync(properties.isVSync);

		m_graphicsContext.reset(new GraphicsContext(m_native)); // Needs to do something
		m_aspectRatio = (float)properties.width / (float)properties.height;
		m_winProps = properties;
		
		glfwSetWindowUserPointer(m_native, &m_handler);
		glfwSetWindowCloseCallback(m_native,
			[](GLFWwindow* win) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				auto& callback = handler->getOnWindowClose();
				WindowCloseEvent e;
				callback(e);
			});

		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow* win, int32_t focused) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				if (focused) {
					auto& callback = handler->getOnWindowFocus();
					WindowFocusEvent e;
					callback(e);
				} else {
					auto& callback = handler->getOnWindowLoseFocus();
					WindowLoseFocusEvent e;
					callback(e);
				}
			});

		glfwSetWindowPosCallback(m_native,
			[](GLFWwindow* win, int32_t xpos, int32_t ypos) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				auto& callback = handler->getOnWindowMove();
				WindowMoveEvent e(xpos, ypos);
				callback(e);
			});

		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow* win, int32_t width, int32_t height) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				auto& callback = handler->getOnWindowResize();
				WindowResizeEvent e(width, height);
				callback(e);
			});

		glfwSetKeyCallback(m_native,
			[](GLFWwindow* win, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				if (action == GLFW_PRESS) {
					auto& callback = handler->getOnKeyPress();
					KeyPressEvent e(key, 0);
					callback(e);
				} else if (action == GLFW_REPEAT) {
					auto& callback = handler->getOnKeyPress();
					KeyPressEvent e(key, 1);
					callback(e);
				} else if (action == GLFW_RELEASE) {
					auto& callback = handler->getOnKeyRelease();
					KeyReleaseEvent e(key);
					callback(e);
				}
			});

		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow* win, int32_t button, int32_t action, int32_t mods) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				if (action == GLFW_PRESS) {
					auto& callback = handler->getOnMouseButtonPress();
					MouseButtonPressEvent e(button);
					callback(e);
				}
				else if (action == GLFW_RELEASE) {
					auto& callback = handler->getOnMouseButtonRelease();
					MouseButtonReleaseEvent e(button);
					callback(e);
				}
			});
		
		glfwSetScrollCallback(m_native,
			[](GLFWwindow* win, double xoffset, double yoffset) {
				EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(win);
				auto& callback = handler->getOnMouseScroll();
				MouseScrollEvent e(xoffset);
				callback(e);
			});

			
	}

	void Window::close()
	{
	}

	void Window::onUpdate(float timeStep)
	{
		glfwPollEvents();
		m_graphicsContext->swapBuffers();
	}

	void Window::setVSync(bool VSync) {
		m_winProps.isVSync = VSync;
		if (m_winProps.isVSync) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}

}

