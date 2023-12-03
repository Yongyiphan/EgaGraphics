#pragma once
#include "GLFW_Window.h"


namespace Core {
				class Input {
				public:
								static void key_cb(GLWindow* pwin, int key, int scancode, int action, int mod) {};
								static void mousebutton_cb() {};
								static void mousescroll_cb() {};
								static void mousepos_cb() {};
								static void framebuffersize_cb() {};


				};

}
