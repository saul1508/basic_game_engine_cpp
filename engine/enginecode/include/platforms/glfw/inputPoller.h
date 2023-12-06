/** \file inputPoller.h */
#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Engine {
	/** \class InputPoller
	* GLFW Input poller for getting the current keyboard/mouse state
	*/
	class InputPoller {
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Method for if a key is pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Method for if a mouse button is pressed
		static glm::vec2 getMousePosition(); //!< Getter method for the mouse position
		static void setNativeWindow(void* nativeWin); //!< Setter method for the glfw native window
		inline static float getMouseX() { return getMousePosition().x; } //!< Method to get the x position of the mouse
		inline static float getMouseY() { return getMousePosition().y; } //!< Methof to get the y position of the mouse
	private:
		inline static GLFWwindow* s_window = nullptr; //!< Pointer attribute for the current GLFW window
	};
}

