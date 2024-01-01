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

				class Input : public ISingleton<Input> {
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
								inline std::map<int, KeyInfo*>& GetCurrentSequence() { return ActiveButtonSequence; }

				private:
								KeyInfo* findKey(int key);

								std::map<int, KeyInfo> m_KeyList;
								double mouse_scroll_x{}, mouse_scroll_y{};
								double mouse_pos_x{}, mouse_pos_y{};

								std::map<int, KeyInfo*> ActiveButtonSequence;


				};


				template<typename T, size_t N>
				class KeyMap {
								using KM = std::bitset<N>;
								KM m_value{};
				public:
								KeyTriggerType m_TriggerType{ KeyTriggerType::CLICK };
								KeyMap() = default;
								KeyMap(KeyTriggerType p_triggertype, const T& singleFlag) {
												SetFlags(singleFlag);
												m_TriggerType = p_triggertype;
								}
								template<typename... Enums>
								KeyMap(KeyTriggerType p_triggertype, Enums... flags) {
												SetFlags(flags...);
												m_TriggerType = p_triggertype;
								}

								template <typename... Enums>
								void Set(Enums... flags) {
												m_value |= (KM(flags) | ...);
								}

								template <typename... Enums>
								bool CheckFlags(Enums...flags) {
												return (m_value[STCast(flags)] && ...);
								}

								template<typename... Enums>
								void SetFlags(Enums... flags) {
												(m_value.set(STCast(flags)), ...);
								}

				};



				using Base_KeyMap = KeyMap<ENUM_Key_Actions, STCast(ENUM_Key_Actions::MAX_FLAG)>;



				class KeyBinding : IBaseObject {
				protected:
								std::map<int, Base_KeyMap> m_BaseKeyActionMap;
								std::vector<Base_KeyMap> m_TriggeredKeys;
				public:
								KeyBinding() {}
								virtual void Init() {}
								void SetKeyBinding(int key, Base_KeyMap instruction);

								std::vector<Base_KeyMap> GetTriggered() {
												m_TriggeredKeys.clear();
												auto& i_Input = Input::GetInstance();
												auto& KeySequence = i_Input.GetCurrentSequence();;
												for (auto [key, _] : KeySequence) {
																if (m_BaseKeyActionMap.find(key) != m_BaseKeyActionMap.end()) {
																				auto& instructions = m_BaseKeyActionMap[key];
																				bool triggered = false;
																				switch (instructions.m_TriggerType) {
																				case KeyTriggerType::CLICK:
																								if (i_Input.IsKeyPress(key)) triggered = true;
																								break;
																				case KeyTriggerType::HOLD:
																								if (i_Input.IsKeyHold(key)) triggered = true;
																								break;
																				case KeyTriggerType::CLICK_HOLD:
																								if (i_Input.IsKeyPressHold(key)) triggered = true;
																								break;
																				}
																				if (triggered) {
																								m_TriggeredKeys.push_back(m_BaseKeyActionMap[key]);
																				}
																}
												}
												return m_TriggeredKeys;
								}
				};

}
