#pragma once
#ifndef CORE_H
#define CORE_H
#include "Defines.h"
#include "GLFW_Window.h"
#include "Input.h"
#include "Shader/Shader.h"



namespace Core {



				struct GL_Core {
								std::shared_ptr<GLWindow> AppWindow;
								std::shared_ptr<Input> AppInput;
								std::shared_ptr<GL_Graphics::ShaderManager> GLShader;

								GL_Core();
								~GL_Core();
								void Init(int width, int height);
								bool Run();
								void Next();
								void SetupShaders();
				};


}

#endif //CORE_H
