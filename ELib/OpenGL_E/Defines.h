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

#define ASSERT_MSG(msg)\
do{\
				E_LOG("FATAL", msg);\
				std::raise(SIGABRT);\
} while (0)


