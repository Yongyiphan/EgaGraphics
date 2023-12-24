#include <epch.h>
#include "Graphics.h"
#include "Render.h"
#include "Shader/Shader.h"
#include "Imgui/ImGuiHelper.h"
#include <glm/gtc/matrix_transform.hpp>


namespace GL_Graphics {

				void RenderSystem::Render(BufferData BD, ECS::TransformComponent* transform, glm::mat4 projection) {
								GLBuffer::BufferID BufferID = BufferSystem::CreateGLBuffer(BD);
								auto& Shader = ShaderManager::GetInstance();
								Shader.Use("SingleRender");

								BufferSystem::Bind(BufferID.vaoid);

								glm::mat4 trs = GL_Graphics::Model_Xform(*transform);

								Shader.SetUniformMat4("trs", projection * trs);
								Shader.SetUniform1i("TextureFlag", 0);
								Shader.SetUniform1i("SingleTextureFlag", 0);
								GL_Graphics::DrawElementCall(BD.GetPrimitive(), (GLsizei)BD.GetIndexBuffer()->GetElementCount(), GL_UNSIGNED_SHORT, NULL);

								BufferSystem::UnBind();
								Shader.UnUse();
								BufferSystem::DeleteGLBuffer(BufferID);
				}

				void RenderSystem::Render(const BufferData&, ECS::TransformComponent*, ECS::SpriteComponent*) {}
				void RenderSystem::Render(const BufferData&, ECS::TransformComponent*, ECS::TextComponent*) {}

				void RenderSystem::Render(BufferData BD, float width, float height, TextureID TID, glm::mat4 projection) {
								GLBuffer::BufferID BufferID = BufferSystem::CreateGLBuffer(BD);
								auto& Shader = ShaderManager::GetInstance();
								Shader.Use("SingleRender");
								BufferSystem::Bind(BufferID.vaoid);
								glm::mat4 trs(1.f);
								trs = glm::scale(trs, glm::vec3(width / 2.f, height / 2.f, 1.f));

								Shader.SetUniformMat4("trs", projection * trs);
								Shader.SetUniform1i("TextureFlag", 1);
								Shader.SetUniform1i("SingleTextureFlag", 1);
								GLCall(glBindTextureUnit(0, TID));
								GLCall(glBindTexture(GL_TEXTURE_2D, TID));
								Shader.SetUniform1i("SingleTexture", 0);

								GL_Graphics::DrawElementCall(BD.GetPrimitive(), (GLsizei)BD.GetIndexBuffer()->GetElementCount(), GL_UNSIGNED_SHORT, NULL);

								BufferSystem::UnBind();
								Shader.UnUse();
								BufferSystem::DeleteGLBuffer(BufferID);
				}

				void RenderSystem::BatchFlush() {}
				void RenderSystem::BatchNew() {}
				void RenderSystem::BatchStart() {
								ClearColor();
				}
				void RenderSystem::BatchEnd() {}
				void RenderSystem::Submit() {}


				void RenderSystem::SetClearColor(float r, float g, float b) {
								RenderSystem::GetInstance().Clear_Color = glm::vec3(r, g, b);
				}

				void RenderSystem::SetClearColor(glm::vec3 clr) {
								RenderSystem::GetInstance().Clear_Color = clr;
				}

				void RenderSystem::ClearColor() {
								Clear();
								ClearColor(RenderSystem::GetInstance().GetClearColor());
				}

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
