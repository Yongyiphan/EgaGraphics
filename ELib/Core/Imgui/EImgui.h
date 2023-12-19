#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#ifdef ELIB_OPENGL 
#include <backends/imgui_impl_opengl3.h>
#endif // ELIB_OPENGL
#include <GLFW/glfw3.h>


namespace Core {


				class EImGui {
				public:
								void Init(GLFWwindow* p_window);
								void StartFrame();
								void EndFrame();
								void CleanUp();
								void RenderFramebuffer(ImTextureID) {}
				};
}
