///** \file material.h */
//#pragma once
//#include <memory>
//#include "platforms/openGL/shader.h"
//
//	/** \class Material 
//	*	\brief Holds a shader band the uniform data associated with that shader
//	*/
//	class Material {
//		public:
//			Material() = delete; //!< Deleted default constructor as all materials will need a shader
//			Material(const std::shared_ptr<Engine::Shader>& shader) : //!< Constuctor with shader only
//				m_shader(shader), m_flags(0), m_tint(glm::vec4(0.f)) {}
//			Material(const std::shared_ptr<Engine::Shader>& shader, const glm::vec4& tint) : //!< Constructor with shader and tint
//				m_shader(shader), m_tint(tint) {
//				setFlag(flag_tint);
//			}
//			inline std::shared_ptr<Engine::Shader> getShader() const { return m_shader; } //!< Getter method for the shader
//			inline glm::f32vec4 getTint() const { return m_tint; } //!< Getter method for the tint
//			bool isFlagSet(uint32_t flag) const { return m_flags & flag; } //!< Merhod to check if the flag has been set
//			void setTint(const glm::vec4& tint) { m_tint = tint; } //!< Setter method for the tint;
//
//			constexpr static uint32_t flag_texture = 1 << 0;
//			constexpr static uint32_t flag_tint = 1 << 1;
//		private: 
//			uint32_t m_flags = 0; //!< Bitfield representation for the shader settings attribute
//			std::shared_ptr<Engine::Shader> m_shader; //!< Material shader attribute
//			glm::vec4 m_tint; //!< Material tint attribute
//			void setFlag(uint32_t flag) { m_flags = m_flags | flag; } //!< Internal method to set the flag
//
//
