#pragma once


#ifdef IGL_COMPILE


// streams
#include <iostream>
#include <fstream>
#include <sstream>

// containers
#include <string>
#include <vector>
#include <map>
#include <queue>

// smart ptrs
#include <memory>

// exceptions
#include <exception>

// time
#include <chrono>

// math
#include <cmath>
#include <numeric>

// functions
#include <functional>

// unistd
#include <unistd.h>

// opengl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

// image
#include <SOIL/SOIL.h>


#endif //IGL_COMPILE


#include "igl_typedefs.h"