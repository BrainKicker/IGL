#pragma once

#define IGL_INCLUDE_GL_MATH
#include <IGL/Config.h>

#include <IGL/Math.h>

#include <IGL/System/Throwable/Exception/ExceptionWithStackTrace.h>
#include "IGL/System/Throwable/Exception/IllegalArgumentException.h"


namespace igl {


    class ShaderCreationException : public ExceptionWithStackTrace {
    public:
        ShaderCreationException(const std::string& message) : ExceptionWithStackTrace(message) {}
        ShaderCreationException(std::string&& message) : ExceptionWithStackTrace(std::move(message)) {}
    };


//    class BadUniformValue : public IllegalArgumentException {
//    public:
//        BadUniformValue(const std::string& message) : IllegalArgumentException(message) {}
//        BadUniformValue(std::string&& message) : IllegalArgumentException(std::move(message)) {}
//    };


    class Shader {

        uint mId;

        void compile(const char* vertexCode, const char* fragmentCode) throws(igl::ShaderCreationException);

    public:

        Shader();
        Shader(Shader&& other);

        ~Shader();

        Shader& operator=(Shader&& other);

        void loadFromFiles(const std::string& vertexFilename, const std::string& fragmentFilename) throws(igl::ShaderCreationException);
        void loadFromMemory(const std::string& vertexCode, const std::string& fragmentCode) throws(igl::ShaderCreationException);

        void destroy();

        void setUniform(const std::string& name, const float& t) const;
        void setUniform(const std::string& name, const double& t) const;
        void setUniform(const std::string& name, const int& t) const;
        void setUniform(const std::string& name, const uint& t) const;

        template <int L, typename T>
        void setUniform(const std::string& name, const iglm::Vector<L, T>& vector) const;

        template <int C, int R, typename T>
        void setUniform(const std::string& name, const iglm::Matrix<C, R, T>& matrix) const;

        void setProjection(const iglm::Matrix4& projection) const;
        void setView(const iglm::Matrix4& view) const;
        void setModel(const iglm::Matrix4& model) const;
        void setProjview(const iglm::Matrix4& projview) const;
        void setViewmodel(const iglm::Matrix4& viewmodel) const;

        void use() const;
    };
}