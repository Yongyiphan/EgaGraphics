#pragma once
#include <epch.h>
#include <filesystem>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace GL_Graphics {

				using ShaderID = unsigned int;


				enum class ShaderType {
								//.vert - a vertex shader
								//.frag - a fragment shader
								//.geom - a geometry shader
								//.tesc - a tessellation control shader
								//.tese - a tessellation evaluation shader
								//.comp - a compute shader
								VERT_SHADER,
								FRAG_SHADER,
								GEOM_SHADER,
								CONT_SHADER,
								EVAL_SHADER,
								COMP_SHADER
				};

				struct ShaderInfo {
								GLenum m_gltype{};
								ShaderType m_ShaderType{};
								std::string ext{};
				};

				static std::vector<ShaderInfo> ShaderConf = {
				{GL_VERTEX_SHADER, ShaderType::VERT_SHADER, "vert"},
				{GL_FRAGMENT_SHADER, ShaderType::FRAG_SHADER, "frag"},
				{GL_GEOMETRY_SHADER, ShaderType::GEOM_SHADER, "geom"},
				{GL_TESS_CONTROL_SHADER, ShaderType::CONT_SHADER, "tesc"},
				{GL_TESS_EVALUATION_SHADER, ShaderType::EVAL_SHADER, "tese"},
				{GL_COMPUTE_SHADER, ShaderType::COMP_SHADER, "comp"}
				};

				struct ShaderFile {
								std::filesystem::path m_filepath{};
								ShaderInfo m_ShaderType{};
								bool Corrupted{ false };
								ShaderFile() :m_filepath(), m_ShaderType() {}
								ShaderFile(const std::string& p_filepath, ShaderType p_shadertype);
								void Validate();
				};

				class ShaderGroup {
				public:
								ShaderGroup() {}
								ShaderGroup(const std::string& p_GroupName, std::vector<ShaderType> = { ShaderType::VERT_SHADER, ShaderType::FRAG_SHADER });
								bool IsCorrupted{};
								bool Created{};

								inline std::string GetName() { return m_name; }
								inline std::vector<ShaderFile> GetShaderGroup() { return ShaderGrp; }
								inline void SetShaderID(ShaderID p_ID) { m_ID = p_ID; }
								inline ShaderID GetShaderID() { return m_ID; }
				private:
								ShaderID m_ID{ 0 };
								std::string m_name{};
								std::vector<ShaderFile> ShaderGrp{};
								std::vector<bool> GroupStatus;

				};


				class ShaderManager : public ISingleton<ShaderManager> {
				public:
								ShaderManager() {}
								~ShaderManager() {}

								void AddShaderGroup(ShaderGroup);
								void RemoveShaderGroup(const std::string& ShaderGrp);
								void Use(const std::string& grp_name);
								void UnUse();
								ShaderID GetShader(const std::string& grp_name);


								void SetUniformMat3(const std::string&, glm::mat3);
								void SetUniformMat4(const std::string&, glm::mat4);
								void SetUniform1i(const std::string&, int value);
								void SetUniform1v(const std::string&, int count, int data[]);
								void SetUniformVec2(const std::string&, glm::vec2);
								void SetUniformVec3(const std::string&, glm::vec3);

				private:
								bool Shader_Create(ShaderGroup&);
								bool Shader_Compile(ShaderID, ShaderInfo, const std::string& source);
								bool Shader_Link(ShaderID);
								bool Shader_Validate(ShaderID);
								void HandleError(ShaderID, std::string msg, bool checkShader = false);
								int GetUniformVar(const std::string&);
								std::map<std::string, ShaderGroup> Shader_Cache;
								ShaderID CurrentShaderID{ 0 };
								std::string currShadergrp{ "" };
				};


}
