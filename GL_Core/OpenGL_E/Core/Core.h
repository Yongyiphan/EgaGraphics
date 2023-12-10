#pragma once
#include "Defines.h"
#include "GLFW_Window.h"
#include "Input.h"
#include "Shader/Shader.h"



namespace Core {



				struct GL_Core {
								std::shared_ptr<GLWindow> AppWindow;
								std::shared_ptr<Input> AppInput;
								std::shared_ptr<GL_Graphics::ShaderManager> GLShader;

								GL_Core();
								~GL_Core();
								void Init(int width, int height);
								bool Run();
								void Next();
								void SetupShaders();
				};

				void GLClearError();
				std::pair<bool, std::string> GLCheckError(const char* FILE, int LINE);

}

// Macro definition to wrap gl commands within a error check
#ifdef _DEBUG
#define GLCall( x ) [&](){\
			 Core::GLClearError(); \
			 x; \
			 std::pair<bool, std::string> status = Core::GLCheckError(__FILE__, __LINE__);\
			if(!status.first) {\
										ASSERT_MSG(status.second);\
			}\
			return status.first;\
			}()

#define GLCallV( x ) [&]() { \
     Core::GLClearError(); \
     auto retVal = x; \
					std::pair<bool, std::string> status = Core::GLCheckError(__FILE__, __LINE__);\
					if(!status.first) {\
								ASSERT_MSG(status.second);\
					}\
     return retVal; \
   }()
#else
#define GLCall( x ) [&](){\
			x; \
			return true; \
			}()
#define GLCallV( x ) [&]() { \
     Graphics::GLClearError(); \
     auto retVal = x; \
		 std::pair<bool, std::string> status = Graphics::GLCheckError(__FILE__, __LINE__);\
     return retVal; \
   }()
#endif

