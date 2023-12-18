#include <epch.h>
#include "Graphics.h"
#include "Render.h"
#include "Shader/Shader.h"


namespace GL_Graphics {

				void RenderSystem::Render(BufferData BD, ECS::TransformComponent* transform) {
								GLBuffer::BufferID BufferID = BufferSystem::CreateGLBuffer(BD);
								auto& Shader = ShaderManager::GetInstance();
								Shader.Use("SingleRender");

								BufferSystem::Bind(BufferID.vaoid);

								glm::mat4 trs = GL_Graphics::Model_Xform(*transform);
								glm::mat4 proj_view(1.f);
								proj_view[0].x = 2.f / 1280.f;
								proj_view[1].y = 2.f / 720.f;

								Shader.SetUniformMat4("trs", proj_view * trs);
								GL_Graphics::DrawElementCall(BD.GetPrimitive(), (GLsizei)BD.GetIndexBuffer()->GetElementCount(), GL_UNSIGNED_SHORT, NULL);

								BufferSystem::UnBind();
								Shader.UnUse();
								BufferSystem::DeleteGLBuffer(BufferID);
				}

				void RenderSystem::Render(const BufferData& BD, ECS::TransformComponent*, ECS::SpriteComponent*) {}
				void RenderSystem::Render(const BufferData& BD, ECS::TransformComponent*, ECS::TextComponent*) {}


				void RenderSystem::BatchFlush() {}
				void RenderSystem::BatchNew() {}
				void RenderSystem::BatchStart() {}
				void RenderSystem::BatchEnd() {}
				void RenderSystem::Submit() {}

}
