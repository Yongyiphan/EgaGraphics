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

				//////////////////////////////////////////////////////////////////
				///																																																												///
				///																				INPUT	CALL BACKS																					   ///
				///																																																												///
				//////////////////////////////////////////////////////////////////

				void Input::key_cb(int key, int scancode, int action, int mod) {
								KeyInfo* m_key = findKey(key);
								m_key->scancode = scancode;
								m_key->p_action = m_key->c_action;
								m_key->c_action = action;
								m_key->mod = mod;

								//std::cout << key << ": " << action << std::endl;
				}

				void Input::mousebutton_cb(int button, int action, int mod) {
								KeyInfo* m_key = findKey(button);
								m_key->p_action = m_key->c_action;
								m_key->c_action = action;
								m_key->mod = mod;
								std::cout << button << ": " << action << std::endl;
				}

				void Input::mousescroll_cb(double xoffset, double yoffset) {
								mouse_scroll_x = xoffset;
								mouse_scroll_y = yoffset;
				}

				void Input::mousepos_cb(double xpos, double ypos) {
								mouse_pos_x = xpos;
								mouse_pos_y = ypos;
								//std::cout << "Xpos: (" << xpos << " | " << ypos << ")\n";
				}

				bool Input::IsKeyPress(int key) {
								KeyInfo* fkey = findKey(key);
								bool correct = (fkey && (fkey->p_action == GLFW_PRESS && fkey->c_action == GLFW_RELEASE)) ? true : false;
								if (fkey && fkey->c_action == GLFW_RELEASE) {
												//std::cout << fkey->key << ": " << fkey->c_action << std::endl;
												fkey->Reset();
								}
								return correct;
				}

				bool Input::IsKeyHold(int key) {
								KeyInfo* fkey = findKey(key);
								bool _true = (fkey && (fkey->c_action == GLFW_REPEAT || fkey->c_action == GLFW_PRESS)) ? true : false;
								if (fkey && fkey->c_action == GLFW_RELEASE) {
												//std::cout << fkey->key << ": " << fkey->c_action << std::endl;
												fkey->Reset();
								}
								return _true;
				}

				void Input::IsMouseScroll() {}


				KeyInfo* Input::findKey(int key) {
								return &m_KeyList[key];
				}

}
