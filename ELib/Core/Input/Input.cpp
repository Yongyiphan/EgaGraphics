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

				void Input::Reset() {
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
				}

				void Input::mousebutton_cb(int button, int action, int mod) {
								KeyInfo* m_key = findKey(button);
								m_key->key = button;
								m_key->p_action = m_key->c_action;
								m_key->c_action = action;
								m_key->mod = mod;
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
								KeyInfo* fkey = findKey(key);
								bool correct = (fkey && (fkey->p_action == GLFW_PRESS && fkey->c_action == GLFW_RELEASE)) ? true : false;
								if (fkey && fkey->c_action == GLFW_RELEASE) {
												fkey->Reset();
								}
								return correct;
				}

				bool Input::IsKeyHold(int key) {
								KeyInfo* fkey = findKey(key);
								bool _true = (fkey && (fkey->c_action == GLFW_REPEAT || fkey->c_action == GLFW_PRESS)) ? true : false;
								if (fkey && fkey->c_action == GLFW_RELEASE) {
												fkey->Reset();
								}
								return _true;
				}

				bool Input::IsKeyPressHold(int key) {
								return IsKeyPress(key) || IsKeyHold(key);
				}

				void Input::IsMouseScroll() {}




				KeyInfo* Input::findKey(int key) {
								return &m_KeyList[key];
				}

				Base_KeyMap KeyBinding::IsTriggered(const std::shared_ptr<Input>& p_InputSystem) {
								Base_KeyMap Instructions(Base_Key_Actions::NONE);
								for (auto& [key, _] : m_BaseKeyActionMap) {
												if (p_InputSystem->IsKeyPressHold(key)) {
																Instructions |= _;
												}
								}
								return Instructions;

				}


				void KeyBinding::SetKeyBinding(int key, Base_KeyMap instruction) {
								m_BaseKeyActionMap[key] = instruction;

				}

				Base_KeyMap KeyBinding::GetBaseKeyMap(int p_key) {

								if (m_BaseKeyActionMap.find(p_key) != m_BaseKeyActionMap.end()) {
												return m_BaseKeyActionMap[p_key];
								}
								return Base_KeyMap(Base_Key_Actions::NONE);
				}
}
