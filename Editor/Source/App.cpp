
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
				App->Init(Window_Width, Window_Height);
				App->SetBackgroundColor(0.5f, 0.1f, 0.5f);
				App->AppCamera->AddCamera(new Core::Camera(
								"Engine", {},
								static_cast<float>(Window_Width),
								static_cast<float>(Window_Height)
				));

				GraphicsManager& GMan = GraphicsManager::GetInstance();

				while (App->Run()) {
								App->AppCamera->Update(App->GetDeltaTime());

								auto transformc = ECS::TransformComponent();
								transformc.SetPosition({ 0.f, 0.f, 1.f });
								transformc.SetScale({ 100.f, 200.f, 0.f });

								auto spritec = ECS::SpriteComponent();
								auto meshc = ECS::MeshComponent("FilledCircle");
								auto textc = ECS::TextComponent();

								RenderSystem::BatchStart();
								RenderSystem::Render(*GMan.GetModel(meshc.GetMeshName()).get(), &transformc);
								//RenderSystem::Render(*GMan.GetModel(meshc.GetMeshName()).get(), &transformc);
								// App->AppRender(transformc, spritec, meshc);
								// App->AppRender(transformc, textc);

								////////////

								// App->AppRender->BatchStart();
								// App->AppRender->Submit();
								// App->AppRender->BatchEnd();




								// Require to prep for next cycle
								App->Next();
				}

}