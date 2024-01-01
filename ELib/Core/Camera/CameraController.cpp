#include <epch.h>
#include "CameraController.h"
#include <glm/gtc/matrix_transform.hpp>
#include <functional>


namespace Core {
				float ZoomLerp(float start, float end, float t) {
								return start + t * (end - start);
				}

				void Camera::CalculateLookAt() {
								static glm::vec3 C_Up{ 0.f, 1.f, 0.f };
								m_CamData.Right = glm::normalize(glm::cross(C_Up, m_CamData.Direction));
								m_CamData.Up = glm::cross(m_CamData.Direction, m_CamData.Right);
								m_LookAt = glm::lookAt(m_CamData.Position, m_CamData.Position + m_CamData.Front, C_Up);
								if (!m_DefaultSet) {
												m_DefaultCamData = m_CamData;
												m_DefaultSet = true;
								}
								LimitZoom();
				}

				void Camera::CalculateOrthographicView() {
								float zoomfactor = m_CamData.m_Zoom;// / m_AspectRatio;
								float i_left = -zoomfactor;
								float i_right = zoomfactor;
								float i_bottom = -zoomfactor;
								float i_top = zoomfactor;
								float i_near = -1.f;
								float i_far = 150; // ORTHOGRAPHIC_ZOOM_UPPER_LIMIT;

								m_ProjectionMtx = glm::ortho(i_left, i_right, i_bottom, i_top, i_near, i_far);

				}

				void Camera::CalculatePerspectiveView() {
								m_ProjectionMtx = glm::perspective(glm::radians(m_CamData.m_Fov), 1.f, 0.f, 100.f);
				}

