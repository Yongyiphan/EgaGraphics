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

				BufferData::~BufferData() {
								for (auto layout : m_Data) {
												layout->~IBufferLayout();
								}

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


}
