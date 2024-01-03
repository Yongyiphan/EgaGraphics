#pragma once
#include <epch.h>
#include "Buffer/Buffer.h"


namespace GL_Graphics {

				struct BatchInfo {
								bool IsFilled{ false };
								size_t TotalModelCounter;

								// Sort by primitive;
								std::map<GLenum, BufferData> m_Data;
								std::map<GLenum, size_t> batch_object_counter;
								void Allocate(GLenum, size_t model_pos_vtx_count, size_t model_idx_vtx_count = DEFAULT_CIRCLE_MODEL_SPLICES + 1);
								void Reset();
								bool CheckFilled();
				};

				class RenderSystem :public ISingleton<RenderSystem> {
								glm::vec3 Clear_Color;
								inline glm::vec3 GetClearColor() { return Clear_Color; }

								////////////////////////////////////////////////////////////
								///                                                      ///
								///																 BATCH RENDER FUNCTIONS														 ///
								///                                                      ///
								////////////////////////////////////////////////////////////
				private:
								int Texture_Slot[GPU_LIMIT::GL_MAX_TEXTURE_SLOT];
								size_t LatestTextureSlot{};
								std::map<int, std::unique_ptr<BatchInfo>> DefaultBatchedContainer;
								std::vector<BatchInfo> PenBatchContainer;
				private:
								std::map<GLenum, BatchInfo> DebugBatchContainer;
								glm::vec3 m_DebugColor{ 0.2f, 1.f, 0.2f };
								bool m_DebugFlag{ false };
				private:
								void BatchFlush(bool full = false);
								void BatchNew(int Layer, ECS::MeshComponent*);
								void BatchReset(bool full = false);
								void BatchRenderDebug();
								void BatchRenderPen();
				public:
								size_t AddTextureToSlot(TextureID);
								bool HasTextureSlot();
								bool HasBatchSlot();
								void ResetTextureSlotArray();
								void SetDebugColor(float r, float g, float b);
								inline void ToggleDebug() { m_DebugFlag = m_DebugFlag ? false : true; }
				public: // Batch Render
								static void BatchStart();
								static void BatchEnd();
								static void Submit();
								static void Submit(int Layer, ECS::MeshComponent*, ECS::TransformComponent*, ECS::SpriteComponent* = nullptr);

								////////////////////////////////////////////////////////////
								///                                                      ///
								///												STATIC SINGLE RENDER FUNCTIONS											 ///
								///                                                      ///
								////////////////////////////////////////////////////////////
				public:
								static void Render(const BufferData&, ECS::TransformComponent*, glm::mat4 projection);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::SpriteComponent*);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::TextComponent*);
								// Render Framebuffer as texture
								static void Render(BufferData, float, float, TextureID, glm::mat4 projection = glm::mat4(1.f));
				public:
								static void SetClearColor(float r, float g, float b);
								static void SetClearColor(glm::vec3 clr);
								static void ClearColor(float r, float g, float b);
								static void ClearColor(glm::vec3 clr);
								static void ClearColor(); // Using internal member variable: Clear_Color
								static void Clear(); // Clear buffer
				};

}
