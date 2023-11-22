/** \file myScene.h */
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "systems/log.h"

/** \class MyScene.h */
namespace Engine {
	class MyScene {
	public:
		MyScene();
	private:
		void createBuffers();
		void createShaders();
		void createTextures();
		void destroy();
		float cubeVertices[8 * 24] = {
			 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, 0.f,   0.f,  // Side 1
			 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, 0.f,   0.5f,
			-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f, 0.33f, 0.5f,
			-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f, 0.33f, 0.f,

			-0.5f, -0.5f,  0.5f,  0.f,  0.f,  1.f, 0.33f, 0.5f, // Side 2
			 0.5f, -0.5f,  0.5f,  0.f,  0.f,  1.f, 0.66f, 0.5f,
			 0.5f,  0.5f,  0.5f,  0.f,  0.f,  1.f, 0.66f, 0.f,
			-0.5f,  0.5f,  0.5f,  0.f,  0.f,  1.f, 0.33f, 0.f,

			-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, 1.f,	  0.f,  //Side 3
			 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f, 0.66f, 0.f,
			 0.5f, -0.5f,  0.5f,  0.f, -1.f,  0.f, 0.66f, 0.5f,
			-0.5f, -0.5f,  0.5f,  0.f, -1.f,  0.f, 1.f,   0.5f,

			 0.5f,  0.5f,  0.5f,  0.f,  1.f,  0.f, 0.f,   0.5f, //Side 4
			 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, 0.f,   1.f,
			-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f, 0.33f, 1.f,
			-0.5f,  0.5f,  0.5f,  0.f,  1.f,  0.f, 0.33f, 0.5f,

			-0.5f,  0.5f,  0.5f, -1.f,  0.f,  0.f, 0.66f, 0.5f, //Side 5
			-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f, 0.33f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f, 0.33f, 1.f,
			-0.5f, -0.5f,  0.5f, -1.f,  0.f,  0.f, 0.66f, 1.f,

			 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f, 1.f,   1.f,  //Side 6
			 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f, 1.f,   0.5f,
			 0.5f,  0.5f,  0.5f,  1.f,  0.f,  0.f, 0.66f, 0.5f,
			 0.5f, -0.5f,  0.5f,  1.f,  0.f,  0.f, 0.66f, 1.f

		};
		float pyramidVertices[6 * 16] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // Magenta square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f,  0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f,  0.5f, 0.8f, 0.2f, 0.8f,

			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.2f, // Green triangle
			-0.5f, -0.5f,  0.5f, 0.2f, 0.8f, 0.2f,
			 0.0f,  0.5f,  0.5f, 0.2f, 0.8f, 0.2f,

			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Red triangle
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.0f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

			 0.5f, -0.5f,  0.5f, 0.8f, 0.8f, 0.2f, // Yellow triangle
			 0.5f, -0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.0f,  0.5f,  0.5f, 0.8f, 0.8f, 0.2f,

			 0.5f, -0.5f, -0.5f, 0.0f, 0.2f, 1.0f, // Blue triangle
			-0.5f, -0.5f, -0.5f, 0.0f, 0.2f, 1.0f,
			 0.0f,  0.5f,  0.5f, 0.0f, 0.2f, 1.0f
		};
		uint32_t pyramidIndices[3 * 6] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};
		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};

		std::vector<glm::mat4> m_models;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		std::string FCVert, FCFrag;
		std::string TPVert, TPFrag;
		uint32_t FCProgram, TPProgram;
		uint32_t pyramidVAO, pyramidVBO, pyramidIBO;
		uint32_t cubeVAO, cubeVBO, cubeIBO;
		uint32_t letterTexture, numberTexture;
		int32_t width, height, channels;
	};
}

