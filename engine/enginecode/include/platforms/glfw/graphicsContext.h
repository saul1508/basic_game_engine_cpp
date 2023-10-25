/** \file graphicsContext.h */
#pragma once
#include <GLFW/glfw3.h>

namespace Engine {
	/** \class GraphicsContext */
	class GraphicsContext {
		public:
			GraphicsContext() = delete; //!< No default use case
			GraphicsContext(GLFWwindow* window); //!< GraphicsContext constructor
			void swapBuffers(); //!< Method to swap the front and back buffers (double buffering)
		private:
			GLFWwindow* m_window; //!< Pointer attribute to a GLFW window
	};
}

