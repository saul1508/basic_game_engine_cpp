/** \file myScene.cpp */
#include "engine_pch.h"
#include "platforms/openGL/myScene.h"
//#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "systems/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

MyScene::MyScene() {
	
}

void MyScene::createBuffers() {
	// Pyramid
	glCreateVertexArrays(1, &pyramidVAO);
	glBindVertexArray(pyramidVAO);

	glCreateBuffers(1, &pyramidVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

	glCreateBuffers(1, &pyramidIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndices), pyramidIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Cube
	glCreateVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	glCreateBuffers(1, &cubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glCreateBuffers(1, &cubeIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void MyScene::createShaders() {

	FCVert = R"(
		#version 440 core
		
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec3 aCol;

		uniform mat4 uModel;
		uniform mat4 uView;
		uniform mat4 uProjection;
				
		out vec3 fragColour;

		void main() {
			fragColour = aCol;
			gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
		}
	)";

	FCFrag = R"(
		#version 440 core

		layout(location = 0) out vec4 colour;
		
		in vec3 fragColour;

		void main() {
			colour = vec4(fragColour, 1.0f);
		}

	)";

	TPVert = R"(
		#version 440 core

		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec3 aNorm;
		layout(location = 2) in vec2 aTex;
		
		uniform mat4 uModel;
		uniform mat4 uView;
		uniform mat4 uProjection;
				
		out vec3 position;
		out vec3 normal;
		out vec3 tex;
		
		void main() {
			position = vec3(uModel * vec4(aPos, 1.0f));
			normal = mat3(transpose(inverse(uModel))) * aNorm;
			tex = vec2(aTex.x, aTex.y);
			gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
		}
		
	)";
	////
	TPFrag = R"(
		#version 440 core
		
		layout(position = 0) put vec4 colour;
		
		uniform vec3 uLightPos;
		uniform vec3 uViewPos;
		uniform vec3 uLightCol;
		uniform sampler2D uTexData;
		
		in vec3 normal;
		in vec3 position;
		in vec3 tex;

		void main() {
			float ambientStrength = 0.4f;
			vec3 ambient = ambientStrength * uLightCol;
			vec3 norm = normalize(normal);
			vec3 lightDir = normalize(uLightPos - position);
			float diff = max(dot(norm, lightDir), 0.0f);
			vec3 diffuse = diff * uLightCol;
			float specularStrength = 0.8f;
			vec3 viewDir = normalize(uViewPos - position);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
			vec3 specular = specularStrength * spec * uLightCol;

			colour = vec4((ambient + diffuse + specular), 1.0f) * texture(uTexData, tex);	
		}
	)";

	// Pyramid
	GLuint FCVertShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = FCVert.c_str();
	glShaderSource(FCVertShader, 1, &source, 0);
	glCompileShader(FCVertShader);

	GLint isCompiled = 0;
	glGetShaderiv(FCVertShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(FCVertShader, maxLength, &maxLength, &infoLog[0]);
		//Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));
		glDeleteShader(FCVertShader);
		return;
	}

	GLuint FCFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = FCFrag.c_str();
	glShaderSource(FCFragShader, 1, &source, 0);
	glCompileShader(FCFragShader);

	isCompiled = 0;
	glGetShaderiv(FCFragShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(FCFragShader, maxLength, &maxLength, &infoLog[0]);
		//Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

		glDeleteShader(FCVertShader);
		return;
	}

	FCProgram = glCreateProgram();
	glAttachShader(FCProgram, FCVertShader);
	glAttachShader(FCProgram, FCFragShader);
	glLinkProgram(FCProgram);

	GLint isLinked = 0;
	glGetProgramiv(FCProgram, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(FCProgram, maxLength, &maxLength, &infoLog[0]);
		//Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

		glDeleteProgram(FCProgram);
		glDeleteShader(FCVertShader);
		glDeleteShader(FCFragShader);
		return;
	}

	//Cube
	GLuint TPVertShader = glCreateShader(GL_VERTEX_SHADER);

	source = TPVert.c_str();
	glShaderSource(TPVertShader, 1, &source, 0);
	glCompileShader(TPVertShader);

	isCompiled = 0;
	glGetShaderiv(TPVertShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(TPVertShader, maxLength, &maxLength, &infoLog[0]);
		//Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));
		glDeleteShader(TPVertShader);
		return;
	}

	GLuint TPFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = TPFrag.c_str();
	glShaderSource(TPFragShader, 1, &source, 0);
	glCompileShader(TPFragShader);

	isCompiled = 0;
	glGetShaderiv(TPFragShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(TPFragShader, maxLength, &maxLength, &infoLog[0]);
		//Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

		glDeleteShader(TPFragShader);
		return;
	}

	TPProgram = glCreateProgram();
	glAttachShader(TPProgram, TPVertShader);
	glAttachShader(TPProgram, TPFragShader);
	glLinkProgram(TPProgram);

	isLinked = 0;
	glGetProgramiv(TPProgram, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(TPProgram, maxLength, &maxLength, &infoLog[0]);
		//Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

		glDeleteProgram(TPProgram);
		glDeleteShader(TPVertShader);
		glDeleteShader(TPFragShader);
		return;
	}

	glDetachShader(TPProgram, TPVertShader);
	glDetachShader(TPProgram, TPFragShader);

	//m_models[0] = glm::mat4(1.0f);
	//m_view = glm::mat4(1.0f);
	//m_projection = glm::mat4(1.0f);

	//glUseProgram(FCProgram);
	//glBindVertexArray(pyramidVAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);

	//GLuint uniformLocation;

	//uniformLocation = glGetUniformLocation(FCProgram, "u_model");;
	//glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[0]));

	//uniformLocation = glGetUniformLocation(FCProgram, "u_view");;
	//glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	//uniformLocation = glGetUniformLocation(FCProgram, "u_projection");;
	//glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

	//glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);
}

void MyScene::createTextures() {
	glGenTextures(1, &letterTexture);
	glBindTexture(GL_TEXTURE_2D, letterTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load("assets/textures/letterCube.png", &width, &height, &channels, 0);
	if (data) {
		if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		return;
	}

	stbi_image_free(data);


	glGenTextures(1, &numberTexture);
	glBindTexture(GL_TEXTURE_2D, numberTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("assets/textures/numberCube.png", &width, &height, &channels, 0);
	if (data) {
		if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		return;
	}

	stbi_image_free(data);
}

void MyScene::destroy() {
	glDeleteVertexArrays(1, &pyramidVAO);
	glDeleteBuffers(1, &pyramidVBO);
	glDeleteBuffers(1, &pyramidIBO);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &cubeIBO);

	glDeleteShader(FCProgram);
	glDeleteShader(TPProgram);

	glDeleteTextures(1, &letterTexture);
	glDeleteTextures(1, &numberTexture);

}
