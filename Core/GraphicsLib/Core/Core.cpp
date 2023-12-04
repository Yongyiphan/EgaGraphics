#include <epch.h>
#include "Core.h"

#include <iostream>

namespace Core {


				void SetDriver(Core::Driver SelectedDriver) {
								CurrentDriver = SelectedDriver;
				}

				GL_Core::GL_Core() {
								AppWindow = std::make_shared<Core::GLWindow>();
								AppInput = std::make_shared<Core::Input>();
				}

				void GL_Core::Init(int width, int height) {
								AppWindow->Init(width, height);
				}

				GL_Core::~GL_Core() {
								AppWindow->CleanUp();

				}

				bool GL_Core::Run() {
								bool close = !AppWindow->ShouldClose();
								return close;
				}

				void GL_Core::Next() {
								AppWindow->swapBuffers();
								AppWindow->pollEvents();
				}

}