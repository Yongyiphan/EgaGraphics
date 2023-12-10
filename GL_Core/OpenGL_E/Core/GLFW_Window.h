#pragma once
#include <epch.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

struct GLFWwindow;

namespace Core {
				class Input;
				class GLWindow {
				public:
								enum class WindowMode {
												WINDOWED = 0,
												FULLSCREEN,
												BORDERLESS_WINDOWED,
												BORDERLESS_FULLSCREEN
								};

								GLWindow();
								~GLWindow() {};
								void Init(int width, int height);
								void CleanUp();
								void pollEvents() const noexcept;
								void swapBuffers() const noexcept;
								bool ShouldClose() const noexcept;
								void CloseWindow() const noexcept;

								glm::vec2 GetDimensions();
								void SetDimensions(int, int);

								inline GLFWwindow* GetWindow() { return m_pWindow; }

				private:
								glm::vec2 Dimension{};
								int GL_Version[2] = { 4,5 };
								float m_aspect_ratio{ 16.f / 9.f };
								GLFWwindow* m_pWindow{ nullptr };
				};
}
