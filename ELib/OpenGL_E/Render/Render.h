#pragma once
#include <epch.h>
#include "Buffer/Buffer.h"

namespace GL_Graphics {

				class RenderSystem :public ISingleton<RenderSystem> {

								void BatchFlush();
								void BatchNew();
				public:
								static void Render(BufferData, ECS::TransformComponent*);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::SpriteComponent*);
								static void Render(const BufferData&, ECS::TransformComponent*, ECS::TextComponent*);

								static void BatchStart();
								static void BatchEnd();
								static void Submit();
				};

}
