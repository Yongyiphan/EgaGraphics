#include <Core/Core.h>



int main()
{
				Core::SetDriver(Core::Driver::OpenGL);
				Core::GL_Core* App = new Core::GL_Core();
				int Window_Width = 1280;
				int Window_Height = 720;
				App->Init(Window_Width, Window_Height);
				while (App->Run()) {
								//App->AppWindow->CloseWindow();
								if (App->AppInput->IsKeyPress(MOUSE_LEFT)) {
												std::cout << "Mouse Pressed\n";
								}
								if (App->AppInput->IsKeyHold(MOUSE_LEFT)) {
												std::cout << "Mouse Hold\n";
								}

								// Require to prep for next cycle
								App->Next();
				}

				delete App;

}