				Camera::Camera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height, glm::vec3 p_Target) {
								SetName(p_Name);
								m_CamData.Position = p_Position;
								m_CamData.Front = glm::vec3(0.f, 0.f, -1.f);
								SetCameraWindow(p_width, p_height);
								SetTarget(p_Target);
								m_CamData.m_Zoom = std::abs(p_Position.z);
				}


				void Camera::SetCameraWindow(float p_Width, float p_Height) {
								m_Dimensions.x = p_Width;
								m_Dimensions.y = p_Height;
								m_Dimensions.z = 1.f;
								glm::vec3 scale = 2.f / m_Dimensions;
								//m_CamWindowToNDC[0].x = scale.x;
								//m_CamWindowToNDC[1].y = scale.y;
								//m_CamWindowToNDC[2].z = 1.f;
								//m_CamWindowToNDC[3].w = 1.f;
								m_CamWindowToNDC = glm::scale(glm::mat4(1.f), scale);
								m_AspectRatio = p_Width / p_Height;
				}

				void Camera::SetTarget(glm::vec3 p_target) {
								m_CamData.Direction = glm::normalize(m_CamData.Position - p_target);
								m_CamData.Target = p_target;
				}

				void Camera::SetMovement(ENUM_Key_Actions actions, float p_value) {
								switch (actions) {
								case ENUM_Key_Actions::ROLL:
												m_Movement.m_RollSpeed = p_value;
												break;
								case ENUM_Key_Actions::YAW:
												m_Movement.m_YawSpeed = p_value;
												break;
								case ENUM_Key_Actions::PITCH:
												m_Movement.m_PitchSpeed = p_value;
												break;
								case ENUM_Key_Actions::ZOOM:
												m_Movement.m_ZoomSpeed = p_value;
												break;
								default:
												m_Movement.m_MoveSpeed = p_value;
												break;
								}
				}

				void Camera::Toggle3D(bool Is3D) {
								m_Is3D = Is3D;
				}
				void Camera::ToggleView(bool p_View) {
								m_IsOrthagonal = p_View;

				}

				void Camera::LimitZoom() {
								if (m_IsOrthagonal) {
												auto& zoom = m_CamData.m_Zoom;
												if (zoom < ORTHOGRAPHIC_ZOOM_LOWER_LIMIT) {
																zoom = ORTHOGRAPHIC_ZOOM_LOWER_LIMIT;
												}
												else if (zoom > ORTHOGRAPHIC_ZOOM_UPPER_LIMIT) {
																zoom = ORTHOGRAPHIC_ZOOM_UPPER_LIMIT;
												}
								}
								else {
												auto& zoom = m_CamData.m_Fov;
												if (zoom < PERSPECTIVE_FOV_LOWER_LIMIT) {
																zoom = PERSPECTIVE_FOV_LOWER_LIMIT;
												}
												if (zoom > PERSPECTIVE_FOV_UPPER_LIMIT) {
																zoom = PERSPECTIVE_FOV_UPPER_LIMIT;
												}
								}
				}

				void Camera::ApplyMovement(ENUM_Key_Actions actions, float p_value) {
								const float nearThreshold = 0.5f; // Threshold to start slowing down zoom
								const float farThreshold = 0.9f; // Threshold to cap zoom increase
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
																m_CamData.m_Zoom += p_value;
												}
												else {
																m_CamData.m_Fov += p_value;
												}
												break;
								case ENUM_Key_Actions::LEFT:
												m_CamData.Position.x += p_value;
												m_CamData.Target.x += p_value;
												break;
								case ENUM_Key_Actions::RIGHT:
												m_CamData.Position.x += p_value;
												m_CamData.Target.x += p_value;
												break;
								case ENUM_Key_Actions::UP:
												m_CamData.Position.y += p_value;// glm::normalize(glm::cross(m_CamData.Front, m_CamData.Up))* p_value;
												break;
								case ENUM_Key_Actions::DOWN:
												m_CamData.Position.y += p_value; // glm::normalize(glm::cross(m_CamData.Front, m_CamData.Up))* p_value;
												break;
								}

				}

				void Camera::SetKeyBind(int Key, Base_KeyMap instructions) {
								m_KeyBindings.SetKeyBinding(Key, instructions);
				}

				void Camera::Update(double ddt) {
								float fdt = (float)ddt;

								KEY_TRIGGER_START(m_KeyBindings);
								KeyMapInstructions(instructions, fdt);
								KEY_TRIGGER_END;


								CalculateLookAt();
								if (m_IsOrthagonal) {
												CalculateOrthographicView();
								}
								else {
												CalculatePerspectiveView();
								}

				}

				void Camera::KeyMapInstructions(Base_KeyMap instructions, float fdt) {
								if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD)) {
												auto i_zoomspeed = m_Movement.m_ZoomSpeed;
												ApplyMovement(ENUM_Key_Actions::ZOOM, i_zoomspeed);
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::BACKWARD)) {
												auto i_zoomspeed = -m_Movement.m_ZoomSpeed;
												ApplyMovement(ENUM_Key_Actions::ZOOM, i_zoomspeed);
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::LEFT)) {
												ApplyMovement(ENUM_Key_Actions::LEFT, -m_Movement.m_MoveSpeed);
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::RIGHT)) {
												ApplyMovement(ENUM_Key_Actions::RIGHT, m_Movement.m_MoveSpeed);
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::UP)) {
												ApplyMovement(ENUM_Key_Actions::UP, m_Movement.m_MoveSpeed);
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::DOWN)) {
												ApplyMovement(ENUM_Key_Actions::DOWN, -m_Movement.m_MoveSpeed);
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::RESET)) {
												m_CamData = m_DefaultCamData;
								}
								if (instructions.CheckFlags(ENUM_Key_Actions::TOGGLE, ENUM_Key_Actions::VIEW)) {
												static bool view = false;
												view = view ? false : true;
												ToggleView(view);
								}

				}

}

namespace Core {

				CameraManager::CameraManager() {
				}

				CameraManager::~CameraManager() {
								for (auto& [cam_name, cam] : m_CameraList) {
												delete cam;
								}
				}

				void CameraManager::AddCamera(Camera* p_cam) {
								m_CameraList[p_cam->GetName()] = std::move(p_cam);
								m_CurrentCamera = p_cam->GetName();
				}

				void CameraManager::Update(double p_deltatime) {
								this->GetCurrentCamera()->Update(p_deltatime);

				}

				Camera* CameraManager::GetCurrentCamera() {
								return m_CameraList[m_CurrentCamera];
				}

}
