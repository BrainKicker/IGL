#pragma once

#include <IGL/igl_compile_includes.h>


namespace igl {


    class Mesh {

        uint mVAO = GL_NONE, mVBO = GL_NONE;
        uint mVerticesCount = 0;

        void glDelete();

    public:

        Mesh();
        Mesh(const float* buffer, uint verticesCount, const int* attrs);
        Mesh(Mesh&& other);

        ~Mesh();

        Mesh& operator=(Mesh&& other);

        void create(const float* buffer, uint verticesCount, const int* attrs);

        void draw(uint primitive = GL_TRIANGLES) const;
    };
}