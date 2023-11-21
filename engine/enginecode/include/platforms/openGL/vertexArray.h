/** \file vertexArray.h */
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "vertexBuffer.h"
#include "indexBuffer.h"

namespace Engine {
	/** \class VertexArray */
	class VertexArray {
		public:
			VertexArray(); //!< VertexArray constuctor
			~VertexArray(); //!< VertexArray destructor
			void bind();
			void unbind();
			inline uint32_t getID() const { return m_openGLID; }
			void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
			void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
			inline std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const { return m_vertexBuffers; }
			inline std::vector<std::shared_ptr<IndexBuffer>> getIndexBuffers() const { return m_indexBuffers; }
			inline uint32_t getDrawCount() const {};
	    private:
			std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
			std::vector<std::shared_ptr<IndexBuffer>> m_indexBuffers;
			uint32_t m_openGLID;
			uint32_t m_attributeIndex = 0;
	};
}

