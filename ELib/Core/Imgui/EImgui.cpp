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

				void EImGui::RenderStatsTracker() {

								const char* WindowName = "Render Stats";
								ImGui::Begin(WindowName, NULL);
								Core::RenderStat& StatTracker = Core::RenderStat::GetInstance();

								ImVec2 GUISize(150, 0);
								float rowHeight = 50;
								for (auto [m_type, stat] : StatTracker.GetTrackList()) {
												ImGui::Text("%s: %d", Core::RenderStat::RenderStatToString(m_type).c_str(), stat);
												GUISize.y += rowHeight;
								}
								ImGui::SetWindowSize(WindowName, GUISize);

								StatTracker.Reset();
								ImGui::End();

				}

				void EImGui::RenderFramebuffer(GL_Graphics::FrameBuffer p_FrameBuffer, glm::vec2 target_size) {
								ImGuiWindowFlags Flags{};
								Flags |= ImGuiWindowFlags_NoScrollbar;
								Flags |= ImGuiWindowFlags_NoScrollWithMouse;
								ImGui::Begin(p_FrameBuffer.GetName().c_str(), NULL, Flags);
								ImVec2 WindowSize(target_size.x, target_size.y);
								ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
								ImGui::BeginChild(p_FrameBuffer.GetName().c_str(), WindowSize, NULL, Flags);
								ImGui::Image((ImTextureID)p_FrameBuffer.GetColorAttachment(0), WindowSize, ImVec2(0, 1), ImVec2(1, 0));
								ImGui::EndChild();
								ImGui::PopStyleVar();
								ImGui::End();
				}

}
