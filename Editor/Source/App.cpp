
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

				void Update() {
								KEY_TRIGGER_START(KeyMap);
								TestMovement(instructions);
								KEY_TRIGGER_END;
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
				App->AppCamera->AddCamera(new Core::SampleCamera(
								"Engine", { 0.f, 0.f, 5.f },
								FWidth, FHeight,
								{ 0.f, 0.f, 0.f }
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
				TO.transformc.SetPosition({ 0.f, 0.f, 0.f });
				TO.transformc.SetScale({ 30.f, 30.f, 0.f });

				TO.KeyMap.SetKeyBinding(GLFW_KEY_A, { KeyTriggerType::CLICK_HOLD, ENUM_Key_Actions::LEFT });
				TO.KeyMap.SetKeyBinding(GLFW_KEY_D, { KeyTriggerType::CLICK_HOLD, ENUM_Key_Actions::RIGHT });
				TO.KeyMap.SetKeyBinding(GLFW_KEY_W, { KeyTriggerType::CLICK_HOLD, ENUM_Key_Actions::UP });
				TO.KeyMap.SetKeyBinding(GLFW_KEY_S, { KeyTriggerType::CLICK_HOLD, ENUM_Key_Actions::DOWN });



				TestObject BG{};
				BG.transformc.SetPosition({ 0.f, 0.f, 0.f });
				BG.transformc.SetScale({ FWidth, FHeight, 0.f });
				BG.meshc.SetMeshName("FilledQuad");

				RenderSystem::SetClearColor(App->GetBackgroundColor());
				while (App->Run()) {
								auto window_size = App->AppWindow->GetDimensions();
#define USE_FRAMEBUFFER_IMAGE
#ifdef USE_FRAMEBUFFER_IMAGE
								MainBuffer.Resize(window_size.x, window_size.y);
								FrameBuffer::Bind(MainBuffer.GetFrameBufferID());
#endif
								App->AppCamera->Update(App->GetDeltaTime());
								proj_view = App->AppCamera->GetCurrentCamera()->GetProjectionViewMatrix();

								{
												TO.Update();
								}

								RenderSystem::BatchStart();
								RenderSystem::Submit(0, &BG.meshc, &BG.transformc);
								//RenderSystem::Render(*GMan.GetModel(BG.meshc.GetMeshName()).get(), &BG.transformc, proj_view);
								//RenderSystem::Render(*GMan.GetModel(TO.meshc.GetMeshName()).get(), &TO.transformc, proj_view);
								RenderSystem::BatchEnd();

								// Require to prep for next cycle
#ifdef USE_FRAMEBUFFER_IMAGE
								FrameBuffer::UnBind();
								//App->EImGui->RenderFramebuffer(MainBuffer, glm::vec2{ Window_Width, Window_Height });
								RenderSystem::Render(*GMan.GetModel("FilledQuad").get(), 2.f, 2.f, MainBuffer.GetColorAttachment(0));
#endif
								App->Next();
				}
}
