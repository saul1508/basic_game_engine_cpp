/** \file graphicsContext.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platforms/glfw/graphicsContext.h"
#include "systems/log.h"

namespace Engine {
	GraphicsContext::GraphicsContext(GLFWwindow* win) : m_window(win) {
		glfwMakeContextCurrent(m_window);
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		if (!result) Log::error("Could not create OpenGL context for the current GLFW window: {0}", result);

		//Enable OpenGL debug with a callback
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
			[](
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam
				)
			{
				switch (severity) {
				case GL_DEBUG_SEVERITY_HIGH:
					Log::error(message);
					break;
				case GL_DEBUG_SEVERITY_MEDIUM:
					Log::warn(message);
					break;
				case GL_DEBUG_SEVERITY_LOW:
					Log::info(message);
					break;
				}
			}
		, nullptr);
	}

	void GraphicsContext::swapBuffers() {
		glfwSwapBuffers(m_window);
	}
}

