#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "Buffer/Buffer.h"


namespace GL_Graphics {


				BufferData CreatePointModel();
				BufferData CreateLineModel();
				BufferData CreateQuadModel(bool hollow = false);
				BufferData CreateCircleModel(size_t points, bool hollow = false);
}

#endif //MODEL_H
