#pragma once
#include <epch.h>
#include <Input/Input.h>


namespace Core {

				// Bridge between user controls and Camera's control result

				class Camera : public virtual IBaseObject {
				protected:
								glm::vec3 m_Dimensions{};
								float m_AspectRatio{};
				protected:
								bool m_Is3D{ false }, m_IsOrthagonal{ true }, m_DefaultSet{ false };
				protected:
								glm::mat4 m_LookAt{};
								glm::mat4 m_CamWindowToNDC{};
								glm::mat4 m_ProjectionMtx{};
				protected:
								struct CamData {
												glm::vec3 Up{}, Right{}, Direction{}, Target{}, Front{}, Position{};
												float m_Roll, m_Yaw, m_Pitch, m_Zoom, m_Fov{ DEFAULT_PERSPECTIVE_FOV };
								}m_CamData{}, m_DefaultCamData{};

								struct MovementSpecs {
												float m_RollSpeed, m_YawSpeed, m_PitchSpeed, m_MoveSpeed, m_ZoomSpeed;
								}m_Movement{};

								Core::KeyBinding m_KeyBindings;
								virtual void SetUp() {}
								virtual void KeyMapInstructions(Base_KeyMap, float);
								void LimitZoom();
				public:
								virtual void Update(double);
								virtual void ApplyMovement(ENUM_Key_Actions, float value);

				private:
								void CalculateLookAt();
								void CalculateOrthographicView();
								void CalculatePerspectiveView();
				public:
								Camera() {};
								Camera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height, glm::vec3 p_Target = { 0.f, 0.f, 0.f });
								Camera(const Camera&) = delete;
								Camera& operator=(const Camera&) = delete;
								inline glm::mat4 GetViewMatrix() { return m_CamWindowToNDC * m_LookAt; }
								inline glm::mat4 GetProjection() { return m_ProjectionMtx; }
								inline glm::mat4 GetProjectionViewMatrix() {
												return m_ProjectionMtx * GetViewMatrix();
								}
								inline bool IsOrthographic() { return m_IsOrthagonal; }
				public:
								void SetTarget(glm::vec3);
								void SetCameraWindow(float p_Width, float p_Height);
								void SetMovement(ENUM_Key_Actions, float value);
								void SetKeyBind(int Key, Base_KeyMap instructions);
								void Toggle3D(bool = false);
								void ToggleView(bool = false);
				};



				class CameraManager : public ISingleton<CameraManager> {

								std::map<std::string, Camera*> m_CameraList;
								std::string m_CurrentCamera;
				public:
								CameraManager();
								CameraManager(const CameraManager&) = delete;
								CameraManager& operator=(const CameraManager&) = delete;
								~CameraManager();
								static void AddCamera(Camera*);
								static void Update(double p_deltatime);
								static Camera* GetCurrentCamera();


				};

				float ZoomLerp(float start, float end, float t);

}
