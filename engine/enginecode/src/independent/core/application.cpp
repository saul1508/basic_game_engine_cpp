/** \file application.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
	#include "platforms/windows/winTimer.h"
#endif

#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
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
		uint32_t pyramidVAO, pyramidVBO, pyramidIBO;
		uint32_t cubeVAO, cubeVBO, cubeIBO;
		uint32_t letterTexture, numberTexture;
		int32_t width, height, channels;


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

		FCVert = R"(
		#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexColour;
				out vec3 fragmentColour;
				uniform mat4 u_model;
				uniform mat4 u_view;
				uniform mat4 u_projection;
				void main()
				{
					fragmentColour = a_vertexColour;
					gl_Position =  u_projection * u_view * u_model * vec4(a_vertexPosition,1);
				}
	)";

		FCFrag = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 fragmentColour;
				void main()
				{
					colour = vec4(fragmentColour, 1.0);
				}

	)";

		TPVert = R"(
		#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexNormal;
				layout(location = 2) in vec2 a_texCoord;
				out vec3 fragmentPos;
				out vec3 normal;
				out vec2 texCoord;
				uniform mat4 u_model;
				uniform mat4 u_view;
				uniform mat4 u_projection;
				void main()
				{
					fragmentPos = vec3(u_model * vec4(a_vertexPosition, 1.0));
					normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
					texCoord = vec2(a_texCoord.x, a_texCoord.y);
					gl_Position =  u_projection * u_view * u_model * vec4(a_vertexPosition,1.0);
				}
		)";
		////
		TPFrag = R"(
		#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 normal;
				in vec3 fragmentPos;
				in vec2 texCoord;
				uniform vec3 u_lightPos; 
				uniform vec3 u_viewPos; 
				uniform vec3 u_lightColour;
				uniform sampler2D u_texData;
				void main()
				{
					float ambientStrength = 0.4;
					vec3 ambient = ambientStrength * u_lightColour;
					vec3 norm = normalize(normal);
					vec3 lightDir = normalize(u_lightPos - fragmentPos);
					float diff = max(dot(norm, lightDir), 0.0);
					vec3 diffuse = diff * u_lightColour;
					float specularStrength = 0.8;
					vec3 viewDir = normalize(u_viewPos - fragmentPos);
					vec3 reflectDir = reflect(-lightDir, norm);  
					float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
					vec3 specular = specularStrength * spec * u_lightColour;  
					
					colour = vec4((ambient + diffuse + specular), 1.0) * texture(u_texData, texCoord);
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
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));
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
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));
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
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

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
			GLint maxLength = 2048;

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPVertShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));
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
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

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
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(TPProgram);
			glDeleteShader(TPVertShader);
			glDeleteShader(TPFragShader);
			return;
		}

		glDetachShader(TPProgram, TPVertShader);
		glDetachShader(TPProgram, TPFragShader);

		m_view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		m_projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		m_models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		m_models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		m_models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glUseProgram(FCProgram);
		glBindVertexArray(pyramidVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);

		GLuint uniformLocation;

		uniformLocation = glGetUniformLocation(FCProgram, "u_model");;
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[0]));

		uniformLocation = glGetUniformLocation(FCProgram, "u_view");;
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_view));

		uniformLocation = glGetUniformLocation(FCProgram, "u_projection");;
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_projection));

		glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);
	

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
			Log::info("ts {}", timeStep);
			//accumulatedTime += timeStep;



			//Log::trace("Hello World! {0} {1}", 42, "I am a string");
			//Log::trace("FPS {0} {1}", 1.0f / timeStep,  accumulatedTime);
			//Log::trace("{0}", RandNumGenerator::normalInt(10.f, 2.5f));
			//Log::trace("{0}", RandNumGenerator::uniformIntBetween(-10, 10));

			/*if (accumulatedTime > 3000.0f) {


			}*/

			if (InputPoller::isKeyPressed(NG_KEY_ESCAPE)) {
				m_running = false;
			}

			// Do frame stuff
			for (auto& model : m_models) { model = glm::rotate(model, timeStep, glm::vec3(0.f, 1.0, 0.f)); }

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(FCProgram);
			glBindVertexArray(pyramidVAO);

			GLuint uniformLocation;

			uniformLocation = glGetUniformLocation(FCProgram, "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[0])); // Must include <glm/gtc/type_ptr.hpp>

			uniformLocation = glGetUniformLocation(FCProgram, "u_view");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_view));

			uniformLocation = glGetUniformLocation(FCProgram, "u_projection");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_projection));

			glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);

			glUseProgram(TPProgram);
			glBindVertexArray(cubeVAO);

			uniformLocation = glGetUniformLocation(TPProgram, "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[1]));

			uniformLocation = glGetUniformLocation(TPProgram, "u_view");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_view));

			uniformLocation = glGetUniformLocation(TPProgram, "u_projection");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_projection));

			uniformLocation = glGetUniformLocation(TPProgram, "u_lightColour");
			glUniform3f(uniformLocation, 1.f, 1.f, 1.f);

			uniformLocation = glGetUniformLocation(TPProgram, "u_lightPos");
			glUniform3f(uniformLocation, 1.f, 4.f, 6.f);

			uniformLocation = glGetUniformLocation(TPProgram, "u_viewPos");
			glUniform3f(uniformLocation, 0.f, 0.f, 0.f);

			uniformLocation = glGetUniformLocation(TPProgram, "u_texData");
			glUniform1i(uniformLocation, 0);

			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

			uniformLocation = glGetUniformLocation(TPProgram, "u_model");
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_models[2]));

			uniformLocation = glGetUniformLocation(TPProgram, "u_texData");
			glUniform1i(uniformLocation, 1);

			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

			m_window->onUpdate(timeStep);
		}

		glDeleteVertexArrays(1, &pyramidVAO);
		glDeleteBuffers(1, &pyramidVBO);
		glDeleteBuffers(1, &pyramidIBO);

		glDeleteVertexArrays(1, &cubeVAO);
		glDeleteBuffers(1, &cubeVBO);
		glDeleteBuffers(1, &cubeIBO);

		glDeleteProgram(FCProgram);
		glDeleteProgram(TPProgram);

		glDeleteTextures(1, &letterTexture);
		glDeleteTextures(1, &numberTexture);
	}


}
