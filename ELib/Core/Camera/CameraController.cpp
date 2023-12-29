#include <epch.h>
#include "CameraController.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Core {

				void Camera::CalculateLookAt() {
								static glm::vec3 C_Up{ 0.f, 1.f, 0.f };
								m_CamData.Right = glm::normalize(glm::cross(C_Up, m_CamData.Direction));
								m_CamData.Up = glm::cross(m_CamData.Direction, m_CamData.Right);
								m_LookAt = glm::lookAt(m_CamData.Position, m_CamData.Position + m_CamData.Front, C_Up);
								if (!m_DefaultSet) {
												m_DefaultCamData = m_CamData;
												m_DefaultSet = true;
								}
				}

				void Camera::OrthographicView() {

				}

				void Camera::PerspectiveView() {
								m_ProjectionMtx = glm::perspective(glm::radians(m_CamData.m_Fov), 1.f, 0.f, 100.f);
				}

				Camera::Camera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height) {
								SetName(p_Name);
								m_CamData.Position = p_Position;
								m_CamData.Front = glm::vec3(0.f, 0.f, -1.f);
								SetCameraWindow(p_width, p_height);
				}


				void Camera::SetCameraWindow(float p_Width, float p_Height) {
								m_Dimensions.x = p_Width;
								m_Dimensions.y = p_Height;
								glm::vec3 scale = 2.f / m_Dimensions;
								m_CamWindowToNDC[0].x = scale.x;
								m_CamWindowToNDC[1].y = scale.y;
								m_CamWindowToNDC[2].z = 1.f;
								m_AspectRatio = p_Width / p_Height;
				}

				void Camera::SetTarget(glm::vec3 p_target) {
								m_CamData.Direction = glm::normalize(m_CamData.Position - p_target);
								m_CamData.Target = p_target;
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
												if (m_IsOrthagonal) {
												}
												else {
																m_CamData.m_Fov += p_value;
																if (m_CamData.m_Fov < 1.f) { m_CamData.m_Fov = 1.0f; }
																if (m_CamData.m_Fov > 60.f) { m_CamData.m_Fov = 60.f; }
												}
												break;
								case ENUM_Key_Actions::LEFT:
												m_CamData.Position += p_value * m_CamData.Front;
												break;
								case ENUM_Key_Actions::RIGHT:
												m_CamData.Position += p_value * m_CamData.Front;
												break;
								case ENUM_Key_Actions::UP:
												m_CamData.Position += glm::normalize(glm::cross(m_CamData.Front, m_CamData.Up)) * p_value;
												break;
								case ENUM_Key_Actions::DOWN:
												m_CamData.Position += glm::normalize(glm::cross(m_CamData.Front, m_CamData.Up)) * p_value;
												break;
								}

				}

				void Camera::SetKeyBind(int Key, Base_KeyMap instructions) {
								m_KeyBindings.SetKeyBinding(Key, instructions);
				}

				void Camera::Update(const std::shared_ptr<Core::Input>& p_inputsystem, double ddt) {
								float fdt = (float)ddt;
								m_KeyBindings.Update(p_inputsystem->GetCurrentSequence(), [&](Base_KeyMap instructions) {
												if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD)) {
																E_LOG_INFO("Zoom in");
																ApplyMovement(ENUM_Key_Actions::ZOOM, m_Movement.m_ZoomSpeed);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::BACKWARD)) {
																E_LOG_INFO("Zoom out");
																ApplyMovement(ENUM_Key_Actions::ZOOM, -m_Movement.m_ZoomSpeed);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::LEFT)) {
																E_LOG_INFO("Cam Left");
																ApplyMovement(ENUM_Key_Actions::LEFT, -m_Movement.m_MoveSpeed * fdt);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::RIGHT)) {
																E_LOG_INFO("Cam Right");
																ApplyMovement(ENUM_Key_Actions::RIGHT, m_Movement.m_MoveSpeed * fdt);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::UP)) {
																E_LOG_INFO("Cam Up");
																ApplyMovement(ENUM_Key_Actions::UP, m_Movement.m_MoveSpeed);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::DOWN)) {
																E_LOG_INFO("Cam Down");
																ApplyMovement(ENUM_Key_Actions::DOWN, -m_Movement.m_MoveSpeed);
												}
												if (instructions.CheckFlags(ENUM_Key_Actions::RESET)) {
																m_CamData = m_DefaultCamData;
												}
												});

								CalculateLookAt();
								if (m_IsOrthagonal) {
												OrthographicView();
								}
								else {
												PerspectiveView();
								}

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
