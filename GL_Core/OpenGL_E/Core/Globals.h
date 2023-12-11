#pragma once
#include <filesystem>
#include <Windows.h>


extern std::filesystem::path exe_dir;

extern std::filesystem::path asset_dir;
extern std::filesystem::path audio_dir;
extern std::filesystem::path image_dir;

extern std::filesystem::path shader_dir;

namespace Core {

				enum class Driver {
								OpenGL,
								Vulkan,
								Direct
				} static CurrentDriver;

				enum class PathError {
								COMPLETED,
								INVALID_DIR,
								INVALID_FILE,
				};

				void SetDriver(Core::Driver = Core::Driver::OpenGL);

				void Globals_Init();

				PathError ValidatePath(const std::filesystem::path&);
				void GLClearError();
				std::pair<bool, std::string> GLCheckError(const char* FILE, int LINE);
};
// Macro definition to wrap gl commands within a error check
#ifdef _DEBUG
#define GLCall( x ) [&](){\
			 Core::GLClearError(); \
			 x; \
			 std::pair<bool, std::string> status = Core::GLCheckError(__FILE__, __LINE__);\
			if(!status.first) {\
										ASSERT_MSG(status.second);\
			}\
			return status.first;\
			}()

#define GLCallV( x ) [&]() { \
     Core::GLClearError(); \
     auto retVal = x; \
					std::pair<bool, std::string> status = Core::GLCheckError(__FILE__, __LINE__);\
					if(!status.first) {\
								ASSERT_MSG(status.second);\
					}\
     return retVal; \
   }()
#else
#define GLCall( x ) [&](){\
			x; \
			return true; \
			}()
#define GLCallV( x ) [&]() { \
     Graphics::GLClearError(); \
     auto retVal = x; \
		 std::pair<bool, std::string> status = Graphics::GLCheckError(__FILE__, __LINE__);\
     return retVal; \
   }()
#endif

