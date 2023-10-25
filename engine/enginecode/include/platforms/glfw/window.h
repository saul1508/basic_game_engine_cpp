/** \file window.h */
#pragma once
#include "events/eventHandler.h"
#include "platforms/glfw/graphicsContext.h"

namespace Engine {
	/** \struct WindowProperties
	* Data required to initialise the window
	*/

	struct WindowProperties {
		char* title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVSync;

		WindowProperties(char* title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false, bool vsync = false) :
			title(title), width(width), height(height), isFullScreen(fullscreen), isVSync(vsync)
		{}
	};

	/** \class Window
	* GLFW window implementation
	*/

	class Window {
		public:
			Window() = delete; //!< No default constructor use case
			Window(const WindowProperties& properties); //!< Window constructor 
			void close(); //!< Method for when the window is closed
			void onUpdate(float timeStep); //!< Method for when the window is updated
			void setVSync(bool vSync); //!< Setter method for vSync
			uint32_t getWidth() { return m_winProps.width; } //!< Getter method for the width
			uint32_t getHeight() { return m_winProps.height; } //!< Getter methof for the height
			GLFWwindow* getNativeWindow() const { return m_native; } //!< Getter method for a pointer to the native GLFW window		
			bool isFullScreenMode() const { return m_winProps.isFullScreen; } //!< Method for whether the window is fullscreen
			bool isVSync() const { return m_winProps.isVSync;  } //!< Method for whether vSync is being used

			inline EventHandler& getEventHandler() { return m_handler; } //!< Inline getter method for the event handl
		protected:
			EventHandler m_handler; //!< Attribute for the event handler
			GLFWwindow* m_native; //!< Attribute for the native GLFW window
			WindowProperties m_winProps; //!< Attribute for window properties
			std::shared_ptr<GraphicsContext> m_graphicsContext; //!< Attribute fore the GLFW graphics context
			float m_aspectRatio; //!< Attribute for the aspect ratio
	};
}


