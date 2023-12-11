/** \file shader.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Engine {
	/** \class Shader */
	class Shader {
	public:
		Shader(const char* vertexFilePath, const char* fragmentFilePath); //!< Constructor taking in two file paths
		Shader(const char* filepath); //!< Overruden constructor taking one file path
		~Shader(); //!< Destructor for Shader
		uint32_t getID() const { return m_openGLID; } //!< Getter method for the openGL ID
		void use(); //!< Method to use the currently bound shader
		void uploadInt(const char* name, int value); //!< Method to upload an integer
		void uploadFloat(const char* name, float value); //!< Method to upload a float
		void uploadFloat2(const char* name, const glm::vec2& value); //!< Method to upload a vec2
		void uploadFloat3(const char* name, const glm::vec3& value); //!< Method to upload a vec3
		void uploadFloat4(const char* name, const glm::vec4& value); //!< Method to upload a vec4
		void uploadMat4(const char* name, const glm::mat4& value); //!< Method to upload a mat4
	private:
		uint32_t m_openGLID; //!< OpenGL ID attribute
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc); //!< Method to compile and link the shader programs
	};
}
