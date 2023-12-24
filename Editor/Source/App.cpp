
#ifdef ELIB_OPENGL 
#include <Core.h>
using namespace GL_Graphics;
#endif
#ifdef ELIB_VULKAN 
#include <Vulkan_E/Core/Core.h>
#endif

struct TestObject {
				Core::KeyBinding m_KeyBind;
				ECS::TransformComponent transformc;
				ECS::SpriteComponent spritec;
				ECS::MeshComponent meshc;
				ECS::TextComponent textc;
				Core::KeyBinding KeyMap;

				TestObject() {
								transformc = ECS::TransformComponent();
								spritec = ECS::SpriteComponent();
								meshc = ECS::MeshComponent("FilledCircle");
								textc = ECS::TextComponent();
				}

				inline void TestMovement(Core::Base_KeyMap Instruction) {
								if (Instruction.CheckFlags(ENUM_Key_Actions::UP)) {
												transformc.SetPosition(transformc.GetPosition() + glm::vec3{ 0.f, 10.f, 0.f });
								}
								if (Instruction.CheckFlags(ENUM_Key_Actions::DOWN)) {
												transformc.SetPosition(transformc.GetPosition() + glm::vec3{ 0.f, -10.f, 0.f });
								}
								if (Instruction.CheckFlags(ENUM_Key_Actions::LEFT)) {
												transformc.SetPosition(transformc.GetPosition() + glm::vec3{ -10.f, 0.f, 0.f });

								}
								if (Instruction.CheckFlags(ENUM_Key_Actions::RIGHT)) {
												transformc.SetPosition(transformc.GetPosition() + glm::vec3{ 10.f, 0.f, 0.f });
								}
				}

				void Update(const std::shared_ptr<Core::Input>& p_input) {

								KeyMap.Update(p_input->GetCurrentSequence(), [&](Core::Base_KeyMap l) {
												TestMovement(l);
												});
				}
};

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

				TestObject TO{};
				TO.transformc.SetPosition({ 0.f, 0.f, 1.f });
				TO.transformc.SetScale({ 30.f, 30.f, 1.f });

				TO.KeyMap.SetKeyBinding(GLFW_KEY_A, { ENUM_Key_Actions::LEFT });
				TO.KeyMap.SetKeyBinding(GLFW_KEY_D, { ENUM_Key_Actions::RIGHT });
				TO.KeyMap.SetKeyBinding(GLFW_KEY_W, { ENUM_Key_Actions::UP });
				TO.KeyMap.SetKeyBinding(GLFW_KEY_S, { ENUM_Key_Actions::DOWN });

				App->AppCamera->GetCurrentCamera()->SetKeyBind(GLFW_KEY_Z, { ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD });
				App->AppCamera->GetCurrentCamera()->SetKeyBind(GLFW_KEY_X, { ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::BACKWARD });
				Core::Base_KeyMap km(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD);

				TestObject BG{};
				BG.transformc.SetScale({ FWidth, FHeight, 1.f });
				BG.meshc.SetMeshName("FilledQuad");

				RenderSystem::SetClearColor(App->GetBackgroundColor());
				while (App->Run()) {
								auto window_size = App->AppWindow->GetDimensions();
#define USE_FRAMEBUFFER_IMAGE
#ifdef USE_FRAMEBUFFER_IMAGE
								MainBuffer.Resize(window_size.x, window_size.y);
								FrameBuffer::Bind(MainBuffer.GetFrameBufferID());
#endif
								App->AppCamera->Update(App->AppInput, App->GetDeltaTime());
								proj_view[0].x = 2.f / window_size.x;
								proj_view[1].y = 2.f / window_size.y;
								//proj_view = App->AppCamera->GetCurrentCamera()->GetProjectionViewMatrix();

								{
												TO.Update(App->AppInput);
								}

								RenderSystem::BatchStart();
								RenderSystem::Render(*GMan.GetModel(BG.meshc.GetMeshName()).get(), &BG.transformc, proj_view);
								RenderSystem::Render(*GMan.GetModel(TO.meshc.GetMeshName()).get(), &TO.transformc, proj_view);
								RenderSystem::BatchEnd();

								// Require to prep for next cycle
#ifdef USE_FRAMEBUFFER_IMAGE
								FrameBuffer::UnBind();
								//App->EImGui->RenderFramebuffer(MainBuffer, glm::vec2{ Window_Width, Window_Height });
								RenderSystem::Render(*GMan.GetModel("FilledQuad").get(), FWidth, FHeight, MainBuffer.GetColorAttachment(0), proj_view);
#endif
								App->Next();
				}
}
