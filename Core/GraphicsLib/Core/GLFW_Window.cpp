#include <epch.h>
#include "Core.h"
#include "GLFW_Window.h"

namespace Core {


				void GLWindow::Init(int width, int height, const std::shared_ptr<Core::Input>& input) {

								int success = glfwInit();
								if (success == GLFW_FALSE) {
												return;
								}
								Dimension.x = static_cast<float>(width);
								Dimension.y = static_cast<float>(height);

								GLFWmonitor* monitor = glfwGetPrimaryMonitor();
								GLFWvidmode const* videoMode = glfwGetVideoMode(monitor);
								glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_Version[0]);
								glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_Version[1]);
								glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Modern oGL
								glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);					// Double buffering
								glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);				// Window color depth
								glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
								glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
								glfwWindowHint(GLFW_ALPHA_BITS, videoMode->redBits);			// Using same size as red
								glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);		// Refresh rate
								glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);						// Allow resizable
								m_aspect_ratio = 16.f / 9.f; // Width / Height


								m_pWindow = glfwCreateWindow(width, height, "Graphic Playground", NULL, NULL);
								if (!m_pWindow) {
												glfwTerminate();
												return;
								}
								// Set Callbacks
								glfwSetWindowSizeCallback(m_pWindow, Window_size_cb);
								glfwSetFramebufferSizeCallback(m_pWindow, Framebuffer_size_cb);



								glfwMakeContextCurrent(m_pWindow);
								glfwSetWindowUserPointer(m_pWindow, this);
								glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

								GLenum err = glewInit();
								if (GLEW_OK != err) {
												std::cerr << "Unable to init glew - error: " << glewGetErrorString(err) << "abort program" << std::endl;
												CleanUp();
												return;
								}
								if (GLEW_VERSION_4_5) {

								}
								else {
												std::cerr << "Driver does not support OpenGL 4.5 - abort program" << std::endl;
												CleanUp();
												return;
								}

				}


				void GLWindow::pollEvents() const noexcept {

				}
				void GLWindow::swapBuffers() const noexcept {

				}
				void GLWindow::CloseWindow() {
								glfwSetWindowShouldClose(m_pWindow, GLFW_FALSE);

				}

				glm::vec2 GLWindow::GetDimensions() {
								return Dimension;
				}
				void GLWindow::CleanUp() {
								glfwDestroyWindow(m_pWindow);
								glfwTerminate();
				}

				//////////////////////////////////////////////////////////////////
				///																																																												///
				///                 STATIC CALLBACK FUNCTIONS	                 ///
				///																																																												///
				//////////////////////////////////////////////////////////////////

				void GLWindow::Window_size_cb(GLFWwindow*, int, int) {

				}

				void GLWindow::Framebuffer_size_cb(GLFWwindow*, int width, int height) {

				}
}
