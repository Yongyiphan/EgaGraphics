#pragma once
#ifndef EPCH_H
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <limits>

#ifdef ELIB_OPENGL
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define E_API __declspec(dllimport) 
#define unref(x) (void)x
#include "Defines.h"
//#include "Core.h"
#include "Event/Event.h"
#include "Globals.h"
#include "ECS/ECS.h"

#endif //EPCH.H
