#pragma once
#include <string>
#include <sstream>
#include <csignal>

/////////////////////////////////////////////////////////
///                                                   ///
///                 EVENT CALLBACKS                   ///
///                                                   ///
/////////////////////////////////////////////////////////
#define GL_CORE_EVENT_WINDOW_RESIZE "Event_Window_Resize"
#define GL_CORE_EVENT_MOUSEBUTTON "Event_MouseButton"
#define GL_CORE_EVENT_MOUSESCROLL "Event_MouseScroll"
#define GL_CORE_EVENT_MOUSEPOSITION "Event_MousePosition"
#define GL_CORE_EVENT_KEYPRESS "Event_KeyPress"


/////////////////////////////////////////////////////////
///                                                   ///
///                     PATH																										///
///                                                   ///
/////////////////////////////////////////////////////////
#define EDITOR_PATH ""
#define GL_ASSETS_PATH "GL_Assets"
#define GL_AUDIOS_PATH "Audios"
#define GL_IMAGES_PATH "Images"
#define GL_SHADER_PATH "Shader"

#define E_LOG(Level, msg) \
    do { \
        std::stringstream logStream; \
        std::string file(__FILE__); \
        size_t lastSlash = file.find_last_of("/\\"); \
        if (lastSlash != std::string::npos) { \
            file = file.substr(lastSlash + 1); \
        } \
        logStream << Level <<  ": File: " << file << " @" << __LINE__ << " - " << msg; \
        std::cout << logStream.str() << "\n"; \
    } while (0)

#define E_LOG_INFO(msg) E_LOG("INFO", msg)
#define E_LOG_WARN(msg) E_LOG("WARN", msg)
#define E_LOG_ERROR(msg) E_LOG("ERROR", msg)
#define E_LOG_FATAL(msg) E_LOG("FATAL", msg)
#define E_LOG_DEBUG(msg) E_LOG("DEBUG", msg)

#define ASSERT_MSG(msg)\
do{\
				E_LOG("FATAL", msg);\
				std::raise(SIGABRT);\
} while (0)


////////////////////////////////////////////////////////////
///                                                      ///
///																				CONTROLS PLAN				   														///
///                                                      ///
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
///																				  CAMERA                          ///
////////////////////////////////////////////////////////////
#include "Window/GLFW_Window.h"
enum class Camera_Key_Actions {
				NONE = 0,
				ROLL,
				YAW,
				PITCH,
				ZOOM,
				VIEW,
				TOGGLE,
				MAX_CAM_FLAG = 8,
};

enum class Base_Key_Actions {
				NONE = 0,
				FORWARD,
				BACKWARD,
				LEFT,
				RIGHT,
				RESET,
				MAX_FLAG = 8,
};


////////////////////////////////////////////////////////////
///																				   INPUT                          ///
////////////////////////////////////////////////////////////
#define MOUSE_LEFT GLFW_MOUSE_BUTTON_1
#define MOUSE_RIGHT GLFW_MOUSE_BUTTON_2
#define MOUSE_MIDDLE GLFW_MOUSE_BUTTON_3
