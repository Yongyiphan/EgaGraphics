#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include "ImGuiHelper.h"
#include <Graphics.h>
#ifdef ELIB_OPENGL 
#include <backends/imgui_impl_opengl3.h>
#endif // ELIB_OPENGL


namespace Core {


				class EImGui {
				public:
								void Init(GLFWwindow* p_window);
								void StartFrame();
								void EndFrame();
								void CleanUp();
				public:
								void RenderStatsTracker();
								void RenderFramebuffer(GL_Graphics::FrameBuffer, glm::vec2 target_size);
				};
}
