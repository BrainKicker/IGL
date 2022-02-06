#pragma once

#include <IGL/igl_compile_includes.h>

#include <IGL/System.h>

namespace igl {


    class ShaderCreationException : public MessageException {
    public:
        ShaderCreationException(const std::string& message) : MessageException(message) {}
    };


    class Shader {

        uint mId = GL_NONE;

        void glDelete();

        void uniformMatrix(const std::string& name, const glm::mat4& matrix) const;

    public:

        Shader(const std::string& vertexFilename, const std::string& fragmentFilename);
        Shader(Shader&& other);

        ~Shader();

        Shader& operator=(Shader&& other);

        void load(const std::string& vertexFilename, const std::string& fragmentFilename);

        void setModel(const glm::mat4& model) const;

        void setProjView(const glm::mat4& projview) const;

        void use() const;
    };
}