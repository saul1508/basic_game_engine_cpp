///** \file renderer3D.h */
//#pragma once
//#include "platforms/openGL/vertexArray.h"
//#include "rendering/material.h"
//#include "rendering/renderCommon.h"
//#include <memory>
//
//namespace Engine {
//	/** \class Renderer3D
//	* Renders a 3D Scene
//	*/
//	class Renderer3D {
//		public:
//			static void init(); //!< Method to initialise the renderer data
//			static void begin(const Engine::SceneWideUniforms& swu); //!< Method to begin a new scene
//			//! Submit an item for rendering
//			/*!
//				\param geometry - The vertices and indices to be rendered
//				\param material - The material which describes how the geometry should be rendered
//				\param modelMat - The transform matrix where the geometry will be rendered
//			*/
//			static void submit(const std::shared<VertexArray>& geometry, const Material&, const glm::mat4& modelMat); //!< Method to send data to be drawn
//			static void end(); //!< Method to end the current scene
//		private:
//			/*! \struct A set of internal variables to the renderer*/
//			struct internalData {
//				Engine::SceneWideUniforms swu;
//			};
//			inline static std::shared_ptr<internalData> s_data; //!< Attribute for the data internal to the renderer
//	};
//}
