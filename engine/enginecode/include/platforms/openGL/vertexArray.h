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
			VertexArray(); //!< VertexArray default constuctor
			~VertexArray(); //!< VertexArray destructor
			void bind(); //!< Method to bind the vertex array
			void unbind(); //!< Method to unbind the vertex array
			inline uint32_t getID() const { return m_openGLID; } //!< Getter method for the OpenGL ID
			void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer); //!< Method to add a vertex buffer to the vertex array
			void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer); //!< Method to add an index buffer to the vertex array
			inline std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const { return m_vertexBuffers; } //!< Getter method for vertex buffers
			inline std::shared_ptr<IndexBuffer> getIndexBuffers() const { return m_indexBuffers; } //!< Getter method for index buffers
			inline uint32_t getDrawCount() const { return m_indexBuffers->getCount(); } //!< Getter method for the draw count
	    private:
			std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers; //!< Vector attribute for the vertex buffers
			std::shared_ptr<IndexBuffer> m_indexBuffers; //!< Vector attribute for the index buffers
			uint32_t m_openGLID; //!< OpenGL ID attribute
			uint32_t m_attributeIndex = 0; //!< Attribute index attribute
	};
}

