#pragma once
#include <string>
#include <sstream>
#include <csignal>
#define _CRTDBG_MAP_ALLOC

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
#define DEFAULT_PERSPECTIVE_FOV 60.f
#define PERSPECTIVE_FOV_UPPER_LIMIT 100.f
#define PERSPECTIVE_FOV_LOWER_LIMIT 1.0f
#define ORTHOGRAPHIC_ZOOM_UPPER_LIMIT 20.f
#define ORTHOGRAPHIC_ZOOM_LOWER_LIMIT 0.1f

#include "Window/GLFW_Window.h"
#define UICast(x) static_cast<unsigned int>(x)
#define STCast(x) static_cast<size_t>(x)

enum class ENUM_Key_Actions : size_t {
				NONE,
				FORWARD,
				BACKWARD,
				LEFT,
				RIGHT,
				UP,
				DOWN,
				RESET,
				ROLL,
				YAW,
				PITCH,
				ZOOM,
				VIEW,
				TOGGLE,
				MAX_FLAG,
};

enum class KeyTriggerType {
				CLICK,
				HOLD,
				CLICK_HOLD,
};

#define KEY_TRIGGER_START(keybind)for(auto&instructions : keybind.GetTriggered()){
#define KEY_TRIGGER_END }

enum GPU_LIMIT : int {
				GL_MAX_TEXTURE_SLOT = 16,
};
enum BATCH_LIMIT : size_t {
				MAX_BATCH_OBJECT = 1000,
};

////////////////////////////////////////////////////////////
///																				   INPUT                          ///
////////////////////////////////////////////////////////////
#define MOUSE_LEFT GLFW_MOUSE_BUTTON_1
#define MOUSE_RIGHT GLFW_MOUSE_BUTTON_2
#define MOUSE_MIDDLE GLFW_MOUSE_BUTTON_3
