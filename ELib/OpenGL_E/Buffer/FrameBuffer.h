#include <epch.h>

namespace GL_Graphics {
				using TextureID = unsigned int;
				using FrameBufferID = unsigned int;

				struct Attachment {
								GLint m_internalformat{};
								GLenum m_format{}, m_attachment{};
								TextureID m_TextureID{};
								bool IsDepthStencil{ false };
								Attachment() = default;
								Attachment(GLint p_InternalFormat, GLenum p_Format, GLenum p_Attachment = GL_COLOR_ATTACHMENT0);
				};

				struct FrameBufferSettings :public IBaseObject {
								float m_Width{}, m_Height{};
								bool IsDepthStencil{ false };
								bool IsCompleted{};
								std::vector<Attachment> m_Attachment;
								FrameBufferSettings() = default;
								FrameBufferSettings(const std::string& p_Name, float width = 0, float height = 0);
				};

				class FrameBuffer : public IBaseObject {
				private:
								FrameBufferSettings m_fbsettings;
				private:
								FrameBufferID m_FrameBufferID{};
								std::vector<Attachment> m_ColorAttachment;
								TextureID m_DepthTexture;
								void Create(float width, float height);
								void Destroy();
								void CompileAttachment(Attachment&);
				public:
								FrameBuffer() = default;
								FrameBuffer(FrameBufferSettings);
								void AddAttachment(Attachment);

								TextureID GetColorAttachment(size_t);
								TextureID GetDepthTexture();
								FrameBufferID GetFrameBufferID();
								void Resize(float width, float height);
								static void Bind(FrameBufferID);
								static void UnBind();


				};





}
