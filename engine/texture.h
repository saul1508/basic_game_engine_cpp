/** \file texture.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
/** \class Texture */
class Texture {
	public:
		Texture(const char* filepath, uint32_t slot = 0); //!< Constrictor taking in a filepath
		Texture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot = 0); //!< Overloaded constructor
		~Texture(); //!< Texture destuctor
		void bindToSlot(uint32_t slot); //!< Method to bind the current texture
		void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data); //!< Method to edit the current texture
		inline uint32_t getID() { return m_openGLID; } //!< Getter method for the openGL ID
		inline uint32_t getWidth() { return m_width; } //!< Getter method for the width of the texture as an integer
		inline uint32_t getHeight() { return m_height; } //!< Getter method for the height of the texture as an integer
		inline uint32_t getWidthF() { return static_cast<float>(m_height); } //!< Getter method for the height of the texture as a float
		inline uint32_t getHeightF() { return static_cast<float>(m_width); } //!< Getter method for the width of the texture as a float
		inline uint32_t getChannels() { return m_channels; } //!< Getter method for the texture channels
	private:
		uint32_t m_openGLID; //!< OpenGL ID attribute
		uint32_t m_width; //!< Texture width attribute
		uint32_t m_height; //!< Texture height attribute
		uint32_t m_channels; //!< Texture channels attribute
		void init(uint32_t width, uint32_t height, uint32_t channels, char* data, uint32_t slot); //!< Method to initialise a texture
};
