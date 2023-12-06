/** \file bufferLayout.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "bufferElement.h"

/** \class BufferLayout */
class BufferLayout {
	public:
		BufferLayout(); //!< Default constructor
		BufferLayout(const std::initializer_list<BufferElement>& elements) : //!< BufferLayout constructor
			m_elements(elements) {
			calcStrideAndOffsets();
		};
		inline uint32_t getStride() { return m_stride; } //!< Getter method for the stride
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); } //!< Method for the start of the elements vector
		std::vector<BufferElement>::iterator end() { return m_elements.end(); } //!< Method for the end of the elements vector
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); } //!< Method for the start of the elements vector
			std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); } //!< Method for the end of the elements vector
	private:
		std::vector<BufferElement> m_elements; //!< Buffer elements vector attribute 
		uint32_t m_stride; //!< Stride attribute
		void calcStrideAndOffsets(); //!< Method to calculate the stride and offsets of the buffer
		uint32_t prevOffset = 0; //!< Attribute for the previous offset
		uint32_t offset; //!< Attribute for the current offset
};

BufferLayout TPLayout{ 
	{ShaderDataType::Float3},
	{ShaderDataType::Float3},
	{ShaderDataType::Float2}
};
