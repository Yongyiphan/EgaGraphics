#pragma once
#include <epch.h>
#include <Input/Input.h>


namespace Core {

				// Bridge between user controls and Camera's control result
				class CameraKeyBinds : Core::KeyBinding {
				public:
				};

				class Camera : public virtual IBaseObject {
								glm::vec3 m_Dimensions{};
								float m_AspectRatio{};
								glm::vec3 m_Position{};
				private:
								bool m_Is3D{ false }, m_IsOrthagonal{ false };
								glm::mat4 m_LookAt{};
								glm::mat4 m_CamWindowToNDC{};
								glm::mat4 m_ProjectionMtx{};
								struct CamData {
												glm::vec3 Up{}, Right{}, Direction{};
												float m_Roll, m_Yaw, m_Pitch;
								}m_CamData{};

								CameraKeyBinds m_KeyBindings;
				private:
								void CalculateLookAt();
				public:
								Camera() {};
								Camera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height);
								Camera(const Camera&) = delete;
								Camera& operator=(const Camera&) = delete;
								inline glm::mat4 GetViewMatrix() { return m_CamWindowToNDC * m_LookAt; }
								inline glm::mat4 GetProjection() { return m_ProjectionMtx; }
								inline glm::mat4 GetProjectionViewMatrix() { return m_ProjectionMtx * GetViewMatrix(); }
				public:
								void SetYaw(float);
								void SetRoll(float);
								void SetPitch(float);
				public:
								void SetCameraWindow(float p_Width, float p_Height);
								void Zoom(float);
								void Toggle3D(bool = false);
								void ToggleView(bool = false);
								virtual void Update(int key);
				};



				class CameraManager {

								std::map<std::string, Camera*> m_CameraList;
								std::string m_CurrentCamera;
				public:
								CameraManager();
								CameraManager(const CameraManager&) = delete;
								CameraManager& operator=(const CameraManager&) = delete;
								void AddCamera(Camera*);
								void Update(double p_deltatime);
								Camera* GetCurrentCamera();


				};

}
