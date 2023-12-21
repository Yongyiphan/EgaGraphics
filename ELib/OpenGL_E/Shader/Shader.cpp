#include <epch.h>
#include "Shader.h"
#include <GL/glew.h>
#include <cstdlib>

namespace GL_Graphics {


				ShaderFile::ShaderFile(const std::string& p_filepath, ShaderType p_shadertype) {
								m_filepath = p_filepath;
								m_ShaderType = ShaderConf[static_cast<int>(p_shadertype)];
								Validate();
				}

				void ShaderFile::Validate() {
								// Check if file exists
								if (std::filesystem::exists(m_filepath)) {
												return;
								}
								else {
												Corrupted = true;
												E_LOG("ERROR", m_filepath << " not found");
								}
				}

				ShaderGroup::ShaderGroup(const std::string& p_GroupName, std::vector<ShaderType> p_ShaderTypes) {

								if (std::filesystem::exists(shader_dir)) {
												m_name = p_GroupName;
												for (auto st : p_ShaderTypes) {
																ShaderInfo si = ShaderConf[static_cast<int>(st)];
																auto filepath = shader_dir / (p_GroupName + "." + si.ext);
																ShaderFile new_File(filepath.string(), st);
																if (new_File.Corrupted) {
																				E_LOG("ERROR: ", "File does not exist");
																				continue;
																}
																ShaderGrp.emplace_back(new_File);
												}
												Created = true;
								}

				}


				void ShaderManager::AddShaderGroup(ShaderGroup p_sgroup) {
								if (Shader_Create(p_sgroup)) {
												if (!Shader_Link(p_sgroup.GetShaderID())) {
																p_sgroup.IsCorrupted = true;
																return;
												}
												if (!Shader_Validate(p_sgroup.GetShaderID())) {
																p_sgroup.IsCorrupted = true;
																return;
												}
								}
								else {
												p_sgroup.IsCorrupted = true;
								}
								if (p_sgroup.IsCorrupted) { return; }
								else {
												Shader_Cache[p_sgroup.GetName()] = p_sgroup;
								}


				}

				void ShaderManager::RemoveShaderGroup(const std::string& ShaderGrp) {
								Shader_Cache.erase(ShaderGrp);
				}

				bool ShaderManager::Shader_Create(ShaderGroup& p_sgroup) {
								bool success{ true };
								p_sgroup.SetShaderID(glCreateProgram());
								currShadergrp = p_sgroup.GetName();
								for (auto sfile : p_sgroup.GetShaderGroup()) {
												std::string sourcefile;
												std::ifstream inFile{ sfile.m_filepath.string(), std::ifstream::in };
												if (inFile.fail()) {
																E_LOG("ERROR", "Unable to read file");
																return success = false;;
												}
												std::stringstream buffer;
												buffer << inFile.rdbuf();
												inFile.close();
												sourcefile = buffer.str();
												if (!Shader_Compile(p_sgroup.GetShaderID(), sfile.m_ShaderType, sourcefile)) {
																return success;
												}
								}
								E_LOG("INFO", currShadergrp + " shader group created");

								return success;
				}
				bool ShaderManager::Shader_Compile(ShaderID p_pgrm, ShaderInfo p_info, const std::string& p_source) {
								ShaderID nid = glCreateShader(p_info.m_gltype);
								const char* src = p_source.c_str();
								glShaderSource(nid, 1, &src, nullptr);
								glCompileShader(nid);

								int result;
								glGetShaderiv(nid, GL_COMPILE_STATUS, &result);
								if (GL_FALSE == result) {
												HandleError(nid, currShadergrp + p_info.ext + "failed to compile\n", true);
												return false;
								}
								else {
												glAttachShader(p_pgrm, nid);
								}
								return true;

				}
				bool ShaderManager::Shader_Link(ShaderID p_id) {
								glLinkProgram(p_id);
								int result;
								glGetProgramiv(p_id, GL_LINK_STATUS, &result);
								if (GL_FALSE == result) {
												HandleError(p_id, "Failed to link shader\n");
												return false;
								}
								return true;

				}

