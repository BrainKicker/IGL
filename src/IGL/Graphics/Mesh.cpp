#include <IGL/Config/Compile.h>
#include <IGL/Graphics/LowLevel/Mesh.h>

namespace igl {


    void Mesh::genVBO() {
        if (mVBO != GL_NONE)
            return;
        glGenBuffers(1, &mVBO);
    }

    void Mesh::deleteVBO() {
        glDeleteBuffers(1, &mVBO);
        mVBO = GL_NONE;
    }



    Mesh::Mesh() : mVAO(GL_NONE), mVBO(GL_NONE), mVerticesCount(0) {}

    Mesh::Mesh(const float* buffer, int verticesCount, const int* attrs) {
        create(buffer, verticesCount, attrs);
    }

    Mesh::Mesh(Mesh&& other)
            : mVAO(other.mVAO), mVBO(other.mVBO), mVerticesCount(other.mVerticesCount) {
        other.mVAO = other.mVBO = other.mVerticesCount = GL_NONE;
    }



    Mesh::~Mesh() {
        destroy();
    }



    Mesh& Mesh::operator=(Mesh&& other) {

        destroy();

        mVAO = other.mVAO;
        mVBO = other.mVBO;
        mVerticesCount = other.mVerticesCount;

        other.mVAO = other.mVBO = other.mVerticesCount = GL_NONE;

        return *this;
    }



    PrimitiveType Mesh::getPrimitiveType() const {
        return mPrimitiveType;
    }

    void Mesh::setPrimitiveType(PrimitiveType primitiveType) {
        mPrimitiveType = primitiveType;
    }



    int Mesh::getVerticesCount() const {
        return mVerticesCount;
    }



    void Mesh::create(const float* buffer, int verticesCount, const int* attrs) {

        destroy(false);

        mVerticesCount = verticesCount;

        int vertexSize = 0;
        for (int i = 0; attrs[i]; ++i)
            vertexSize += attrs[i];

        glGenVertexArrays(1, &mVAO);
        genVBO();

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * verticesCount, buffer, GL_STATIC_DRAW);

        // attributes
        for (int i = 0, offset = 0; attrs[i]; ++i) {
            int size = attrs[i];
            glVertexAttribPointer(i, size, GL_FLOAT, false, vertexSize * sizeof(float),
                                  (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(i);
            offset += size;
        }

        glBindVertexArray(GL_NONE);
        glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    }



    void Mesh::destroy(bool deleteBuff) {
        glDeleteVertexArrays(1, &mVAO);
        mVAO = GL_NONE;
        if (deleteBuff)
            deleteVBO();
        mVerticesCount = 0;
    }


    void Mesh::draw() const {
        draw(mPrimitiveType);
    }

    void Mesh::draw(PrimitiveType primitiveType) const {
        draw(0, mVerticesCount, primitiveType);
    }

    void Mesh::draw(int from, int count, PrimitiveType primitiveType) const {
        glBindVertexArray(mVAO);
        glDrawArrays((GLenum) primitiveType, from, count);
    }
}