#pragma once
#include <epch.h>
#include "GraphicsHelper.h"
#include "Buffer/Buffer.h"
#include "Buffer/FrameBuffer.h"
#include "Render/Render.h"

namespace GL_Graphics {

				// Holds cache and data
				class GraphicsManager : public ISingleton<GraphicsManager> {
								friend ISingleton<GraphicsManager>;

								std::map<std::string, std::shared_ptr<BufferData>> Model_Cache;
				public:

								void StoreModel(const std::string& p_modelname, BufferData);
								std::shared_ptr<BufferData> GetModel(const std::string& p_modelname);

				};

}
