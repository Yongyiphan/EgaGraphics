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

#include <GL/glew.h>
#include <glm/glm.hpp>

#define E_API __declspec(dllimport) 
#define unref(x) (void)x
#include "Defines.h"
//#include "Core/Core.h"
#include "Core/Event.h"
#include "Core/Globals.h"
#include "Core/ECS.h"

#endif //EPCH.H
