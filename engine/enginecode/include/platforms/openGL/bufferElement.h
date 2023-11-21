/** \file bufferElement.h */
#pragma once
#include "shaderDataTypes.h"

/** \class BufferElement */
class BufferElement {
	public:
		BufferElement();
		BufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_normalised(normalised) {};
		ShaderDataType m_dataType;
		uint32_t m_size;
		uint32_t m_offset;
		bool m_normalised;
		
};