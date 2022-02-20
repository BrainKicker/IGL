#pragma once

#include <IGL/Config.h>

// pre-declaration
class Mesh;


namespace igl {


    // abstract
    class RenderTarget {
    public:

        virtual ~RenderTarget() = default;

        virtual void draw(const Mesh& mesh) const = 0;
    };
}