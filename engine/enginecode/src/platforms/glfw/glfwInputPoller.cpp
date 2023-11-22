/** \file glfwInputPoller.cpp */

#include "engine_pch.h"
#include "platforms/glfw/glfwInputPoller.h"

namespace Engine {

	GLFWwindow* GLFWInputPoller::m_window = nullptr;

	bool GLFWInputPoller::isKeyPressed(int32_t keyCode)
	{
		if (m_window) {
			auto answer = glfwGetKey(m_window, keyCode);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;
		}
		return false;
	}
	bool GLFWInputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		if (m_window) {
			auto answer = glfwGetMouseButton(m_window, mouseButton);
			return answer == GLFW_PRESS;
		}
		return false;
	}
	glm::vec2 GLFWInputPoller::getMousePosition()
	{
		if (m_window) {
			double x, y;
			glfwGetCursorPos(m_window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));
		}
		{
			return { -1.f, 1.f };
		}
	}

}