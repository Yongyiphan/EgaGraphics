#include <epch.h>
#include "ECS.h"



namespace ECS {

				void Component::GenerateID(const std::string& p_name) {
								static ComponentID LatestID;
								static std::map<std::string, ComponentID> GeneratedList;
								m_Name = p_name;
								auto Generated = GeneratedList.find(p_name);
								if (Generated != GeneratedList.end()) {
												ID = Generated->second;
								}
								else {
												ID = ++LatestID;
												// Store
												GeneratedList[p_name] = ID;
								}
				}

				void Component::SetName(const std::string& p_Name) {
								m_Name = p_Name;
				}

				std::string Component::GetName() {
								return m_Name;
				}
}

namespace ECS {


				TransformComponent::TransformComponent()
								: m_Position(), m_Rotation({ 0.f, 0.f, 1.f }), m_Scale(),
								m_RotDegree(0), Component() {
								GenerateID("Transform");
				}


				void TransformComponent::SetPosition(glm::vec3 p_Position) {
								m_Position = p_Position;
				}

				void TransformComponent::SetRotationAxis(glm::vec3 p_Rotation) {
								m_Rotation = p_Rotation;
				}

				void TransformComponent::SetRotationDegree(float p_degree) {
								m_RotDegree = p_degree;
				}

				void TransformComponent::SetScale(glm::vec3 p_Scale) {
								m_Scale = p_Scale;
				}

				SpriteComponent::SpriteComponent() {
								GenerateID("Sprite");
				}

				TextComponent::TextComponent() { GenerateID("Text"); }
				MeshComponent::MeshComponent() { GenerateID("Mesh"); }
				MeshComponent::MeshComponent(const std::string& p_MeshName) {
								GenerateID("Mesh");
								SetMeshName(p_MeshName);
				}
}
