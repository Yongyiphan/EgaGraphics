#include <epch.h>
#include "Imgui/EImgui.h"

namespace Core {
				void EImGui::Init(GLFWwindow* p_window) {
								IMGUI_CHECKVERSION();
								ImGui::CreateContext();
								ImGuiIO& io = ImGui::GetIO();
								(void)io;
#ifdef ELIB_OPENGL 
								ImGui_ImplGlfw_InitForOpenGL(p_window, true);
								ImGui_ImplOpenGL3_Init("#version 330");
#endif // ELIB_OPENGL
				}


				void EImGui::StartFrame() {
#ifdef ELIB_OPENGL 
								ImGui_ImplOpenGL3_NewFrame();
#endif
								ImGui_ImplGlfw_NewFrame();
								ImGui::NewFrame();
				}

				void EImGui::EndFrame() {
								ImGui::Render();
#ifdef ELIB_OPENGL 

								ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
				}


				void EImGui::CleanUp() {
#ifdef ELIB_OPENGL 
								ImGui_ImplOpenGL3_Shutdown();
#endif // ELIB_OPENGL
								ImGui_ImplGlfw_Shutdown();
								ImGui::DestroyContext();
				}
}
