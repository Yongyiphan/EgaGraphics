#include <epch.h>
#include "Graphics.h"
#include "Render.h"
#include "Shader/Shader.h"
#include "Imgui/ImGuiHelper.h"


namespace GL_Graphics {

				void RenderSystem::Render(BufferData BD, ECS::TransformComponent* transform, glm::mat4 projection) {
								GLBuffer::BufferID BufferID = BufferSystem::CreateGLBuffer(BD);
								auto& Shader = ShaderManager::GetInstance();
								Shader.Use("SingleRender");

								BufferSystem::Bind(BufferID.vaoid);

								glm::mat4 trs = GL_Graphics::Model_Xform(*transform);

								Shader.SetUniformMat4("trs", projection * trs);
								GL_Graphics::DrawElementCall(BD.GetPrimitive(), (GLsizei)BD.GetIndexBuffer()->GetElementCount(), GL_UNSIGNED_SHORT, NULL);

								BufferSystem::UnBind();
								Shader.UnUse();
								BufferSystem::DeleteGLBuffer(BufferID);
				}

				void RenderSystem::Render(const BufferData&, ECS::TransformComponent*, ECS::SpriteComponent*) {}
				void RenderSystem::Render(const BufferData&, ECS::TransformComponent*, ECS::TextComponent*) {}


				void RenderSystem::BatchFlush() {}
				void RenderSystem::BatchNew() {}
				void RenderSystem::BatchStart() {}
				void RenderSystem::BatchEnd() {}
				void RenderSystem::Submit() {}

				void RenderSystem::ClearColor(float r, float g, float b) {
								Clear();
								glClearColor(r, g, b, 1.f);
				}

				void RenderSystem::ClearColor(glm::vec3 clr) {
								RenderSystem::ClearColor(clr.r, clr.g, clr.b);
				}

				void RenderSystem::Clear() {
								glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				}
}
