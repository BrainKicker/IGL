#pragma once

#include <IGL/Config.h>

#include <IGL/System.h>

#include <IGL/Graphics/Color.h>
#include <IGL/Graphics/LowLevel/PrimitiveType.h>
#include <IGL/Graphics/LowLevel/Mesh.h>
#include <IGL/Graphics/LowLevel/Shader.h>

#ifdef IGL_GRAPHICS_ALL
    #define IGL_GRAPHICS_2D
    #define IGL_GRAPHICS_3D
#endif // IGL_GRAPHICS_ALL

#ifdef IGL_GRAPHICS_2D
    #include <IGL/Graphics/Graphics2D.h>
#endif
#ifdef IGL_GRAPHICS_3D
    #include <IGL/Graphics/Graphics3D.h>
#endif