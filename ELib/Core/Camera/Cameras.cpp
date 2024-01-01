#include <epch.h>
#include "Cameras.h"


namespace Core {
				SampleCamera::SampleCamera() {
								SetUp();
				}

				SampleCamera::SampleCamera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height, glm::vec3 p_Target) :
								Camera(p_Name, p_Position, p_width, p_height, p_Target) {
								SetUp();
				}

				void SampleCamera::SetUp() {
								SetKeyBind(GLFW_KEY_Z, { KeyTriggerType::CLICK_HOLD, ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD });
								SetKeyBind(GLFW_KEY_X, { KeyTriggerType::CLICK_HOLD, ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::BACKWARD });
								SetKeyBind(GLFW_KEY_LEFT, { KeyTriggerType::CLICK_HOLD,ENUM_Key_Actions::LEFT });
								SetKeyBind(GLFW_KEY_RIGHT, { KeyTriggerType::CLICK_HOLD,ENUM_Key_Actions::RIGHT });
								SetKeyBind(GLFW_KEY_UP, { KeyTriggerType::CLICK_HOLD,ENUM_Key_Actions::UP });
								SetKeyBind(GLFW_KEY_DOWN, { KeyTriggerType::CLICK_HOLD,ENUM_Key_Actions::DOWN });
								SetKeyBind(GLFW_KEY_R, { KeyTriggerType::CLICK, ENUM_Key_Actions::RESET });
								SetKeyBind(GLFW_KEY_I, { KeyTriggerType::CLICK, ENUM_Key_Actions::TOGGLE, ENUM_Key_Actions::VIEW });
								SetMovement(ENUM_Key_Actions::LEFT, 10.f);
								SetMovement(ENUM_Key_Actions::ZOOM, 1.f);
				}
}
