/** \file vertexBuffer.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "platforms/openGL/bufferLayout.h"

namespace Engine {
	/** \class VertexBuffer */
	class VertexBuffer {
	public:
		VertexBuffer(void* vertices, uint32_t size, BufferLayout layout); //!< Constructor for VertexBuffer+
		~VertexBuffer(); //!< Destructor for VertexBuffer
		void bind(); //!< Method to bind the vertex buffer
		void unbind(); //!< Method to unbind the vertex buffer
		void edit(void* vertices, uint32_t size, uint32_t offset); //!< Method to edit 
		inline uint32_t getID() const { return m_openGLID; } //!< Inline getter method for the ID
		inline const BufferLayout& getLayout() const { return m_layout; }
	private:
		uint32_t m_openGLID; //!< Render ID attribute
		BufferLayout m_layout; //!< Buffer layout attribute
	};
}