#include "engine_pch.h"
#include "./include/platforms/openGL/bufferLayout.h"

void BufferLayout::calcStrideAndOffsets()
{
	for (int i = 0; i < m_elements.size(); i++) {
		m_elements[i].m_offset = prevOffset;
		prevOffset += m_elements[i].m_size;
	}
	m_stride = prevOffset;
}
