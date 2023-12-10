#include <epch.h>
#include "Core.h"
#include "Buffer/Buffer.h"

namespace Core {


				void SetDriver(Core::Driver SelectedDriver) {
								CurrentDriver = SelectedDriver;
				}

				GL_Core::GL_Core() {
								AppWindow = std::make_shared<Core::GLWindow>();
								AppInput = std::make_shared<Core::Input>();
								GLShader = std::make_shared<GL_Graphics::ShaderManager>();
								std::filesystem::path __ = std::filesystem::current_path();
				}

				void GL_Core::Init(int width, int height) {
								AppWindow->Init(width, height);
								Globals_Init();
								SetupShaders();



				}

				GL_Core::~GL_Core() {
								AppWindow->CleanUp();

				}

				bool GL_Core::Run() {
								bool close = !AppWindow->ShouldClose();
								return close;
				}

				void GL_Core::Next() {
								AppWindow->swapBuffers();
								AppWindow->pollEvents();
				}

				void GL_Core::SetupShaders() {
								GLShader->AddShaderGroup(GL_Graphics::ShaderGroup("Test",
												{
																GL_Graphics::ShaderType::VERT_SHADER,
																GL_Graphics::ShaderType::FRAG_SHADER,
																//GL_Graphics::ShaderType::GEOM_SHADER,
												}));
				}

				void GLClearError() {
								while (glGetError() != GL_NO_ERROR);
				}

				std::pair<bool, std::string> GLCheckError(const char* FILE, int LINE) {
								while (GLenum err = glGetError()) {
												std::stringstream ss;
												ss << "Err Code: " << err << " at: \n" << FILE << " (" << LINE << ")";
#ifdef _DEBUG
												ASSERT_MSG(ss.str());
#endif
												return std::make_pair<bool, std::string>(false, ss.str());
								}
								return std::make_pair<bool, std::string>(true, "Success");
				}
}