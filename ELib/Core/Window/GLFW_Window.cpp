#include <epch.h>
#include "Core.h"
#include "GLFW_Window.h"
#include "Event/Event.h"

namespace Core {

				GLWindow::GLWindow() {

								EventDispatcher::GetInstance().RegisterEvent(
												new Event<int, int>(GL_CORE_EVENT_WINDOW_RESIZE, [&](int w, int h) {
																SetDimensions(w, h);
																})
								);
				}

				void GLWindow::Init(int width, int height) {

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
								glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow*, int width, int height) {
												EventDispatcher::GetInstance().DispatchEvent(GL_CORE_EVENT_WINDOW_RESIZE, width, height);
												});

								glfwSetKeyCallback(m_pWindow, [](GLFWwindow*, int key, int scancode, int action, int mods) {
												EventDispatcher::GetInstance().DispatchEvent(GL_CORE_EVENT_KEYPRESS, key, scancode, action, mods);
												EventDispatcher::GetInstance().DispatchEvent(GL_CORE_EVENT_KEYPRESS, key);
												});

								glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow*, int button, int action, int mod) {
												EventDispatcher::GetInstance().DispatchEvent(GL_CORE_EVENT_MOUSEBUTTON, button, action, mod);
												});


								glfwSetScrollCallback(m_pWindow, [](GLFWwindow*, double xoffset, double yoffset) {
												EventDispatcher::GetInstance().DispatchEvent(GL_CORE_EVENT_MOUSESCROLL, xoffset, yoffset);
												});

								glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow*, double xpos, double ypos) {
												EventDispatcher::GetInstance().DispatchEvent(GL_CORE_EVENT_MOUSEPOSITION, xpos, ypos);
												});


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
								glfwPollEvents();
				}
				void GLWindow::swapBuffers() const noexcept {
								glfwSwapBuffers(m_pWindow);

				}
				bool GLWindow::ShouldClose() const noexcept {
								return glfwWindowShouldClose(m_pWindow);

				}
				void GLWindow::CloseWindow() const noexcept {
								glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
				}

				glm::vec2 GLWindow::GetDimensions() {
								return Dimension;
				}
				void GLWindow::SetDimensions(int w, int h) {
								Dimension.x = static_cast<float>(w);
								Dimension.y = static_cast<float>(h);
								glViewport(0, 0, w, h);
				}

				void GLWindow::CleanUp() {
								glfwDestroyWindow(m_pWindow);
								glfwTerminate();
				}

}
