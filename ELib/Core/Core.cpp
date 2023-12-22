#include <epch.h>
#include "Core.h"
#include "Models/Model.h"
#include <chrono>

namespace Core {


				void SetDriver(Core::Driver SelectedDriver) {
								CurrentDriver = SelectedDriver;
				}

				GL_Core::GL_Core() {
								AppWindow = std::make_shared<Core::GLWindow>();
								AppInput = std::make_shared<Core::Input>();
								AppCamera = std::make_shared<Core::CameraManager>();
								EImGui = std::make_shared<Core::EImGui>();

				}

				void GL_Core::Init(int width, int height) {
								AppWindow->Init(width, height);
								Globals_Init();
								SetupShaders();
								SetupModels();
								EImGui->Init(AppWindow->GetWindow());

				}

				GL_Core::~GL_Core() {
								EImGui->CleanUp();
								AppWindow->CleanUp();

				}

				bool GL_Core::Run() {
								AppWindow->pollEvents();
								bool close = !AppWindow->ShouldClose();
								StartFrame();
								EImGui->StartFrame();
								GL_Graphics::RenderSystem::Clear();
								// Very Defaulted base key inputs. redundant in main loop
								if (AppInput->IsKeyPress(GLFW_KEY_ESCAPE)) {
												AppWindow->CloseWindow();
								}
								return close;
				}

				void GL_Core::Next() {
								EImGui->RenderStatsTracker();

								EImGui->EndFrame();
								AppWindow->swapBuffers();
								AppInput->Reset();
								SetFPS_Title();
								EndFrame();
				}

				void GL_Core::StartFrame() {
								static std::chrono::steady_clock::time_point currentTime, lastTime;
								m_Deltatime = 0.0;
								lastTime = currentTime;
								currentTime = std::chrono::steady_clock::now();
								std::chrono::duration<double> delta = currentTime - lastTime;
								m_Deltatime = delta.count();
				}

				void GL_Core::EndFrame() {
				}

				void GL_Core::SetFPS_Title() {
								double fps = 1.0 / m_Deltatime;
								std::string newtitle = AppWindow->GetWindowName() + " FPS [ " + std::to_string(fps) + " ]";
								glfwSetWindowTitle(AppWindow->GetWindow(), newtitle.c_str());
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

				glm::vec3 GL_Core::GetBackgroundColor() {
								return m_BGColor;
				}


}