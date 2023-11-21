/** \file indexBuffer.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

/** \class IndexBuffer */
class IndexBuffer {
	public:
		IndexBuffer(uint32_t* indeces, uint32_t count);
		~IndexBuffer();
		void bind();
		void unbind();
		inline uint32_t getID() const { return m_openGLID; }
		inline uint32_t getCount() const { return m_count; }
		void edit(uint32_t* indices, uint32_t count, uint32_t offset);
	private:
		uint32_t m_openGLID;
		uint32_t m_count;
};