#pragma once
#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include "Assets/IAssets.h"


namespace Core {


				class AssetsManager : public ISingleton<AssetsManager> {
				public:
								AssetsManager();


				private:
								std::map<std::string, IAsset> m_AssetList;

				};
}



#endif
