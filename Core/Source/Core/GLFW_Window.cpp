#include <epch.h>
#include "Core.h"
#include "GLFW_Window.h"

namespace Core {

				GLWindow GLWindow::AppWindow{};

				void GLWindow::Init() {

								int success = glfwInit();
								if (success == GLFW_FALSE) {
												return;
								}

								GLFWmonitor* monitor = glfwGetPrimaryMonitor();
								GLFWvidmode const* videoMode = glfwGetVideoMode(monitor);
								glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
								glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
								glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Modern oGL
								glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);					// Double buffering
								glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);				// Window color depth
								glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
								glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
								glfwWindowHint(GLFW_ALPHA_BITS, videoMode->redBits);			// Using same size as red
								glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);		// Refresh rate
								glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);						// Allow resizable
								m_aspect_ratio = 16.f / 9.f; // Width / Height


								m_pWindow = glfwCreateWindow(static_cast<int>(Dimension.x), static_cast<int>(Dimension.y), "Graphic Playground", monitor, nullptr);


				}

				bool GLWindow::shouldClose() const noexcept { return false; }

				void GLWindow::pollEvents() const noexcept {

				}
				void GLWindow::swapBuffers() const noexcept {

				}

				glm::vec2 GLWindow::GetDimensions() {
								return Dimension;
				}
}
