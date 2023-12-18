#include <epch.h>
#include "Buffer.h"
#include <glm/glm.hpp>


namespace GL_Graphics {



				void BufferData::Resize() {
								m_TotalSize = 0;
								size_t t_datapos{ 0 };
								for (auto ele : m_Data) {
												ele->GetDataPos() = static_cast<GLsizei>(t_datapos);
												ele->GetOffset() = m_TotalSize;
												m_TotalSize += ele->GetTotalDataSize();
												if (ele->GetDataSize() == sizeof(glm::mat3)) {
																t_datapos += 3;
												}
												else if (ele->GetDataSize() == sizeof(glm::mat4)) {
																t_datapos += 4;
												}
												else {
																++t_datapos;
												}
								}
				}


				void BufferData::Clear() {
								for (auto m_ele : m_Data) {
												m_ele->Clear();
								}
								m_Data.clear();
								m_IdxBuffer->Clear();

				}

				void GLBuffer::BufferID::Reset() {
								if (glIsVertexArray(vaoid) == GL_TRUE) {
												glDeleteVertexArrays(1, &vaoid);
												vaoid = 0;
								}
								if (glIsBuffer(vboid) == GL_TRUE) {
												GLCall(glDeleteBuffers(1, &vboid));
												vboid = 0;
								}
								if (glIsBuffer(pboid) == GL_TRUE) {
												GLCall(glDeleteBuffers(1, &pboid));
												pboid = 0;
								}
				}

				void BufferSystem::Bind(GL_ID p_ID) {
								GLCall(glBindVertexArray(p_ID));
				}

				void BufferSystem::UnBind() {
								GLCall(glBindVertexArray(0));
				}


				GLBuffer::BufferID BufferSystem::CreateGLBuffer(BufferData BD) {
								GLBuffer::BufferID NID;
								BD.Resize();
								bool success = false;
								success = GLCall(glCreateBuffers(1, &NID.vboid));
								success = GLCall(glCreateVertexArrays(1, &NID.vaoid));
								if (!success || BD.GetTotalSize() == 0 || NID.vboid == 0) {
												NID.Completed = false;
												DeleteGLBuffer(NID);
												return NID;
								}
								success = GLCall(glNamedBufferStorage(NID.vboid, BD.GetTotalSize(), nullptr, GL_DYNAMIC_STORAGE_BIT));
								for (auto ele : BD.GetLayoutData()) {
												if (ele->IsMatrixTyped()) {
																success = BufferManager.HandleMatrixVAElement(NID, ele);
																continue;
												}
												success = GLCall(glNamedBufferSubData(NID.vboid, ele->GetOffset(), ele->GetTotalDataSize(), ele->GetRawData()));
												success = GLCall(glEnableVertexArrayAttrib(NID.vaoid, ele->GetDataPos()));
												success = GLCall(glVertexArrayVertexBuffer(NID.vaoid, ele->GetDataPos(), NID.vboid, ele->GetOffset(), ele->GetDataSize()));
												success = GLCall(glVertexArrayAttribFormat(NID.vaoid, ele->GetDataPos(), ele->GetSubElementCount(), ele->GetGL_Type(), GL_FALSE, 0));
												success = GLCall(glVertexArrayAttribBinding(NID.vaoid, ele->GetDataPos(), ele->GetDataPos()));
												if (ele->IsInstanced()) {
																success = GLCall(glVertexArrayBindingDivisor(NID.vaoid, ele->GetDataPos(), 1));
												}
												if (!success) {
																goto Combust;
												}
								}

								if (auto idx = BD.GetIndexBuffer()) {
												success = BufferManager.HandleIndexBuffer(NID, idx);
								}
				Combust:
								if (!success) {
												NID.Completed = false;
												DeleteGLBuffer(NID);
								}


								return NID;
				}

				void BufferSystem::DeleteGLBuffer(GLBuffer::BufferID IDs) {
								GLCall(glDeleteVertexArrays(1, &IDs.vaoid));
								GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
								GLCall(glDeleteBuffers(1, &IDs.vboid));
								GLCall(glDeleteBuffers(1, &IDs.pboid));
								GLCall(glDeleteBuffers(1, &IDs.eboid));
				}

				bool BufferSystem::HandleMatrixVAElement(GLBuffer::BufferID NID, const std::shared_ptr<ILayoutElement>& ele) {
								bool success = true;
								for (GLint _i{ 0 }, i{ ele->GetDataPos() }; success && _i < ele->GetDimension(); i++, _i++) {
												success = GLCall(glEnableVertexArrayAttrib(NID.vaoid, i));
												success = GLCall(
																glVertexAttribPointer(
																				i, ele->GetDimension(),
																				ele->GetGL_Type(), GL_FALSE, ele->GetDataSize(),
																				(void*)(ele->GetOffset() + (_i * ele->GetSubSubDataSize()))));
												if (ele->IsInstanced()) {
																success = GLCall(glVertexArrayBindingDivisor(NID.vaoid, i, 1));
												}
								}
								success = GLCall(glNamedBufferSubData(NID.vboid, ele->GetOffset(), ele->GetTotalDataSize(), ele->GetRawData()));
								return success;
				}

				bool BufferSystem::HandleIndexBuffer(GLBuffer::BufferID NID, const std::shared_ptr<BufferLayoutElement<index_type>>& idx) {
								GL_ID ebo{};
								bool success = true;
								success = GLCall(glCreateBuffers(1, &ebo));
								success = GLCall(glNamedBufferStorage(ebo, idx->GetTotalDataSize(), idx->GetRawData(), GL_DYNAMIC_STORAGE_BIT));
								success = GLCall(glVertexArrayElementBuffer(NID.vaoid, ebo));
								NID.eboid = ebo;
								return success;
				}
}
