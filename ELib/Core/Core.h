#pragma once
#ifndef CORE_H
#define CORE_H
#include "Defines.h"
#include "Window/GLFW_Window.h"
#include "Input/Input.h"
#include "Shader/Shader.h"
#include "Graphics.h"
#include "ECS/ECS.h"


namespace Core {



				class GL_Core {
								glm::vec3 m_BGColor{};
				public:
								std::shared_ptr<GLWindow> AppWindow;
								std::shared_ptr<Input> AppInput;

								GL_Core();
								~GL_Core();
								void Init(int width, int height);
								bool Run();
								void Next();
								void SetupShaders();
								void SetupModels();
								void SetBackgroundColor(float r, float g, float b);
				};


}

#endif //CORE_H