				bool ShaderManager::Shader_Validate(ShaderID p_id) {
								glValidateProgram(p_id);
								int result;
								glGetProgramiv(p_id, GL_VALIDATE_STATUS, &result);
								if (GL_FALSE == result) {
												HandleError(p_id, "Failed to validate shader\n");
												return false;
								}
								return true;
				}

				ShaderID ShaderManager::GetShader(const std::string& grp_name) {
								auto found = Shader_Cache.find(grp_name);
								if (found != Shader_Cache.end()) {
												return found->second.GetShaderID();
								}
								else {
												E_LOG("Warn", "Invalid shader group name");
								}
								return 0;
				}

				void ShaderManager::HandleError(ShaderID pgrm, std::string err_msg, bool checkShader) {
								GLint log_len;
								char* error_log = nullptr;
								if (checkShader) {
												GLCall(glGetShaderiv(pgrm, GL_INFO_LOG_LENGTH, &log_len));
												error_log = new char[log_len];
												GLCall(glGetShaderInfoLog(pgrm, log_len, &log_len, error_log));
												err_msg += error_log;
												delete[] error_log;
												error_log = nullptr;
								}
								else {
												GLCall(glGetProgramiv(pgrm, GL_INFO_LOG_LENGTH, &log_len));
												error_log = new char[log_len];
												GLCall(glGetProgramInfoLog(pgrm, log_len, &log_len, error_log));
												err_msg += error_log;
												delete[] error_log;
												error_log = nullptr;
								}
								ASSERT_MSG(err_msg);
				}


				void ShaderManager::Use(const std::string& grp_name) {
								ShaderID p_id = GetShader(grp_name);
								if (p_id) {
												if (p_id != CurrentShaderID) {
																bool info = false;
																if (info) {
																				std::stringstream ss;
																				ss << "Shader changed from: ";
																				ss << CurrentShaderID;
																				ss << " to: " << p_id;
																				E_LOG("INFO", ss.str());
																}
																CurrentShaderID = p_id;
												}
												GLCall(glUseProgram(CurrentShaderID));
								}
				}

				void ShaderManager::UnUse() {
								CurrentShaderID = 0;
								glUseProgram(CurrentShaderID);
				}

				int ShaderManager::GetUniformVar(const std::string& p_name) {
								int location = GLCallV(glGetUniformLocation(CurrentShaderID, p_name.c_str()));
								if (location == -1) {
												E_LOG("WARN", "Uniform: " + p_name + " does not exist");
								}
								return location;
				}

				void ShaderManager::SetUniformMat3(const std::string& p_name, glm::mat3 mat3) {
								GLCall(glUniformMatrix3fv(GetUniformVar(p_name), 1, GL_FALSE, &mat3[0][0]));
				}
				void ShaderManager::SetUniformMat4(const std::string& p_name, glm::mat4 mat4) {
								GLCall(glUniformMatrix4fv(GetUniformVar(p_name), 1, GL_FALSE, &mat4[0][0]));
				}

				void ShaderManager::SetUniform1i(const std::string& p_name, int value) {
								GLCall(glUniform1i(GetUniformVar(p_name), value));
				}

				void ShaderManager::SetUniform1v(const std::string& p_name, int count, int data[]) {
								GLCall(glUniform1iv(GetUniformVar(p_name), count, data));
				}

				void ShaderManager::SetUniformVec2(const std::string& p_name, glm::vec2 vec) {
								GLCall(glUniform2f(GetUniformVar(p_name), vec.x, vec.y));
				}
				void ShaderManager::SetUniformVec3(const std::string& p_name, glm::vec3 vec) {
								GLCall(glUniform3f(GetUniformVar(p_name), vec.x, vec.y, vec.z));
				}

}
