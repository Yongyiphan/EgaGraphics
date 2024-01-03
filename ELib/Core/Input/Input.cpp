#include <epch.h>
#include "Input.h"


namespace Core {
				auto& IM = Core::Input::GetInstance();

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

				void Input::Reset() {
								for (auto it = IM.ActiveButtonSequence.begin(); it != IM.ActiveButtonSequence.end();) {
												if (it->second->c_action == GLFW_RELEASE) {
																it = IM.ActiveButtonSequence.erase(it);
												}
												else {
																++it;
												}
								}
				}

				//////////////////////////////////////////////////////////////////
				///																																																												///
				///																				INPUT	CALL BACKS																					   ///
				///																																																												///
				//////////////////////////////////////////////////////////////////

				void Input::key_cb(int key, int scancode, int action, int mod) {
								KeyInfo* m_key = findKey(key);
								m_key->key = key;
								m_key->scancode = scancode;
								m_key->p_action = m_key->c_action;
								m_key->c_action = action;
								m_key->mod = mod;
								ActiveButtonSequence[key] = m_key;
				}

				void Input::mousebutton_cb(int button, int action, int mod) {
								KeyInfo* m_key = findKey(button);
								m_key->key = button;
								m_key->p_action = m_key->c_action;
								m_key->c_action = action;
								m_key->mod = mod;
								ActiveButtonSequence[button] = m_key;
				}

				void Input::mousescroll_cb(double xoffset, double yoffset) {
								mouse_scroll_x = xoffset;
								mouse_scroll_y = yoffset;
				}

				void Input::mousepos_cb(double xpos, double ypos) {
								mouse_pos_x = xpos;
								mouse_pos_y = ypos;
				}


				bool Input::IsKeyPress(int key) {
								KeyInfo* fkey = IM.findKey(key);
								bool correct = (fkey && (fkey->p_action == GLFW_PRESS && fkey->c_action == GLFW_RELEASE)) ? true : false;
								if (fkey && fkey->c_action == GLFW_RELEASE) {
												fkey->Reset();
								}
								return correct;
				}

				bool Input::IsKeyHold(int key) {
								KeyInfo* fkey = IM.findKey(key);
								bool _true = (fkey && (fkey->c_action == GLFW_REPEAT || fkey->c_action == GLFW_PRESS)) ? true : false;
								if (fkey && fkey->c_action == GLFW_RELEASE) {
												fkey->Reset();
								}
								return _true;
				}

				bool Input::IsKeyPressHold(int key) {
								return IsKeyPress(key) || IsKeyHold(key);
				}

				bool Input::IsMouseScroll() { return false; }




				KeyInfo* Input::findKey(int key) {
								return &m_KeyList[key];
				}

				void KeyBinding::SetKeyBinding(int key, Base_KeyMap instruction) {
								m_BaseKeyActionMap[key] = instruction;
				}

}
