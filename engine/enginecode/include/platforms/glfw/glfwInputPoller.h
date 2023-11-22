/** \file glfwInputPoller.h */
#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine {
	/** \class GLFWInputPoller
	*  Input poller for getting the current keyboard and mouse state specific to the GLFW system
	*/
	class GLFWInputPoller {
		public:
			static bool isKeyPressed(int32_t keyCode); //!< Virtual method for if the key is pressed
			static bool isMouseButtonPressed(int32_t mouseButton); //!< Virtual method for if the mouse button is pressed
			static glm::vec2 getMousePosition(); //!< Getter method for the mouse position
			static void setCurrentWindow(GLFWwindow* newWin) { m_window = newWin; }
		private:
			static GLFWwindow* m_window; //!< Current GLFW Window

	};
}