#pragma once
#include <epch.h>
#include <Input/Input.h>


namespace Core {

				// Bridge between user controls and Camera's control result

				class Camera : public virtual IBaseObject {
								glm::vec3 m_Dimensions{};
								float m_AspectRatio{};
				private:
								bool m_Is3D{ false }, m_IsOrthagonal{ false }, m_DefaultSet{ false };
								glm::mat4 m_LookAt{};
								glm::mat4 m_CamWindowToNDC{};
								glm::mat4 m_ProjectionMtx{};
								struct CamData {
												glm::vec3 Up{}, Right{}, Direction{}, Target{}, Front{}, Position{};
												float m_Roll, m_Yaw, m_Pitch, m_Zoom, m_Fov{ 45.f };
								}m_CamData{}, m_DefaultCamData;
								struct MovementSpecs {
												float m_Roll, m_Yaw, m_Pitch, m_MoveSpeed{ 10.f }, m_ZoomSpeed;
								}m_Movement{};

								Core::KeyBinding m_KeyBindings;
				private:
								void CalculateLookAt();
								void OrthographicView();
								void PerspectiveView();
				public:
								Camera() {};
								Camera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height);
								Camera(const Camera&) = delete;
								Camera& operator=(const Camera&) = delete;
								inline glm::mat4 GetViewMatrix() { return m_CamWindowToNDC * m_LookAt; }
								inline glm::mat4 GetProjection() { return m_ProjectionMtx; }
								inline glm::mat4 GetProjectionViewMatrix() {
												return m_ProjectionMtx * GetViewMatrix();
								}
				public:
								void SetTarget(glm::vec3);
								void SetMovement(ENUM_Key_Actions, float value);
								void SetKeyBind(int Key, Base_KeyMap instructions);
								void Toggle3D(bool = false);
								void ToggleView(bool = false);
				public:
								void SetCameraWindow(float p_Width, float p_Height);
								virtual void Update(const std::shared_ptr<Core::Input>&, double);
								virtual void ApplyMovement(ENUM_Key_Actions, float value);
				};



				class CameraManager {

								std::map<std::string, Camera*> m_CameraList;
								std::string m_CurrentCamera;
				public:
								CameraManager();
								CameraManager(const CameraManager&) = delete;
								CameraManager& operator=(const CameraManager&) = delete;
								void AddCamera(Camera*);
								void Update(const std::shared_ptr<Core::Input>& p_input, double p_deltatime);
								Camera* GetCurrentCamera();


				};

}
