#pragma once
#include "../epch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

struct GLFWwindow;

namespace Core {


				class GLWindow {
				public:
								enum class WindowMode {
												WINDOWED = 0,
												FULLSCREEN,
												BORDERLESS_WINDOWED,
												BORDERLESS_FULLSCREEN
								};

								GLWindow() {};
								~GLWindow() {};
								void Init();
								bool shouldClose() const noexcept;
								void pollEvents() const noexcept;
								void swapBuffers() const noexcept;

								glm::vec2 GetDimensions();
								static GLWindow AppWindow;


				private:
								glm::vec2 Dimension{};
								glm::vec2 Version{};
								float m_aspect_ratio{ 16.f / 9.f };
								GLFWwindow* m_pWindow{ nullptr };
				};
}
