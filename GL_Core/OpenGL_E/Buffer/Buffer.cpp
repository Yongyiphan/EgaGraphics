#include <epch.h>
#include "Buffer.h"
#include <glm/glm.hpp>


namespace GL_Graphics {


				template <>
				void BufferLayoutElement<glm::vec2>::GetSpecs() {
								m_DataSize = sizeof(glm::vec2);
								m_SubElementCount = 2;
				}

				template <>
				void BufferLayoutElement<glm::vec3>::GetSpecs() {
								m_DataSize = sizeof(glm::vec3);
								m_SubElementCount = 3;
				}

				template <>
				void BufferLayoutElement<glm::vec4>::GetSpecs() {
								m_DataSize = sizeof(glm::vec4);
								m_SubElementCount = 4;
				}

				template<>
				void BufferLayoutElement<float>::GetSpecs() {
								m_DataSize = sizeof(float);
								m_SubElementCount = 1;
				}


}
