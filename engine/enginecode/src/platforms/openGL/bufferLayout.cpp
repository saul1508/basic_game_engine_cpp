#include "engine_pch.h"
#include "./include/platforms/openGL/bufferLayout.h"

void BufferLayout::calcStrideAndOffsets()
{
	for (int i = 0; i < m_elements.size(); i++) {
		offset = i * prevOffset;
		prevOffset += sizeof(float);
	}
	m_stride = prevOffset;
}
