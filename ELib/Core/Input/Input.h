#pragma once
#include <Defines.h>
#include "Window/GLFW_Window.h"
#include <optional>




namespace Core {
				struct KeyInfo {
								int key;
								int scancode;
								int p_action;
								int c_action;
								int mod;
								void Reset() { p_action = -1; c_action = -1; }
				};

				class Input {
				public:
								Input();
								void key_cb(int key, int scancode, int action, int mod);
								void mousebutton_cb(int button, int action, int mod);
								void mousescroll_cb(double xoffset, double yoffset);
								void mousepos_cb(double xpos, double ypos);
								//void framebuffersize_cb();

								bool IsKeyPress(int key);
								bool IsKeyHold(int key);

								bool IsMousePress(int key);
								bool IsMouseHold(int key);
								void IsMouseScroll();


				private:

								KeyInfo* findKey(int key);

								std::map<int, KeyInfo> m_KeyList;
								double mouse_scroll_x{}, mouse_scroll_y{};
								double mouse_pos_x{}, mouse_pos_y{};

				};

}
