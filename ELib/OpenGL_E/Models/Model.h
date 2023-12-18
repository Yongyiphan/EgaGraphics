#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "Buffer/Buffer.h"
#include "ECS/ECS.h"

namespace GL_Graphics {


				BufferData CreatePointModel();
				BufferData CreateLineModel();
				BufferData CreateQuadModel(bool hollow = false);
				BufferData CreateCircleModel(size_t points, bool hollow = false);
				BufferData CreateTextModel(ECS::TransformComponent* transformc_ptr, ECS::TextComponent* textc_ptr);
}

#endif //MODEL_H
