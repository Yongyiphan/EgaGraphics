#include <epch.h>
#pragma once

namespace ECS {

				using ComponentID = uint64_t;

				struct IComponent {
								virtual ~IComponent() {};
				};

				class Component :public IComponent {
				protected:
								std::string m_Name;
								ComponentID ID;
								void GenerateID(const std::string& p_name);
				public:
								virtual void SetName(const std::string& p_name);
								virtual std::string GetName();
								inline virtual ComponentID GetID() { return ID; }
								virtual ~Component() override {};

				};

				class TransformComponent : public virtual Component {

				private:
								glm::vec3 m_Position;
								glm::vec3 m_Rotation;
								glm::vec3 m_Scale;
								float m_RotDegree{};

				public:
								inline glm::vec3 GetPosition() { return m_Position; }
								inline glm::vec3 GetRotationAxis() { return m_Rotation; }
								inline float GetRotationDegree() { return m_RotDegree; }
								inline glm::vec3 GetScale() { return m_Scale; }

				public:
								TransformComponent();
								~TransformComponent() {};
								void SetPosition(glm::vec3);
								void SetRotationAxis(glm::vec3);
								void SetRotationDegree(float);
								void SetScale(glm::vec3);
				};

				class SpriteComponent : public virtual Component {
				public:
								SpriteComponent();
								~SpriteComponent() {}

				};

				class TextComponent : public virtual Component {
				public:
								TextComponent();
								~TextComponent() {}

				};

				class MeshComponent : public virtual Component {
								std::string m_MeshName;
				public:
								MeshComponent();
								MeshComponent(const std::string& meshname);
								~MeshComponent() {}

								inline std::string GetMeshName() { return m_MeshName; }
								inline void SetMeshName(const std::string& p_MeshName) { m_MeshName = p_MeshName; }
				};
}
