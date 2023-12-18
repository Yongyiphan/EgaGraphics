#include <epch.h>
#pragma once




namespace GL_Graphics {

				glm::mat4 Model_Xform(ECS::TransformComponent);


				void DrawArrayCall(GLenum mode, GLint first, GLsizei count, GLsizei instances = 0);
				void DrawElementCall(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instances = 0);
}
