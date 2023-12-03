#include <Core/Core.h>

int main()
{

				Core::SetDriver(Core::Driver::OpenGL);
				Core::GLWindow::AppWindow.Init();
}