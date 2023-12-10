#define OpenGL_E 
//#define Vulkan_E

#ifdef OpenGL_E
#include <OpenGL_E/Core/Core.h>
#endif
#ifdef Vulkan_E
#include <Vulkan_E/Core/Core.h>
#endif

int main()
{
				Core::SetDriver(Core::Driver::OpenGL);
				Core::GL_Core* App = new Core::GL_Core();
				int Window_Width = 1280;
				int Window_Height = 720;
				App->Init(Window_Width, Window_Height);
				while (App->Run()) {
								//App->AppWindow->CloseWindow();
								if (App->AppInput->IsKeyPress(GLFW_KEY_ESCAPE)) {
												App->AppWindow->CloseWindow();
								}

								// Require to prep for next cycle
								App->Next();
				}

				delete App;

}