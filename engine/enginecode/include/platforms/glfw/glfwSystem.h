/** \file glfwSystem.h */
#pragma once

#include <GLFW/glfw3.h>
#include "systems/system.h"
#include "systems/log.h"

namespace Engine {

	/** \class GLFWSystem */
	class GLFWSystem : public System {
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override { //!< Start the glfwSystem
			if(!glfwInit()) Log::error("GLFW did not initialise"); 
		} 
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override { 
			glfwTerminate();
		}
	};
}


