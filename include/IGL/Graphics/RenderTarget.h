#pragma once

#include <IGL/Config.h>



namespace igl {


    // pre-declaration
    class Mesh;


    // abstract
    class RenderTarget {
    public:

        virtual ~RenderTarget() = default;

        virtual void draw(const Mesh& mesh) const = 0;
    };
}