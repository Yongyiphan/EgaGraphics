#include <epch.h>
#include "Core.h"
#include "Models/Model.h"

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
								auto __ = GL_Graphics::CreateQuadModel();



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

}