/** \file vertexBuffer.cpp */
#include "engine_pch.h"
#include "platforms/openGL/vertexBuffer.h"

namespace Engine {
	VertexBuffer::VertexBuffer(void* vertices, uint32_t size, BufferLayout layout) :
		m_layout(layout)
	{
		glCreateBuffers(1, &m_openGLID);
		glBindBuffer(GL_ARRAY_BUFFER, m_openGLID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_openGLID);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_openGLID);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::edit(void* vertices, uint32_t size, uint32_t offset)
	{
	}
}


