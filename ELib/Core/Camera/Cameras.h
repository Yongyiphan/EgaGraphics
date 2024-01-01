#pragma once
#include <epch.h>
#include "CameraController.h"


namespace Core {
				class SampleCamera : public Camera {
				public:
								SampleCamera();
								SampleCamera(const std::string& p_Name, glm::vec3 p_Position, float p_width, float p_height, glm::vec3 p_Target = { 0.f, 0.f, 0.f });
								~SampleCamera() = default;
								virtual void SetUp() override;


				};
}
