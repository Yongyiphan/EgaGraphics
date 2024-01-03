#include <epch.h>
#include "Graphics.h"
#include "Render.h"
#include "Shader/Shader.h"
#include "Imgui/ImGuiHelper.h"
#include <glm/gtc/matrix_transform.hpp>


////////////////////////////////////////////////////////////
///                                                      ///
///																	 BATCH RENDER CALLS		  														///
///                                                      ///
////////////////////////////////////////////////////////////
namespace GL_Graphics {
				void BatchInfo::Allocate(GLenum primitive, size_t model_pos_vtx_count, size_t model_idx_vtx_count) {
								unref(model_idx_vtx_count);
								if (m_Data.empty() || m_Data.find(primitive) == m_Data.end()) {
												BufferData newBD(primitive);
												size_t ReserveSize = model_pos_vtx_count * BATCH_LIMIT::MAX_BATCH_OBJECT;
												newBD.ConstructBufferElement<glm::vec3>("pos", std::vector<glm::vec3>{}, false, ReserveSize);
												newBD.ConstructBufferElement<glm::vec3>("clr", std::vector<glm::vec3>{}, false, ReserveSize);
												newBD.ConstructBufferElement<glm::vec2>("tex", std::vector<glm::vec2>{}, false, ReserveSize);
												newBD.ConstructBufferElement<float>("tex", std::vector<float>{}, false, ReserveSize);
												newBD.ConstructIndexBuffer(std::vector<GL_Graphics::index_type>{}, false, ReserveSize + BATCH_LIMIT::MAX_BATCH_OBJECT);
												m_Data.insert({ primitive, std::move(newBD) });
								}
				}

				void BatchInfo::Reset(bool forced) {
								if (forced) {

								}
								else {
												for (auto& [primitive_, data] : m_Data) {
																data.Clear();
												}
								}

				}

				bool BatchInfo::CheckFilled() {
								if (TotalModelCounter == BATCH_LIMIT::MAX_BATCH_OBJECT) {
												return IsFilled = true;
								}
								return false;

				}

				void RenderSystem::BatchFlush(bool) {}

				void RenderSystem::BatchNew(int Layer, ECS::MeshComponent* mcomp) {
								if (TotalBatchedContainer.find(Layer) == TotalBatchedContainer.end()) {
												TotalBatchedContainer[Layer] = std::move(std::make_unique<BatchInfo>());
								}
								auto& LatestBatch = TotalBatchedContainer[Layer];
								auto mesh_template = GL_Graphics::GraphicsManager::GetInstance().GetModel(mcomp->GetMeshName());
								auto template_pos = mesh_template->GetBufferElement<glm::vec3>("pos");
								auto template_idx = mesh_template->GetIndexBuffer();
								LatestBatch->Allocate(mesh_template->GetPrimitive(), template_pos->GetElementCount(), template_idx->GetElementCount());
				}

				void RenderSystem::BatchStart() {
								ClearColor();
				}

				void RenderSystem::BatchEnd() {
								RenderSystem::GetInstance().BatchFlush(true);
				}

				void RenderSystem::Submit() {}

				void RenderSystem::Submit(int Layer, ECS::MeshComponent* mcomp, ECS::TransformComponent* tcomp, ECS::SpriteComponent* scomp) {
								if (!tcomp) return;
								auto& RS = RenderSystem::GetInstance();
								RS.BatchNew(Layer, mcomp);
								auto& LatestBatch = RS.TotalBatchedContainer[Layer];
								// Template Info
								auto mesh_template = GL_Graphics::GraphicsManager::GetInstance().GetModel(mcomp->GetMeshName());
								auto template_pos = mesh_template->GetBufferElement<glm::vec3>("pos");
								auto template_clr = mesh_template->GetBufferElement<glm::vec3>("clr");
								auto template_tex = mesh_template->GetBufferElement<glm::vec2>("tex");
								auto template_idx = mesh_template->GetIndexBuffer();
								auto& LatestBatchData = LatestBatch->m_Data[mesh_template->GetPrimitive()];

								auto batch_pos = LatestBatchData.GetBufferElement<glm::vec3>("pos")->GetData();
								auto batch_clr = LatestBatchData.GetBufferElement<glm::vec3>("clr")->GetData();
								auto batch_tex = LatestBatchData.GetBufferElement<glm::vec2>("tex")->GetData();
								glm::mat4 trs = GL_Graphics::Model_Xform(*tcomp);
								for (auto pos : template_pos->GetData()) {
												batch_pos.push_back(trs * glm::vec4(pos, 1.f));
												if (mcomp->IsColorSet()) {
																batch_clr.push_back(mcomp->GetColor());
												}
								}
								if (scomp) {

								}
								else {
												for (auto tex : template_tex->GetData()) {
																batch_tex.push_back(tex);
												}
								}

								if (LatestBatch->CheckFilled()) {
												E_LOG_INFO("Batch Full");
								}


				}

}

////////////////////////////////////////////////////////////
///                                                      ///
///																	 STATIC RENDER CALLS		 														///
///                                                      ///
////////////////////////////////////////////////////////////
namespace GL_Graphics {

				void RenderSystem::Render(const BufferData& BD, ECS::TransformComponent* transform, glm::mat4 projection) {
								GLBuffer::BufferID BufferID = BufferSystem::CreateGLBuffer(BD);
								auto& Shader = ShaderManager::GetInstance();
								Shader.Use("SingleRender");

								BufferSystem::Bind(BufferID.vaoid);

								glm::mat4 trs = GL_Graphics::Model_Xform(*transform);

								Shader.SetUniformMat4("trs", projection * trs);
								Shader.SetUniform1i("TextureFlag", 0);
								Shader.SetUniform1i("SingleTextureFlag", 0);
								GL_Graphics::DrawElementCall(BD.GetPrimitive(), (GLsizei)BD.GetIndexBuffer()->GetElementCount(), GL_UNSIGNED_SHORT, NULL);
								//GL_Graphics::DrawArrayCall(BD.GetPrimitive(), 0, 6);

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
}

////////////////////////////////////////////////////////////
///                                                      ///
///												RENDER SYSTEM GENERAL DEFINITIONS								 ///
///                                                      //
////////////////////////////////////////////////////////////
namespace GL_Graphics {
				int RenderSystem::AddTextureToSlot(TextureID) {
								return LatestTextureSlot;
				}

				void RenderSystem::ResetTextureSlotArray() {

				}

				void RenderSystem::SetDebugColor(float r, float g, float b) {
								m_DebugColor.r = r;
								m_DebugColor.g = g;
								m_DebugColor.b = b;
				}

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
