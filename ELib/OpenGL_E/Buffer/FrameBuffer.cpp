#include <epch.h>
#include "FrameBuffer.h"

namespace GL_Graphics {
				void FrameBuffer::Bind(FrameBufferID id) {
								GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
				}

				void FrameBuffer::UnBind() {
								GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
				}

				Attachment::Attachment(GLint p_InternalFormat, GLenum p_Format, GLenum p_Attachment) {
								m_internalformat = p_InternalFormat;
								m_format = p_Format;
								m_attachment = p_Attachment;
								if (m_attachment == GL_DEPTH_STENCIL_ATTACHMENT) {
												IsDepthStencil = true;
								}
				}

				FrameBufferSettings::FrameBufferSettings(const std::string& p_Name, float width, float height) : IsCompleted(false) {
								SetName(p_Name);
								m_Width = width;
								m_Height = height;

				}

				FrameBuffer::FrameBuffer(FrameBufferSettings p_settings) {
								SetName(p_settings.GetName());
								m_fbsettings = p_settings;
								m_ColorAttachment = m_fbsettings.m_Attachment;
								Create(p_settings.m_Width, p_settings.m_Height);
				}


				void FrameBuffer::Create(float p_width, float p_height) {
								if (p_width == 0 || p_height == 0) {
												m_fbsettings.IsCompleted = false;
												return;
								}
								GLCall(glCreateFramebuffers(1, &m_FrameBufferID));
								FrameBuffer::Bind(m_FrameBufferID);
								GLint i{ 0 };
								for (auto& color_attachment : m_ColorAttachment) {
												if (!color_attachment.IsDepthStencil) {
																color_attachment.m_attachment = GL_COLOR_ATTACHMENT0 + i;
																i++;
												}
												CompileAttachment(color_attachment);
								}

								FrameBuffer::UnBind();
				}


				void FrameBuffer::Destroy() {
								GLCall(glDeleteFramebuffers(1, &m_FrameBufferID));
								for (auto& _attachment : m_ColorAttachment) {
												GLCall(glDeleteTextures(1, &_attachment.m_TextureID));
								}
								m_ColorAttachment.clear();
				}

				void FrameBuffer::AddAttachment(Attachment _attachment) {
								m_ColorAttachment.push_back(_attachment);
								CompileAttachment(_attachment);
				}

				void FrameBuffer::CompileAttachment(Attachment& _attachment) {
								GLsizei gwidth = (GLsizei)m_fbsettings.m_Width;
								GLsizei gheight = (GLsizei)m_fbsettings.m_Height;
								TextureID TexID{ 0 };
								GLenum _target = GL_TEXTURE_2D;
								GLCall(glCreateTextures(_target, 1, &TexID));
								GLCall(glBindTexture(_target, TexID));
								if (_attachment.IsDepthStencil) {
												GLCall(glTextureStorage2D(TexID, 1, _attachment.m_internalformat, gwidth, gheight));
												m_DepthTexture = TexID;
								}
								else {
												GLenum DataType = GL_UNSIGNED_BYTE;
												GLCall(glTexImage2D(_target, 0, _attachment.m_internalformat, gwidth, gheight, 0, _attachment.m_format, DataType, nullptr));
												GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
												GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
												GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
												GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

												_attachment.m_TextureID = TexID;
								}
								GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, _attachment.m_attachment, _target, TexID, 0));

								if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
												auto Err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
												ELOG_FATAL(std::format("Something wrong: Frame Buffer ({})", Err).c_str());
												Destroy();
												m_fbsettings.IsCompleted = false;
												return;
								}
								m_fbsettings.IsCompleted = true;
				}



				void FrameBuffer::Resize(float p_width, float p_height) {
								// If Same Framebuffer size then; irrelevant to recreate;
								if (p_width == m_fbsettings.m_Width && p_height == m_fbsettings.m_Height) {
												return;
								}
								Destroy();
								Create(p_width, p_height);
				}
				TextureID FrameBuffer::GetColorAttachment(size_t color_attachment_index) {
								if (color_attachment_index >= m_ColorAttachment.size()) {
												return 0;
								}
								else {
												return m_ColorAttachment.at(color_attachment_index).m_TextureID;
								}
				}

				TextureID FrameBuffer::GetDepthTexture() {
								return m_DepthTexture;
				}

				FrameBufferID FrameBuffer::GetFrameBufferID() {
								return m_FrameBufferID;
				}
}
