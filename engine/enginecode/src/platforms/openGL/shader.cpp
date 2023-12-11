#include "engine_pch.h"
#include "platforms/openGL/shader.h"
#include <fstream>
#include "systems/log.h"
#include <string>
#include <array>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
	Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
	{
		std::string vertexSrc, fragmentSrc, line;
		std::fstream handle(vertexFilePath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) {
				vertexSrc += (line + "\n");
			}
		}
		else {
			Log::error("Could not open vertex shader source: {0}", vertexFilePath);
			return;
		}
		handle.close();
		handle.open(fragmentFilePath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) {
				fragmentSrc += (line + "\n");
			}
		}
		else {
			Log::error("Could not open fragment shader source: {0}", fragmentFilePath);
			return;
		}
		handle.close();
		compileAndLink(vertexSrc.c_str(), fragmentSrc.c_str());
	}

	Shader::Shader(const char* filepath)
	{
		enum Region {None = -1, Vertex = 0, Fragment, Geometry, TessellationControl, TessellationEvaluation, Compute };
		std::string line;
		std::array<std::string, Region::Compute + 1> src;
		uint32_t region = Region::None;
		std::fstream handle(filepath, std::ios::in);
		if (handle.is_open()) {

			while (getline(handle, line)) {
				if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; continue; }
				if (line.find("#region Fragment") != std::string::npos) { region = Region::Fragment;continue; }
				if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry;continue; }
				if (line.find("#region TesselationControl") != std::string::npos) { region = Region::TessellationControl; continue; }
				if (line.find("#region TesselationEvaluation") != std::string::npos) { region = Region::TessellationEvaluation; continue; }
				if (line.find("#region Compute") != std::string::npos) region = Region::Compute; continue; 
				if (region != Region::None) src[region] += (line + "\n"); 
			}

		} else {
			Log::error("Could not open shader source: {0}", filepath);
			return;
		}
		handle.close();
		compileAndLink(src[Region::Vertex].c_str(), src[Region::Fragment].c_str());
		Log::error("src: {}", src[Region::Vertex].c_str());
	}

	Shader::~Shader()
	{
		glDeleteShader(m_openGLID);
	}

	void Shader::use()
	{
	}

	void Shader::uploadInt(const char* name, int value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
		glUniform1i(uniformLocation, value);
	}

	void Shader::uploadFloat(const char* name, float value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
		glUniform1f(uniformLocation, value);
	}

	void Shader::uploadFloat2(const char* name, const glm::vec2& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
		glUniform2f(uniformLocation, value.x, value.y);
	}

	void Shader::uploadFloat3(const char* name, const glm::vec3& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void Shader::uploadFloat4(const char* name, const glm::vec4& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void Shader::uploadMat4(const char* name, const glm::mat4& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc)
	{
		// Vertex
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexShaderSrc;
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 2048;

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));
			glDeleteShader(vertexShader);
			return;
		}

		// Fragment
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentShaderSrc;
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);

		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			return;
		}

		m_openGLID = glCreateProgram();
		glAttachShader(m_openGLID, vertexShader);
		glAttachShader(m_openGLID, fragmentShader);
		glLinkProgram(m_openGLID);

		GLint isLinked = 0;
		glGetProgramiv(m_openGLID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_openGLID, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_openGLID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		glDetachShader(m_openGLID, vertexShader);
		glDetachShader(m_openGLID, fragmentShader);
	}

}
