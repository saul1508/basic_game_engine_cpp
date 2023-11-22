/** \file inputPoller.h */
#pragma once
#include <glm/glm.hpp>

namespace Engine {
	/** \class InputPoller
	* API agnostic input poller for getting the current keyboard and mouse state
	*/
	class InputPoller {
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Virtual method for if the key is pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< Virtual method for if the mouse button is pressed
		static glm::vec2 getMousePosition(); //!< Getter method for the mouse position
		static void setNativeWindow(void* nativeWin); //!< Setter method for the native window
		inline static float getMouseX(); //!< Getter method for the x position of the mouse
		inline static float getMouseY(); //!< Getter method for the y position of the mouse
	};
}
