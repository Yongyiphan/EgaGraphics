#include <epch.h>
#include "Input.h"


namespace Core {

				Input::Input() {
								EventDispatcher::GetInstance().RegisterEvent(
												new Event<int, int, int, int>(GL_CORE_EVENT_KEYPRESS,
																[&](int key, int scancode, int action, int mod) {
																				key_cb(key, scancode, action, mod);
																}));
								EventDispatcher::GetInstance().RegisterEvent(
												new Event<int, int, int>(GL_CORE_EVENT_MOUSEBUTTON,
																[&](int button, int action, int mod) {
																				mousebutton_cb(button, action, mod);
																}));
								EventDispatcher::GetInstance().RegisterEvent(
												new Event<double, double>(GL_CORE_EVENT_MOUSESCROLL,
																[&](double xoffset, double yoffset) {
																				mousescroll_cb(xoffset, yoffset);
																}));
								EventDispatcher::GetInstance().RegisterEvent(
												new Event<double, double>(GL_CORE_EVENT_MOUSEPOSITION,
																[&](double xpos, double ypos) {
																				mousepos_cb(xpos, ypos);
																}));
				}

				void Input::key_cb(int key, int scancode, int action, int mod) {}
				void Input::mousebutton_cb(int button, int action, int mod) {}
				void Input::mousescroll_cb(double xoffset, double yoffset) {}
				void Input::mousepos_cb(double xpos, double ypos) {
								std::cout << "Xpos: (" << xpos << " | " << ypos << ")\n";
				}
}
