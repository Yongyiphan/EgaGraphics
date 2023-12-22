
#ifdef ELIB_OPENGL 
#include <Core.h>
using namespace GL_Graphics;
#endif
#ifdef ELIB_VULKAN 
#include <Vulkan_E/Core/Core.h>
#endif

int main()
{
				Core::SetDriver(Core::Driver::OpenGL);
				std::unique_ptr<Core::GL_Core> App = std::make_unique<Core::GL_Core>();
				int Window_Width = 1280;
				int Window_Height = 720;
				float FWidth = static_cast<float>(Window_Width);
				float FHeight = static_cast<float>(Window_Height);
				App->Init(Window_Width, Window_Height);
				App->SetBackgroundColor(0.5f, 0.1f, 0.5f);
				App->AppCamera->AddCamera(new Core::Camera(
								"Engine", {},
								FWidth, FHeight
				));

				GraphicsManager& GMan = GraphicsManager::GetInstance();
				FrameBufferSettings MainBufferSettings("MainBuffer", FWidth, FHeight);
				MainBufferSettings.m_Attachment = {
								Attachment(GL_RGBA32F, GL_RGBA, GL_COLOR_ATTACHMENT0),
								Attachment(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL_ATTACHMENT)
				};
				FrameBuffer MainBuffer(MainBufferSettings);

				glm::mat4 proj_view(1.f);

				auto transformc = ECS::TransformComponent();
				auto spritec = ECS::SpriteComponent();
				auto meshc = ECS::MeshComponent("FilledCircle");
				auto textc = ECS::TextComponent();

				transformc.SetPosition({ 0.f, 0.f, 1.f });
				transformc.SetScale({ 30.f, 30.f, 0.f });

				Core::KeyBinding KeyMap;
				Core::Base_KeyMap _;
				KeyMap.SetKeyBinding(GLFW_KEY_W, Core::Base_KeyMap(Base_Key_Actions::UP));
				KeyMap.SetKeyBinding(GLFW_KEY_S, Core::Base_KeyMap(Base_Key_Actions::DOWN));
				KeyMap.SetKeyBinding(GLFW_KEY_A, Core::Base_KeyMap(Base_Key_Actions::LEFT));
				KeyMap.SetKeyBinding(GLFW_KEY_D, Core::Base_KeyMap(Base_Key_Actions::RIGHT));


				while (App->Run()) {
								auto window_size = App->AppWindow->GetDimensions();
								//#define USE_IMGUI_FRAMEBUFFER_IMAGE
#ifdef USE_IMGUI_FRAMEBUFFER_IMAGE
								MainBuffer.Resize(window_size.x, window_size.y);
								FrameBuffer::Bind(MainBuffer.GetFrameBufferID());
#endif
								RenderSystem::ClearColor(App->GetBackgroundColor());

								App->AppCamera->Update(App->GetDeltaTime());
								proj_view[0].x = 2.f / window_size.x;
								proj_view[1].y = 2.f / window_size.y;
								//proj_view = App->AppCamera->GetCurrentCamera()->GetProjectionViewMatrix();

								{

												if () {
																E_LOG_INFO(CurrentKey->key);
																if (App->AppInput->IsKeyPressHold(CurrentKey->key)) {
																				Core::Base_KeyMap Instruction = KeyMap.GetBaseKeyMap(CurrentKey->key);
																				if (Instruction.IsSet(Base_Key_Actions::UP)) {
																								transformc.SetPosition(transformc.GetPosition() + glm::vec3{ 0.f, 10.f, 0.f });
																				}
																				if (Instruction.IsSet(Base_Key_Actions::DOWN)) {
																								transformc.SetPosition(transformc.GetPosition() + glm::vec3{ 0.f, -10.f, 0.f });
																				}
																				if (Instruction.IsSet(Base_Key_Actions::LEFT)) {
																								transformc.SetPosition(transformc.GetPosition() + glm::vec3{ -10.f, 0.f, 0.f });

																				}
																				if (Instruction.IsSet(Base_Key_Actions::RIGHT)) {
																								transformc.SetPosition(transformc.GetPosition() + glm::vec3{ 10.f, 0.f, 0.f });

																				}
																}

												}
								}

								RenderSystem::BatchStart();
								RenderSystem::Render(*GMan.GetModel(meshc.GetMeshName()).get(), &transformc, proj_view);
								RenderSystem::BatchEnd();

								// Require to prep for next cycle
#ifdef USE_IMGUI_FRAMEBUFFER_IMAGE
								//FrameBuffer::UnBind();
								//App->EImGui->RenderFramebuffer(MainBuffer, glm::vec2{ Window_Width, Window_Height });
#endif
								App->Next();
				}

}