/** \file application.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#include <filesystem>
#include "platforms/openGL/vertexArray.h"
#include "platforms/openGL/bufferLayout.h"
#ifdef NG_PLATFORM_WINDOWS
	#include "platforms/windows/winTimer.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "platforms/openGL/vertexArray.h"
#include "platforms/openGL/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr) {
			s_instance = this;
		}

		// Start systems
		// Start logger
		m_log.reset(new Log);
		m_log->start();

		//Start random number system
		m_randNumSystem.reset(new RandNumGenerator);
		m_randNumSystem->start();

		// Start timer system
//#ifdef NG_PLATFORM_WINDOWS
//		m_timer.reset(new WinTimer);
//#else
		m_timer.reset(new ChronoTimer);
//#endif
		m_timer->start();

		// Start glfw system
		m_glfwSystem.reset(new GLFWSystem);
		m_glfwSystem->start();

		m_winProp.title = "My Window";
		m_window.reset(new Window(m_winProp));

		// Setup callbacks
		m_window->getEventHandler().setOnWindowClose([this](WindowCloseEvent& e) {this->onWindowClose(e);});
		m_window->getEventHandler().setOnWindowResize([this](WindowResizeEvent& e) {this->onWindowResize(e);});
		m_window->getEventHandler().setOnWindowFocus([this](WindowFocusEvent& e) {this->onWindowFocus(e);});
		m_window->getEventHandler().setOnWindowLose([this](WindowLoseFocusEvent& e) {this->onWindowLoseFocus(e);});
		m_window->getEventHandler().setOnWindowMove([this](WindowMoveEvent& e) { this->onWindowMove(e);});
		m_window->getEventHandler().setOnMouseButtonPress([this](MouseButtonPressEvent& e) {this->onMouseButtonPress(e);});
		m_window->getEventHandler().setOnMouseButtonRelease([this](MouseButtonReleaseEvent& e) {this->onMouseButtonRelease(e);});
		m_window->getEventHandler().setOnMouseMove([this](MouseMoveEvent& e) {this->onMouseMove(e);});
		m_window->getEventHandler().setOnMouseScroll([this](MouseScrollEvent& e) {this->onMouseScroll(e);});
		m_window->getEventHandler().setOnKeyPress([this](KeyPressEvent& e) {this->onKeyPress(e);});
		m_window->getEventHandler().setOnKeyRelease([this](KeyReleaseEvent& e) {this->onKeyRelease(e);});
		m_window->getEventHandler().setOnKeyType([this](KeyTypeEvent& e) {this->onKeyType(e);});

		// Set input poller
		InputPoller::setNativeWindow(m_window->getNativeWindow());

	}

	Application::~Application()
	{
		// Stop systems
		//Stop random number system
		m_randNumSystem->stop();
		//Stop logger
		m_log->stop();
		//Stop glfw system
		m_glfwSystem->stop();
	}

	void Application::onWindowClose(WindowCloseEvent& e) {
		Log::trace("Closing application");
		m_running = false;
		e.handle(true);
	}
	void Application::onWindowResize(WindowResizeEvent& e) {
		Log::trace("Resized window to {0} by {1}", e.getWidth(), e.getHeight());
		e.handle(true);
	}
	void Application::onWindowFocus(WindowFocusEvent& e) {
		Log::trace("Focussed window");
		e.handle(true);
	}
	void Application::onWindowLoseFocus(WindowLoseFocusEvent& e) {
		Log::trace("Unfocussed window");
		e.handle(true);
	}
	void Application::onWindowMove(WindowMoveEvent& e) {
		Log::trace("Moved window to x:{0}, y:{1}", e.getNewXPos(), e.getNewYPos());
		e.handle(true);
	}
	void Application::onKeyPress(KeyPressEvent& e) {
		Log::trace("{0} key pressed {1} times", e.getKeyCode(), e.getRepeatCount());
		e.handle(true);
	}
	void Application::onKeyRelease(KeyReleaseEvent& e) {
		Log::trace("{0} key released", e.getKeyCode());
		e.handle(true);
	}
	void Application::onKeyType(KeyTypeEvent& e) {
		Log::trace("{0} key typed", e.getKeyCode());
		e.handle(true);
	}
	void Application::onMouseButtonPress(MouseButtonPressEvent& e) {
		Log::trace("Mouse button {0} pressed", e.getButton());
		e.handle(true);
	}
	void Application::onMouseButtonRelease(MouseButtonReleaseEvent& e) {
		Log::trace("Mouse button {0} released", e.getButton());
		e.handle(true);
	}
	void Application::onMouseScroll(MouseScrollEvent& e) {
		Log::trace("Mouse scrolled to an offset of {0}", e.getOffset());
		e.handle(true);
	}
	void Application::onMouseMove(MouseMoveEvent& e) {
		Log::trace("Mouse moved to x:{0} y:{1}", e.getNewXPos(), e.getNewYPos());
		e.handle(true);
	}

	void Application::run()
	{
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
			//	 <------ Pos ------>  <--- colour ---> 
			-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
			 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

			-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
			-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
			 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
			 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

			 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
			 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
			 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

			 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
			-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
			 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		};

		uint32_t pyramidIndices[3 * 6] =
		{
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

		std::vector<glm::mat4> m_models(3);
		glm::mat4 m_view;
		glm::mat4 m_projection;
		std::string FCVert, FCFrag;
		std::string TPVert, TPFrag;
		uint32_t FCProgram, TPProgram;
		uint32_t letterTexture, numberTexture;
		int32_t width, height, channels;

		BufferLayout TPLayout{
			{ShaderDataType::Float3},
			{ShaderDataType::Float3},
			{ShaderDataType::Float2}
		};

		BufferLayout FCLayout{
			{ShaderDataType::Float3},
			{ShaderDataType::Float3},
		};

		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<IndexBuffer> pyramidIBO;
		std::shared_ptr<VertexBuffer> pyramidVBO;

		pyramidVAO.reset(new VertexArray);
		pyramidVBO.reset(new VertexBuffer(pyramidVertices, sizeof(pyramidVertices), FCLayout));
		pyramidIBO.reset(new IndexBuffer(pyramidIndices, 3 * 6));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->addIndexBuffer(pyramidIBO);

		pyramidVAO->unbind();
		pyramidIBO->unbind();
		pyramidVBO->unbind();
		
		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<IndexBuffer> cubeIBO;
		std::shared_ptr<VertexBuffer> cubeVBO;

		cubeVAO.reset(new VertexArray);
		cubeVBO.reset(new VertexBuffer(cubeVertices, sizeof(cubeVertices), TPLayout));
		cubeIBO.reset(new IndexBuffer(cubeIndices, 3 * 12));

		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->addIndexBuffer(cubeIBO);

		cubeVAO->unbind();
		cubeVBO->unbind();
		cubeIBO->unbind();

		std::shared_ptr<Shader> flatColourShader;
		std::shared_ptr<Shader> texturedPhongShader;
		//flatColourShader.reset(new Shader("./assets/shaders/flatColour.glsl"));
		flatColourShader.reset(new Shader("./assets/shaders/flatColour.vert", "./assets/shaders/flatColour.frag"));
		texturedPhongShader.reset(new Shader("./assets/shaders/texturedPhong.vert", "./assets/shaders/texturedPhong.frag"));

		m_view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		m_projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		glm::vec3 pos(-2.f, 0.f, -6.f);
		float rot = 0.f;

		m_models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		m_models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

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
		}
		else {
			return;
		}

		stbi_image_free(data);

		glGenTextures(1, &numberTexture);
		glActiveTexture(GL_TEXTURE0 + 1);
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

		float timeStep = 0.f;
		float accumulatedTime = 0.0f;

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		while (m_running)
		{
			timeStep = m_timer->getElapsedTime();
			m_timer->reset();

			if (InputPoller::isKeyPressed(NG_KEY_ESCAPE)) m_running = false;

			if (InputPoller::isKeyPressed(NG_KEY_LEFT)) pos.x -= timeStep;
			if (InputPoller::isKeyPressed(NG_KEY_RIGHT)) pos.x += timeStep;
			if (InputPoller::isKeyPressed(NG_KEY_UP)) pos.y += timeStep;
			if (InputPoller::isKeyPressed(NG_KEY_DOWN)) pos.y -= timeStep;

			if (InputPoller::isKeyPressed(NG_KEY_J)) rot -= timeStep;
			if (InputPoller::isKeyPressed(NG_KEY_L)) rot += timeStep;

			m_models[0] = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.f, 1.f, 0.f));
			m_models[1] = glm::rotate(m_models[1], timeStep, glm::vec3(0.f, 1.0, 0.f));
			m_models[2] = glm::rotate(m_models[2], timeStep, glm::vec3(0.f, 1.0, 0.f));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(flatColourShader->getID());
			pyramidVAO->bind();
			pyramidIBO->bind();

			GLuint uniformLocation;

			uniformLocation = glGetUniformLocation(flatColourShader->getID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[0])); // Must include <glm/gtc/type_ptr.hpp>

			uniformLocation = glGetUniformLocation(flatColourShader->getID(), "u_view");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_view));

			uniformLocation = glGetUniformLocation(flatColourShader->getID(), "u_projection");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_projection));

			glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			glUseProgram(texturedPhongShader->getID());
			cubeVAO->bind();
			cubeIBO->bind();

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[1]));

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_view");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_view));

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_projection");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_projection));

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_lightColour");
			glUniform3f(uniformLocation, 1.f, 1.f, 1.f);

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_lightPos");
			glUniform3f(uniformLocation, 1.f, 4.f, 6.f);

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_viewPos");
			glUniform3f(uniformLocation, 0.f, 0.f, 0.f);

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_texData");
			glUniform1i(uniformLocation, 0);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[2]));

			uniformLocation = glGetUniformLocation(texturedPhongShader->getID(), "u_texData");
			glUniform1i(uniformLocation, 1);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			m_window->onUpdate(timeStep);
		}

		glDeleteTextures(1, &letterTexture);
		glDeleteTextures(1, &numberTexture);
	}


}
