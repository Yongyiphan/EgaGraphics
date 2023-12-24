#include <epch.h>
#include "CameraController.h"


namespace Core {

				void Camera::CalculateLookAt() {
								static glm::vec3 C_Up{ 0.f, 1.f, 0.f };

				}

				Camera::Camera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height) {
								SetName(p_Name);
								m_Position = p_Position;
								SetCameraWindow(p_width, p_height);
				}


				void Camera::SetCameraWindow(float p_Width, float p_Height) {
								m_Dimensions.x = p_Width;
								m_Dimensions.y = p_Height;
								glm::vec3 scale = 2.f / m_Dimensions;
								m_CamWindowToNDC[0].x = scale.x;
								m_CamWindowToNDC[1].y = scale.y;
								m_CamWindowToNDC[2].z = scale.z;
								m_AspectRatio = p_Width / p_Height;
				}

				void Camera::SetMovement(ENUM_Key_Actions actions, float p_value) {
								switch (actions) {
								case ENUM_Key_Actions::ROLL:
												m_Movement.m_Roll = p_value;
												break;
								case ENUM_Key_Actions::YAW:
												m_Movement.m_Yaw = p_value;
												break;
								case ENUM_Key_Actions::PITCH:
												m_Movement.m_Pitch = p_value;
												break;
								case ENUM_Key_Actions::ZOOM:
												m_Movement.m_ZoomSpeed = p_value;
												break;
								default:
												m_Movement.m_MoveSpeed = p_value;
												break;
								}
				}

				void Camera::ApplyMovement(ENUM_Key_Actions actions, float p_value) {
								switch (actions) {
								case ENUM_Key_Actions::ROLL:
												m_CamData.m_Roll += p_value;
												break;
								case ENUM_Key_Actions::YAW:
												m_CamData.m_Yaw += p_value;
												break;
								case ENUM_Key_Actions::PITCH:
												m_CamData.m_Pitch += p_value;
												break;
								case ENUM_Key_Actions::ZOOM:
												m_CamData.m_Zoom += p_value;
												break;
								case ENUM_Key_Actions::LEFT:
												m_Position.x += p_value;
												break;
								case ENUM_Key_Actions::RIGHT:
												m_Position.x += p_value;
												break;
								case ENUM_Key_Actions::UP:
												m_Position.y += p_value;
												break;
								case ENUM_Key_Actions::DOWN:
												m_Position.y += p_value;
												break;
								}

				}

				void Camera::SetKeyBind(int Key, Base_KeyMap instructions) {
								m_KeyBindings.SetKeyBinding(Key, instructions);
				}

				void Camera::Update(const std::shared_ptr<Core::Input>& p_inputsystem, double) {
								m_KeyBindings.Update(p_inputsystem->GetCurrentSequence(), [&](Base_KeyMap instructions) {
												if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD)) {
																E_LOG_INFO("Zoom in");
																ApplyMovement(ENUM_Key_Actions::ZOOM, m_Movement.m_ZoomSpeed);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::BACKWARD)) {
																E_LOG_INFO("Zoom out");
																ApplyMovement(ENUM_Key_Actions::ZOOM, -m_Movement.m_ZoomSpeed);
												}
												});

				}

}

namespace Core {

				CameraManager::CameraManager() {
				}

				void CameraManager::AddCamera(Camera* p_cam) {
								m_CameraList[p_cam->GetName()] = std::move(p_cam);
								m_CurrentCamera = p_cam->GetName();
				}

				void CameraManager::Update(const std::shared_ptr<Core::Input>& p_input, double p_deltatime) {
								this->GetCurrentCamera()->Update(p_input, p_deltatime);

				}

				Camera* CameraManager::GetCurrentCamera() {
								return m_CameraList[m_CurrentCamera];
				}

}
