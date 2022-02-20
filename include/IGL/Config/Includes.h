#ifdef IGL_INCLUDE_ALL

    #ifndef IGL_INCLUDE_STL
        #define IGL_INCLUDE_STL
    #endif // IGL_INCLUDE_STL


    #ifndef IGL_INCLUDE_BOOST
        #define IGL_INCLUDE_BOOST
    #endif // IGL_INCLUDE_BOOST

    #ifndef IGL_INCLUDE_ABI
        #define IGL_INCLUDE_ABI
    #endif // IGL_INCLUDE_ABI

    #ifndef IGL_INCLUDE_OPENGL
        #define IGL_INCLUDE_OPENGL
    #endif // IGL_INCLUDE_OPENGL

    #ifndef IGL_INCLUDE_GL_MATH
        #define IGL_INCLUDE_GL_MATH
    #endif // IGL_INCLUDE_GL_MATH

    #ifndef IGL_INCLUDE_SOIL
        #define IGL_INCLUDE_SOIL
    #endif // IGL_INCLUDE_SOIL

#endif // IGL_INCLUDE_ALL


#ifdef IGL_INCLUDE_STL

    // streams
    #include <iostream>
    #include <fstream>
    #include <sstream>

    // containers
    #include <initializer_list>
    #include <string>
    #include <vector>
    #include <map>
    #include <queue>

    // smart ptrs
    #include <memory>

    // exceptions and errors
    #include <exception>
    #include <stdexcept>

    // time
    #include <chrono>

    // math
    #include <cmath>
    #include <numeric>

    // functions
    #include <functional>

    // types
    #include <cstdint>

#endif // IGL_INCLUDE_STL



#ifdef IGL_INCLUDE_BOOST

    // boost::stacktrace
    #define BOOST_STACKTRACE_USE_ADDR2LINE
    #include <boost/stacktrace.hpp>

#endif // IGL_INCLUDE_BOOST



#ifdef IGL_INCLUDE_ABI

    // abi
    #include <cxxabi.h>

#endif // IGL_INCLUDE_ABI



#ifdef IGL_INCLUDE_OPENGL

    // opengl
    #ifndef GLEW_STATIC
        #define GLEW_STATIC
    #endif // GLEW_STATIC
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>

#endif // IGL_INCLUDE_OPENGL



#ifdef IGL_INCLUDE_GL_MATH

    // glm
    #include <glm/glm.hpp>
    #include <glm/ext.hpp>
    #include <glm/gtc/type_ptr.hpp>

#endif // IGL_INCLUDE_GL_MATH



#ifdef IGL_INCLUDE_SOIL

    // image
    #include <SOIL/SOIL.h>

#endif // IGL_INCLUDE_SOIL