/** \file vertexArray.cpp */
#include "engine_pch.h"
#include "platforms/openGL/vertexArray.h"
#include "systems/log.h"

namespace Engine {
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_openGLID);
		glBindVertexArray(m_openGLID);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_openGLID);
	}
	void VertexArray::bind()
	{
		glBindVertexArray(m_openGLID);
	}
	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
	void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		m_vertexBuffers.push_back(vertexBuffer);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		auto& layout = vertexBuffer->getLayout();
		auto normalised = GL_FALSE;
		for (auto& element : layout) {
			if (element.m_normalised) normalised = GL_TRUE; else normalised = GL_FALSE;
			glEnableVertexAttribArray(m_attributeIndex);
			glVertexAttribPointer(m_attributeIndex, DataTypeComponentCount(element.m_dataType), ShaderDataTypeOpenGLType(element.m_dataType), normalised, layout.getStride(), (void*)element.m_offset);
			Log::info("Layout: {} {} {} {} {} {}", m_attributeIndex, DataTypeComponentCount(element.m_dataType), ShaderDataTypeOpenGLType(element.m_dataType), element.m_normalised, layout.getStride(), element.m_offset);
			m_attributeIndex++;
		}
	}
	void VertexArray::addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_indexBuffers = indexBuffer;
	}
}