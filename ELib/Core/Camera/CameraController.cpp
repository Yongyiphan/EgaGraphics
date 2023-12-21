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

				void Camera::SetRoll(float p_Roll) {
								m_CamData.m_Roll = p_Roll;
				}

				void Camera::SetYaw(float p_Yaw) {
								m_CamData.m_Yaw = p_Yaw;
				}

				void Camera::SetPitch(float p_Pitch) {
								m_CamData.m_Pitch = p_Pitch;
				}

				void Camera::Update(int) {

				}

}

namespace Core {

				CameraManager::CameraManager() {

								EventDispatcher::GetInstance().RegisterEvent(
												new Event<int>(GL_CORE_EVENT_KEYPRESS,
																[&](int key) {
																				GetCurrentCamera()->Update(key);
																}));
				}

				void CameraManager::AddCamera(Camera* p_cam) {
								m_CameraList[p_cam->GetName()] = std::move(p_cam);
								m_CurrentCamera = p_cam->GetName();
				}

				void CameraManager::Update(double) {

				}

				Camera* CameraManager::GetCurrentCamera() {
								return m_CameraList[m_CurrentCamera];
				}

}
