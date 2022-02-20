#ifdef IGL_COMPILE
    #include <IGL/Config/Compile.h>
#endif // IGL_COMPILE


#ifdef IGL_DEBUG
    #include <IGL/Config/Debug.h>
#endif // IGL_DEBUG


#if defined(IGL_COMPILE) | defined(IGL_DEBUG)

    #ifndef IGL_INCLUDE_ALL
        #define IGL_INCLUDE_ALL
    #endif // IGL_INCLUDE_ALL

    #ifndef IGL_MACROS_ALL
        #define IGL_MACROS_ALL
    #endif // IGL_MACROS_ALL

    #ifndef IGL_GRAPHICS_ALL
        #define IGL_GRAPHICS_ALL
    #endif // IGL_GRAPHICS_ALL

#endif // IGL_COMPILE | IGL_DEBUG


#include <IGL/Config/Includes.h>
#include <IGL/Config/Typedefs.h>
#include <IGL/Config/Macros.h>