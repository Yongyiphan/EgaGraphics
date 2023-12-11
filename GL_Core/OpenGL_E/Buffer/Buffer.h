#include <epch.h>
#pragma once
#ifndef BUFFER_H
#define BUFFER_H


namespace GL_Graphics {

				using GL_ID = GLuint;
				using idx_type = unsigned short;

				struct IBufferLayout {
								virtual size_t GetElementCount() = 0;
								virtual size_t GetTotalDataSize() = 0;
								virtual GLsizei& GetDataSize() = 0;
								virtual GLsizei& GetDataPos() = 0;
								virtual size_t& GetOffset() = 0;
								virtual ~IBufferLayout() {};
				};

				template <typename T>
				class BufferLayoutElement : public IBufferLayout {
				private:
								GLsizei m_DataPos{};
								GLsizei m_DataSize{ 0 };
								GLint m_SubElementCount{ 0 };
								size_t m_Offset{};
				private:
								std::string m_Name;
								std::vector<T> m_Data{};
								bool m_IsInstanced{ false };
								GLint m_Dimensions{ 2 };
								GLenum GL_Type{ GL_FLOAT };
								void GetSpecs() {};
				public:
								BufferLayoutElement();
								BufferLayoutElement(const std::string& p_name, bool p_IsInstanced = false, size_t reserve = 0);
								BufferLayoutElement(const std::string& p_name, std::vector<T> rhs, bool p_IsInstanced = false, size_t reserve = 0);
								~BufferLayoutElement();

								inline virtual size_t GetElementCount() override {
												return m_Data.size();
								}

								inline virtual size_t GetTotalDataSize() override {
												return m_Data.size() * m_DataSize;
								}

								inline std::vector<T>& GetData() { return m_Data; }
								inline std::string GetName() { return m_Name; }
								inline GLsizei& GetDataPos() { return m_DataPos; }
								inline GLsizei& GetDataSize() { return m_DataSize; }
								inline size_t& GetOffset() { return m_Offset; }

				};

				class BufferData {
								std::vector<std::shared_ptr<IBufferLayout>>m_Data;
								std::shared_ptr<BufferLayoutElement<idx_type>> m_IdxBuffer;
								size_t m_TotalSize{ 0 };
				public:
								BufferData() {}

								void Resize();

								template <typename T, typename... Args>
								std::shared_ptr<BufferLayoutElement<T>> ConstructBufferElement(const std::string& p_name, Args&&... args) {
												std::shared_ptr<BufferLayoutElement<T>> existing_element = GetBufferElement<T>(p_name);
												if (existing_element) {
																return existing_element;
												}
												auto new_element = std::make_shared<BufferLayoutElement<T>>(p_name, std::forward<Args>(args)...);
												m_Data.push_back(new_element);
												Resize();
												return new_element;
								}

								std::shared_ptr<BufferLayoutElement<idx_type>> ConstructIndexBuffer(const std::string& p_name, std::vector<idx_type> p_data) {
												m_IdxBuffer = std::make_shared<BufferLayoutElement<idx_type>>(p_name, p_data);
												return m_IdxBuffer;
								}


								template <typename T>
								std::shared_ptr<BufferLayoutElement<T>> GetBufferElement(const std::string& p_name) {
												for (auto& element : m_Data) {
																if (auto converted = std::dynamic_pointer_cast<BufferLayoutElement<T>>(element)) {
																				if (converted->GetName() == p_name) {
																								return converted;
																				}
																}
												}
												return nullptr;
								}

								inline std::shared_ptr<BufferLayoutElement<idx_type>> GetIndexBuffer() {
												return m_IdxBuffer;
								}
				};


				class GLBuffer {

				public:
								struct BufferID {
												GL_ID vaoid, vboid, pboid;
												void Reset();
								}ID;
								BufferData m_BufferData;
				};


				class BufferSystem {
				public:

								static void Bind(GL_ID);
								static void UnBind();

				};

}
#include "Buffer/Buffer.inl"
#endif //BUFFER_H
