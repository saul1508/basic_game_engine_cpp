/** \file bufferElement.h */
#pragma once
#include "shaderDataTypes.h"

/** \class BufferElement */
class BufferElement {
	public:
		BufferElement(); //!< Default Constructor
		BufferElement(ShaderDataType dataType, bool normalised = false) : //!< BufferElement constuctor
			m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_normalised(normalised) {};
		ShaderDataType m_dataType; //!< Data type attribute
		uint32_t m_size; //!< Buffer size attribute;
		uint32_t m_offset; //!< Buffer offset attribute
		bool m_normalised; //!< Normalised attribute
		
};