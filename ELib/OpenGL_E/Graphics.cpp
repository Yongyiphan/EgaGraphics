#include <epch.h>
#include "Graphics.h"
#include "Buffer/Buffer.h"



namespace GL_Graphics {
				template class ISingleton<GraphicsManager>;

				void GraphicsManager::StoreModel(const std::string& p_modelname, BufferData p_model) {
								Model_Cache.emplace(p_modelname, std::make_shared<BufferData>(p_model));
				}

				std::shared_ptr<BufferData> GraphicsManager::GetModel(const std::string& p_modelname) {
								auto found = Model_Cache.find(p_modelname);
								if (found != Model_Cache.end()) {
												return found->second;
								}
								return nullptr;
				}

}
