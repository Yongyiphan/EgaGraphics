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
								//GLShader = std::make_shared<GL_Graphics::ShaderManager>();
								std::filesystem::path __ = std::filesystem::current_path();
				}

				void GL_Core::Init(int width, int height) {
								AppWindow->Init(width, height);
								Globals_Init();
								SetupShaders();
								SetupModels();



				}

				GL_Core::~GL_Core() {
								AppWindow->CleanUp();

				}

				bool GL_Core::Run() {
								bool close = !AppWindow->ShouldClose();
								glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
								glClearColor(m_BGColor.r, m_BGColor.g, m_BGColor.b, 1.f);
								// Very Defaulted base key inputs. redundant in main loop
								if (AppInput->IsKeyPress(GLFW_KEY_ESCAPE)) {
												AppWindow->CloseWindow();
								}
								return close;
				}

				void GL_Core::Next() {
								AppWindow->swapBuffers();
								AppWindow->pollEvents();
				}

				void GL_Core::SetupShaders() {
								auto& GLShader = GL_Graphics::ShaderManager::GetInstance();
								GLShader.AddShaderGroup(GL_Graphics::ShaderGroup("Test",
												{
																GL_Graphics::ShaderType::VERT_SHADER,
																GL_Graphics::ShaderType::FRAG_SHADER,
																//GL_Graphics::ShaderType::GEOM_SHADER,
												}));

								GLShader.AddShaderGroup(GL_Graphics::ShaderGroup("SingleRender",
												{
																GL_Graphics::ShaderType::VERT_SHADER,
																GL_Graphics::ShaderType::FRAG_SHADER,
												}));
				}

				void GL_Core::SetupModels() {
								auto& GM = GL_Graphics::GraphicsManager::GetInstance();
								GM.StoreModel("FilledQuad", GL_Graphics::CreateQuadModel());
								GM.StoreModel("HollowQuad", GL_Graphics::CreateQuadModel(true));
								GM.StoreModel("FilledCircle", GL_Graphics::CreateCircleModel(36));
								GM.StoreModel("HollowCircle", GL_Graphics::CreateCircleModel(36, true));
								GM.StoreModel("Points", GL_Graphics::CreatePointModel());
								GM.StoreModel("Lines", GL_Graphics::CreateLineModel());
				}

				void GL_Core::SetBackgroundColor(float p_r, float p_g, float p_b) {
								m_BGColor.r = p_r;
								m_BGColor.g = p_g;
								m_BGColor.b = p_b;

				}

}