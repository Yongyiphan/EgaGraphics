#pragma once
#include <epch.h>
#include "Buffer/Buffer.h"


namespace GL_Graphics {

				struct BatchInfo {
								bool IsFilled{ false };

								// Sort by primitive;
								std::map<GLenum, BufferData> m_Data;
								void Allocate();
								void Reset();
				};

				class RenderSystem :public ISingleton<RenderSystem> {
								int Texture_Slot[GPU_LIMIT::GL_MAX_TEXTURE_SLOT];
								glm::vec3 Clear_Color;
								inline glm::vec3 GetClearColor() { return Clear_Color; }
								std::vector<BatchInfo> TotalBatchedContainer;
				public:
								void BatchFlush();
								void BatchNew();
								int AddTextureToSlot(TextureID);
								void ResetTextureSlotArray();

								////////////////////////////////////////////////////////////
								///                                                      ///
								///																	 STATIC FUNCTIONS																			 ///
								///                                                      ///
								////////////////////////////////////////////////////////////
				public:
								static void Render(BufferData, ECS::TransformComponent*, glm::mat4 projection);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::SpriteComponent*);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::TextComponent*);
								// Render Framebuffer as texture
								static void Render(BufferData, float, float, TextureID, glm::mat4 projection = glm::mat4(1.f));
				public: // Batch Render
								static void BatchStart();
								static void BatchEnd();
								static void Submit();
				public:
								static void SetClearColor(float r, float g, float b);
								static void SetClearColor(glm::vec3 clr);
								static void ClearColor(float r, float g, float b);
								static void ClearColor(glm::vec3 clr);
								static void ClearColor(); // Using internal member variable: Clear_Color
								static void Clear(); // Clear buffer
				};

}
