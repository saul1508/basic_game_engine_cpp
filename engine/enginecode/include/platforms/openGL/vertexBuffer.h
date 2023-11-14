/** \file vertexBuffer.h */
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

/** \class VertexBuffer */
class VertexBuffer {
	public:
		VertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); //!< Constructor for VertexBuffer+
		~VertexBuffer(); //!< Destructor for VertexBuffer
		void bind(); //!< Method to bind the vertex buffer
		void unbind(); //!< Method to unbind the vertex buffer
		void edit(); //!< Method to edit 
		inline uint32_t getID() const {} //!< Inline getter method for the ID
	private:
		uint32_t mOpenGLID; //!< Render ID attribute
		VertexBufferLayout m_layout; //!< Buffer layout attribute
};