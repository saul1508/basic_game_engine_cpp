/** \file bufferLayout.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "bufferElement.h"

/** \class BufferLayout */
class BufferLayout {
	public:
		BufferLayout();
		BufferLayout(const std::initializer_list<BufferElement>& elements) :
			m_elements(elements) {
			calcStrideAndOffsets();
		};
		inline uint32_t getStride() { return m_stride; }
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;
		void calcStrideAndOffsets();
		uint32_t prevOffset = 0;
		uint32_t offset;
};

BufferLayout TPLayout{
	{ShaderDataType::Float3},
	{ShaderDataType::Float3},
	{ShaderDataType::Float2}
};
