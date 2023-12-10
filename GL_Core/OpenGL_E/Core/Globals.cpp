#include <epch.h>
#include <filesystem>
#include <Windows.h>
#include <algorithm>

std::filesystem::path exe_dir;
std::filesystem::path asset_dir;
std::filesystem::path audio_dir;
std::filesystem::path image_dir;

std::filesystem::path shader_dir;

namespace Core {
				void Globals_Init() {

								char buffer[MAX_PATH];
								GetModuleFileNameA(nullptr, buffer, MAX_PATH);
								exe_dir.assign(std::filesystem::path(buffer).parent_path());

								switch (Core::CurrentDriver) {
								case Driver::OpenGL:
												asset_dir = exe_dir / GL_ASSETS_PATH;
												image_dir = asset_dir / GL_IMAGES_PATH;
												audio_dir = asset_dir / GL_AUDIOS_PATH;
												shader_dir = asset_dir / GL_SHADER_PATH;

												break;
								case Driver::Vulkan:break;
								case Driver::Direct:break;
								}

								std::array<PathError, 5> ErrorChecklist{
												ValidatePath(asset_dir),
												ValidatePath(image_dir),
												ValidatePath(audio_dir),

												ValidatePath(shader_dir),
								};

				}



				PathError ValidatePath(const std::filesystem::path& p_path) {
								if (std::filesystem::exists(p_path)) {
												return PathError::COMPLETED;
								}
								std::cout << "Error: " << p_path << "is invalid\n";
								return PathError::INVALID_DIR;
				}

}
