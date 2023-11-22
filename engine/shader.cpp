#include "engine_pch.h"
#include "shader.h"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
}

void Shader::use()
{
}

void Shader::uploadInt(const char* name, int value)
{
	uint32_t uniformLocation = glGetUniformLocation(m_openGLID, name);
	glUniform1i(uniformLocation, value);
}

void Shader::uploadIntArray(const char* name, int32_t* values, int32_t count)
{
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
	glUniform4f(uniformLocation, value.x, value.y, value.z, value.);
}

void Shader::uploadMat4(const char* name, const glm::mat4& value)
{
}

void Shader::compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
}
