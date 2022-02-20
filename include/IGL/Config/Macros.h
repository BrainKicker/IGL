#include <IGL/Config/Includes.h>


#ifdef IGL_MACROS_ALL
    #ifndef IGL_MACRO_THROWS
        #define IGL_MACRO_THROWS
    #endif // IGL_MACRO_THROWS
#endif // IGL_MACROS_ALL


#ifdef IGL_MACRO_THROWS
    #define throws(...) noexcept(false)
#endif // IGL_MACRO_THROWS