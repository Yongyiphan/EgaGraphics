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
}
