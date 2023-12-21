#pragma once
#include <epch.h>
#include "Buffer/Buffer.h"

namespace GL_Graphics {

				class RenderSystem :public ISingleton<RenderSystem> {

								void BatchFlush();
								void BatchNew();
				public:
								static void Render(BufferData, ECS::TransformComponent*, glm::mat4 projection);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::SpriteComponent*);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::TextComponent*);

								static void BatchStart();
								static void BatchEnd();
								static void Submit();
								static void ClearColor(float r, float g, float b);
								static void ClearColor(glm::vec3 clr);
								static void Clear();
				};

}
