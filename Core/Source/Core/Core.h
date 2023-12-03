#include "epch.h"
#pragma once
#include "GLFW_Window.h"


#define trace(msg) printf("%s\n", msg)

namespace Core {
				template <typename T>
				using SRef = std::shared_ptr<T>;

				enum class Driver {
								OpenGL,
								Vulkan,
								Direct
				} static CurrentDriver;
				void SetDriver(Core::Driver = Core::Driver::OpenGL);
				void Init();
}