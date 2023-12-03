#include "epch.h"
#pragma once
#include "GLFW_Window.h"
#include "Input.h"


#define trace(msg) printf("%s\n", msg)

namespace Core {

				enum class Driver {
								OpenGL,
								Vulkan,
								Direct
				} static CurrentDriver;

				void SetDriver(Core::Driver = Core::Driver::OpenGL);


				struct GL_Core {
								std::shared_ptr<GLWindow> AppWindow;
								std::shared_ptr<Input> AppInput;
								GL_Core();
								~GL_Core();
								void Init(int width, int height);
								bool Run();
								void Next();
				};
}