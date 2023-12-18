#include <epch.h>
#include "GraphicsHelper.h"
#include <glm/gtc/matrix_transform.hpp>


namespace GL_Graphics {


				glm::mat4 Model_Xform(ECS::TransformComponent p_transformc) {
								glm::mat4 result(1.f);

								result = glm::translate(result, p_transformc.GetPosition());
								result = glm::rotate(result, glm::radians(p_transformc.GetRotationDegree()), p_transformc.GetRotationAxis());
								result = glm::scale(result, p_transformc.GetScale());

								// T * R * S
								return result;
				}

				void DrawArrayCall(GLenum mode, GLint first, GLsizei count, GLsizei instances) {
								if (instances) {
												GLCall(glDrawArraysInstanced(mode, first, count, instances));
								}
								else {
												GLCall(glDrawArrays(mode, first, count));
								}
				}
				void DrawElementCall(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instances) {
								if (instances) {
												GLCall(glDrawElementsInstanced(mode, count, type, indices, instances));
								}
								else {
												GLCall(glDrawElements(mode, count, type, indices));
								}
				}
}
