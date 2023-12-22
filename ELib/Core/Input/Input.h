#pragma once
#include <Defines.h>
#include "Window/GLFW_Window.h"
#include <optional>
#include <bitset>




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
								void Reset();
								void key_cb(int key, int scancode, int action, int mod);
								void mousebutton_cb(int button, int action, int mod);
								void mousescroll_cb(double xoffset, double yoffset);
								void mousepos_cb(double xpos, double ypos);
								//void framebuffersize_cb();

								bool IsKeyPress(int key);
								bool IsKeyHold(int key);
								bool IsKeyPressHold(int key);

								//bool IsMousePress(int key);
								//bool IsMouseHold(int key);
								void IsMouseScroll();

				private:
								KeyInfo* findKey(int key);

								std::map<int, KeyInfo> m_KeyList;
								double mouse_scroll_x{}, mouse_scroll_y{};
								double mouse_pos_x{}, mouse_pos_y{};


				};

				template <typename T>
				class KeyMap {
								using UI = typename std::underlying_type<T>::type;
								T m_value;
				public:
								KeyMap() {}
								KeyMap(T p_value) { m_value = p_value; }
								KeyMap(const KeyMap<T>& p_value) { m_value = p_value.m_value; }
								T operator|(const T& p_value) { return static_cast<T>(static_cast<UI>(m_value) | static_cast<UI>(p_value)); }
								T operator&(const T& p_value) { return static_cast<T>(static_cast<UI>(m_value) & static_cast<UI>(p_value)); }
								void operator|=(const T& p_value) { m_value = static_cast<T>(static_cast<UI>(m_value) | static_cast<UI>(p_value)); }
								void operator&=(const T& p_value) { m_value = static_cast<T>(static_cast<UI>(m_value) & static_cast<UI>(p_value)); }
								void operator|=(const KeyMap<T>& p_value) { m_value = static_cast<T>(static_cast<UI>(m_value) | static_cast<UI>(p_value.m_value)); }
								void operator&=(const KeyMap<T>& p_value) { m_value = static_cast<T>(static_cast<UI>(m_value) & static_cast<UI>(p_value.m_value)); }

								friend bool operator<(const KeyMap<T>& lhs, const KeyMap<T>& rhs) { return static_cast<UI>(lhs.m_value) < static_cast<UI>(rhs.m_value); }
				public:
								inline bool IsSet(const T& p_value) {
												auto _ = (static_cast<UI>(m_value) & static_cast<UI>(p_value));
												return  _ != static_cast<UI>(0);
								}

				};

				//using Base_KeyMap = KeyMap<Base_Key_Actions>;
				using Base_KeyMap = std::bitset<static_cast<size_t>(Base_Key_Actions::MAX_FLAG)>;



				class KeyBinding : IBaseObject {
				protected:
								std::map<int, Base_KeyMap> m_BaseKeyActionMap;
				public:
								KeyBinding() {}
								void SetKeyBinding(int key, Base_KeyMap instruction);
								Base_KeyMap GetBaseKeyMap(int key);
								Base_KeyMap IsTriggered(const std::shared_ptr<Input>& InputSystem);
				};

}
