#include <epch.h>
#pragma once
#ifndef BUFFER_H
#define BUFFER_H


namespace GL_Graphics {

				using GL_ID = GLuint;
				using index_type = unsigned short;

				class ILayoutElement {
				protected:
								GLsizei m_DataPos{};
								GLsizei m_DataSize{ 0 };
								GLint m_SubElementCount{ 0 };
								size_t m_Offset{};
								GLenum m_GL_Type{ GL_FLOAT };
				protected:
								std::string m_Name;
								bool m_IsInstanced{ false };
				protected: // Mat3/4 related
								GLint m_Dimensions{ 2 };
								size_t m_SubSubDataSize{};
								bool m_IsMatrix_Type{ false };
				public:
								inline std::string GetName() { return m_Name; }
								inline GLsizei& GetDataPos() { return m_DataPos; }
								inline GLsizei& GetDataSize() { return m_DataSize; }
								inline size_t& GetOffset() { return m_Offset; }
								inline bool IsMatrixTyped() { return m_IsMatrix_Type; }
								inline GLenum GetGL_Type() { return m_GL_Type; }
								inline GLint GetSubElementCount() { return m_SubElementCount; }
								inline bool IsInstanced() { return m_IsInstanced; }
								inline GLint GetDimension() { return m_Dimensions; }
								inline size_t GetSubSubDataSize() { return m_SubSubDataSize; }

				public:
								// Related to typename T
								// Required Override
								virtual size_t GetElementCount() = 0;
								virtual size_t GetTotalDataSize() = 0;
								virtual void Clear() = 0;
								virtual ~ILayoutElement() {};
								virtual void* GetRawData() = 0;
				};

				template <typename T>
				class BufferLayoutElement : public ILayoutElement {
				private:
								std::vector<T> m_Data;
								void GetSpecs() {};
				public:
								BufferLayoutElement();
								BufferLayoutElement(const std::string& p_name, std::vector<T> rhs, bool p_IsInstanced = false, size_t reserve = 0);
								~BufferLayoutElement();

								inline virtual size_t GetElementCount() override {
												return m_Data.size();
								}

								inline virtual size_t GetTotalDataSize() override {
												return m_Data.size() * m_DataSize;
								}
								virtual void Clear() override;
				public:
								// Helpers for Buffer Creation
								inline void* GetRawData() override { return m_Data.data(); }

				};

				class BufferData {
								std::vector<std::shared_ptr<ILayoutElement>>m_Data;
								std::shared_ptr<BufferLayoutElement<index_type>> m_IdxBuffer;
								size_t m_TotalSize{ 0 };
								GLenum m_Primitive{ GL_LINE_STRIP };
				public:
								BufferData() {}
								~BufferData() {};


								void Resize();
								void Clear();
								inline GLenum GetPrimitive() const { return m_Primitive; }
								inline void SetPrimitive(GLenum p_primitive) { m_Primitive = p_primitive; }
								inline size_t GetTotalSize() { return m_TotalSize; }
								inline std::vector<std::shared_ptr<ILayoutElement>>& GetLayoutData() { return m_Data; }

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


								std::shared_ptr<BufferLayoutElement<index_type>> ConstructIndexBuffer(std::vector<index_type> p_data) {
												m_IdxBuffer = std::make_shared<BufferLayoutElement<index_type>>("idx", p_data);
												return m_IdxBuffer;
								}


								template <typename T>
								std::shared_ptr<BufferLayoutElement<T>> GetBufferElement(const std::string& p_name) {
												for (auto& element : m_Data) {
																if (std::shared_ptr<BufferLayoutElement<T>> converted = std::dynamic_pointer_cast<BufferLayoutElement<T>>(element)) {
																				if (converted->GetName() == p_name) {
																								return converted;
																				}
																}
												}
												return nullptr;
								}

								inline std::shared_ptr<BufferLayoutElement<index_type>> GetIndexBuffer() {
												return m_IdxBuffer;
								}
				};


				class GLBuffer {

				public:
								struct BufferID {
												GL_ID vaoid, vboid, pboid;
												GL_ID eboid;
												bool Completed{ false };
												void Reset();
								}ID;
								BufferData m_BufferData;
				};


				class BufferSystem {
								//Handles Matrix typed Vertex Array element
								bool HandleMatrixVAElement(GLBuffer::BufferID, const std::shared_ptr<ILayoutElement>&);
								bool HandleIndexBuffer(GLBuffer::BufferID, const std::shared_ptr<BufferLayoutElement<index_type>>&);
				public:
								static GLBuffer::BufferID CreateGLBuffer(BufferData);
								static void DeleteGLBuffer(GLBuffer::BufferID);
								static void Bind(GL_ID);
								static void UnBind();

				}static BufferManager;

}
#include "Buffer.inl"
#endif //BUFFER_H
