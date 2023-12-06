/** \file indexBuffer.cpp */
#include "engine_pch.h"
#include "platforms/openGL/indexBuffer.h"

namespace Engine {
	IndexBuffer::IndexBuffer(uint32_t* indeces, uint32_t count) :
		m_count(count)
	{
		glCreateBuffers(1, &m_openGLID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_openGLID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indeces, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_openGLID);
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_openGLID);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::edit(uint32_t* indices, uint32_t count, uint32_t offset)
	{

	}

}

