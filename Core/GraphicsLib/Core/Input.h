#pragma once
#include "GLFW_Window.h"


namespace Core {
				class Input {
				public:
								Input();
								void key_cb(int key, int scancode, int action, int mod);
								void mousebutton_cb(int button, int action, int mod);
								void mousescroll_cb(double xoffset, double yoffset);
								void mousepos_cb(double xpos, double ypos);
								//void framebuffersize_cb();
				};

}
