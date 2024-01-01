#pragma once
#ifndef CORE_H
#define CORE_H
#include "Defines.h"
#include "Window/GLFW_Window.h"
#include "Imgui/EImgui.h"
#include "Input/Input.h"
#include "Shader/Shader.h"
#include "Camera/CameraController.h"
#include "Camera/Cameras.h"
#include "Graphics.h"
#include "ECS/ECS.h"


namespace Core {

				class GL_Core {
				private:
								_CrtMemState sOld{};
								_CrtMemState sNew{};
								_CrtMemState sDiff{};
				private:
								glm::vec3 m_BGColor{};
								double m_Deltatime{};
								std::string FPS_title_addons{};
								std::string Cam_View_title_addons{};
								void SetFPS_Title();
								void SetCamera_View_Title();
				public:
								std::shared_ptr<GLWindow> AppWindow;
								std::shared_ptr<Input> AppInput;
								std::shared_ptr<CameraManager> AppCamera;
								std::shared_ptr<EImGui> EImGui;

								GL_Core();
								~GL_Core();
								void Init(int width, int height);
								bool Run();
								void Next();
								void SetupShaders();
								void SetupModels();
								void SetBackgroundColor(float r, float g, float b);
								glm::vec3 GetBackgroundColor();
								void StartFrame();
								void EndFrame();
								inline double GetDeltaTime() { return m_Deltatime; }
				};


}

#endif //CORE_H
