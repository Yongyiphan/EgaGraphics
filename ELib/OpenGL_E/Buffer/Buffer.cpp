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
								if (glIsBuffer(eboid) == GL_TRUE) {
												GLCall(glDeleteBuffers(1, &eboid));
												eboid = 0;
								}
				}

				void BufferSystem::Bind(GL_ID p_ID) {
								glBindVertexArray(p_ID);
				}

				void BufferSystem::UnBind() {
								glBindVertexArray(0);
				}


				GLBuffer::BufferID BufferSystem::CreateGLBuffer(BufferData BD) {
								GLBuffer::BufferID NID;
								BD.Resize();
								bool success = false;
								success = GLCall(glCreateBuffers(1, &NID.vboid));
								success = GLCall(glCreateVertexArrays(1, &NID.vaoid));
								if (!success || BD.GetTotalSize() == 0 || NID.vboid == 0) {
												NID.Completed = false;
												E_LOG_WARN("Buffer is empty");
												DeleteGLBuffer(NID);
												return NID;
								}
								glNamedBufferStorage(NID.vboid, BD.GetTotalSize(), nullptr, GL_DYNAMIC_STORAGE_BIT);

								if (auto idx = BD.GetIndexBuffer()) {
												success = BufferManager.HandleIndexBuffer(NID, idx);
								}
								for (auto ele : BD.GetLayoutData()) {
												if (ele->IsMatrixTyped()) {
																success = BufferManager.HandleMatrixVAElement(NID, ele);
																continue;
												}
												glNamedBufferSubData(NID.vboid, ele->GetOffset(), ele->GetTotalDataSize(), ele->GetRawData());
												glEnableVertexArrayAttrib(NID.vaoid, ele->GetDataPos());
												glVertexArrayVertexBuffer(NID.vaoid, ele->GetDataPos(), NID.vboid, ele->GetOffset(), ele->GetDataSize());
												glVertexArrayAttribFormat(NID.vaoid, ele->GetDataPos(), ele->GetSubElementCount(), ele->GetGL_Type(), GL_FALSE, 0);
												glVertexArrayAttribBinding(NID.vaoid, ele->GetDataPos(), ele->GetDataPos());
												if (ele->IsInstanced()) {
																glVertexArrayBindingDivisor(NID.vaoid, ele->GetDataPos(), 1);
												}
												success = GL_CheckError;
												if (!success) {
																goto Combust;
												}
								}

				Combust:
								if (!success) {
												NID.Completed = false;
												DeleteGLBuffer(NID);
								}
								glBindBuffer(GL_ARRAY_BUFFER, 0);
								glBindVertexArray(0);

								return NID;
				}

				void BufferSystem::DeleteGLBuffer(GLBuffer::BufferID IDs) {
								GLCall(glDeleteVertexArrays(1, &IDs.vaoid));
								GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
								GLCall(glDeleteBuffers(1, &IDs.vboid));
								GLCall(glDeleteBuffers(1, &IDs.pboid));
								GLCall(glDeleteBuffers(1, &IDs.eboid));
				}

				bool BufferSystem::HandleMatrixVAElement(GLBuffer::BufferID& NID, const std::shared_ptr<ILayoutElement>& ele) {
								bool success = true;
								for (GLint _i{ 0 }, i{ ele->GetDataPos() }; success && _i < ele->GetDimension(); i++, _i++) {
												glEnableVertexArrayAttrib(NID.vaoid, i);
												glVertexAttribPointer(
																i, ele->GetDimension(),
																ele->GetGL_Type(), GL_FALSE, ele->GetDataSize(),
																(void*)(ele->GetOffset() + (_i * ele->GetSubSubDataSize())));
												if (ele->IsInstanced()) {
																glVertexArrayBindingDivisor(NID.vaoid, i, 1);
												}
												success = GL_CheckError;
								}
								glNamedBufferSubData(NID.vboid, ele->GetOffset(), ele->GetTotalDataSize(), ele->GetRawData());
								return GL_CheckError;
				}

				bool BufferSystem::HandleIndexBuffer(GLBuffer::BufferID& NID, const std::shared_ptr<BufferLayoutElement<index_type>>& idx) {
								glCreateBuffers(1, &NID.eboid);
								glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NID.eboid);
								//glNamedBufferStorage(NID.eboid, idx->GetTotalDataSize(), idx->GetRawData(), GL_DYNAMIC_STORAGE_BIT);
								glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx->GetTotalDataSize(), idx->GetRawData(), GL_STATIC_DRAW);
								glVertexArrayElementBuffer(NID.vaoid, NID.eboid);
								return GL_CheckError;
				}
}
