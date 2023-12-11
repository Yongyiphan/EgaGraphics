#include "Buffer.h"

namespace GL_Graphics {

				template<typename T>
				inline BufferLayoutElement<T>::BufferLayoutElement() {
								GetSpecs();
				}

				template<typename T>
				inline BufferLayoutElement<T>::BufferLayoutElement(const std::string& p_name, bool p_IsInstanced,
								size_t p_reserve) {
								m_Name = p_name;
								m_IsInstanced = p_IsInstanced;
								if (p_reserve > 0) {
												m_Data.reserve(p_reserve);
								}
								GetSpecs();
				}

				template<typename T>
				inline BufferLayoutElement<T>::BufferLayoutElement(
								const std::string& p_name,
								std::vector<T> rhs, bool p_IsInstanced,
								size_t p_reserve
				) {

								m_Name = p_name;
								m_Data = rhs;
								if (p_reserve > 0) {
												m_Data.reserve(p_reserve);
								}
								m_IsInstanced = p_IsInstanced;
								GetSpecs();
				}

				template<typename T>
				inline BufferLayoutElement<T>::~BufferLayoutElement() {
								m_Data.clear();
				}


				template <>
				inline void BufferLayoutElement<glm::vec2>::GetSpecs() {
								m_DataSize = sizeof(glm::vec2);
								m_SubElementCount = 2;
				}

				template <>
				inline void BufferLayoutElement<glm::vec3>::GetSpecs() {
								m_DataSize = sizeof(glm::vec3);
								m_SubElementCount = 3;
				}

				template <>
				inline void BufferLayoutElement<glm::vec4>::GetSpecs() {
								m_DataSize = sizeof(glm::vec4);
								m_SubElementCount = 4;
				}

				template<>
				inline void BufferLayoutElement<glm::mat3>::GetSpecs() {
								m_DataSize = sizeof(glm::mat3);
								m_SubElementCount = 3;
								m_Dimensions = 3;
				}

				template<>
				inline void BufferLayoutElement<glm::mat4>::GetSpecs() {
								m_DataSize = sizeof(glm::mat4);
								m_SubElementCount = 4;
								m_Dimensions = 4;
				}

				template<>
				inline void BufferLayoutElement<int>::GetSpecs() {
								m_DataSize = sizeof(int);
								m_SubElementCount = 1;
								GL_Type = GL_INT;
				}

				template<>
				inline void BufferLayoutElement<float>::GetSpecs() {
								m_DataSize = sizeof(float);
								m_SubElementCount = 1;
				}

				template<>
				inline void BufferLayoutElement<idx_type>::GetSpecs() {
								m_DataSize = sizeof(idx_type);
								m_SubElementCount = 0;
								GL_Type = GL_UNSIGNED_SHORT;
				}
};
