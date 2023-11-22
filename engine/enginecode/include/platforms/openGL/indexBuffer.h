/** \file indexBuffer.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

/** \class IndexBuffer */
class IndexBuffer {
	public:
		IndexBuffer(uint32_t* indeces, uint32_t count); //!< Index Buffer constructor
		~IndexBuffer(); //!< Index Buffer destructor
		void bind(); //!< Method to bind the index buffer
		void unbind(); //!< Method to unbind the index buffer
		inline uint32_t getID() const { return m_openGLID; } //!< Getter method for the openGL ID
		inline uint32_t getCount() const { return m_count; } //!< Getter method got the index buffer count
		void edit(uint32_t* indices, uint32_t count, uint32_t offset); //!< Method to edit the index buffer
	private:
		uint32_t m_openGLID; //!< OpenGL ID attribute
		uint32_t m_count; //!< Count attribute
};