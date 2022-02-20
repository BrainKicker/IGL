#pragma once

#include <IGL/Config.h>

#include <IGL/Graphics/LowLevel/PrimitiveType.h>


namespace igl {


    class Mesh {

        uint mVAO, mVBO;
        int mVerticesCount;
        PrimitiveType mPrimitiveType = PrimitiveType::Triangles;

        void genVBO();
        void deleteVBO();

    public:

        Mesh();
        Mesh(const float* buffer, int verticesCount, const int* attrs);
        Mesh(Mesh&& other);

        ~Mesh();

        Mesh& operator=(Mesh&& other);

        PrimitiveType getPrimitiveType() const;
        void setPrimitiveType(PrimitiveType primitiveType);

        int getVerticesCount() const;

        void create(const float* buffer, int verticesCount, const int* attrs);

        void destroy(bool deleteBuff = true);

        void draw() const;
        void draw(PrimitiveType primitiveType) const;
        void draw(int from, int count, PrimitiveType primitiveType) const;
    };
}