#include <IGL/Config/Compile.h>
#include <IGL/Graphics/LowLevel/Shader.h>

#include <IGL/System/Util/Files/Files.h>
#include <IGL/System/Util/Types/Types.h>


namespace igl {


    void Shader::compile(const char* vertexCode, const char* fragmentCode) throws(igl::ShaderCreationException) {

        destroy();

        uint vertex = GL_NONE, fragment = GL_NONE;

        int success;

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCode, nullptr);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {

            int infoLogLength;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::string message = "Vertex : compilation failed:\n";
            int logStartPos = message.size();
            message.resize(message.size() + infoLogLength);
            glGetShaderInfoLog(vertex, infoLogLength, nullptr, message.data() + logStartPos);

            throw ShaderCreationException(std::move(message));
        }

        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentCode, nullptr);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {

            int infoLogLength;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::string message = "Fragment : compilation failed:\n";
            int logStartPos = message.size();
            message.resize(message.size() + infoLogLength);
            glGetShaderInfoLog(fragment, infoLogLength, nullptr, message.data() + logStartPos);

            throw ShaderCreationException(std::move(message));
        }

        // Shader Program
        mId = glCreateProgram();
        glAttachShader(mId, vertex);
        glAttachShader(mId, fragment);
        glLinkProgram(mId);

        glGetProgramiv(mId, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {

            int infoLogLength;
            glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::string message = "Shader : program linking failed:\n";
            int logStartPos = message.size();
            message.resize(message.size() + infoLogLength);
            glGetShaderInfoLog(fragment, infoLogLength, nullptr, message.data() + logStartPos);

            throw ShaderCreationException(std::move(message));
        }

        glDetachShader(mId, vertex);
        glDetachShader(mId, fragment);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }



    Shader::Shader() : mId(GL_NONE) {}

    Shader::Shader(Shader&& other) : mId(other.mId) {
        other.mId = GL_NONE;
    }



    Shader::~Shader() {
        destroy();
    }



    Shader& Shader::operator=(Shader&& other) {

        destroy();

        mId = other.mId;

        other.mId = GL_NONE;

        return *this;
    }



    void Shader::loadFromFiles(const std::string& vertexFilename, const std::string& fragmentFilename) throws(igl::ShaderCreationException) {
        try {
            compile(Files::readFile(vertexFilename).c_str(),
                    Files::readFile(fragmentFilename).c_str());
        } catch (const std::ios_base::failure& e) {
            throw ShaderCreationException("File not successfully read");
        }
    }

    void Shader::loadFromMemory(const std::string& vertexCode, const std::string& fragmentCode) throws(igl::ShaderCreationException) {
        compile(vertexCode.c_str(), fragmentCode.c_str());
    }



    void Shader::destroy() {
        glDeleteProgram(mId);
        mId = GL_NONE;
    }



//    template <typename T>
//    void Shader::setUniform(const std::string& name, const T& t) const {
//        throw BadUniformValue(
//                "Cannot set uniform value with type '" + Types::typeName<T>() + "' by name '" + name
//                + "' to shader with id '" + std::to_string(mId) + "'");
//    }
    void Shader::setUniform(const std::string& name, const float& f) const {
        glProgramUniform1f(mId, glGetUniformLocation(mId, name.c_str()), f);
    }
    void Shader::setUniform(const std::string& name, const double& d) const {
        glProgramUniform1d(mId, glGetUniformLocation(mId, name.c_str()), d);
    }
    void Shader::setUniform(const std::string& name, const int& i) const {
        glProgramUniform1i(mId, glGetUniformLocation(mId, name.c_str()), i);
    }
    void Shader::setUniform(const std::string& name, const uint& ui) const {
        glProgramUniform1ui(mId, glGetUniformLocation(mId, name.c_str()), ui);
    }



//    template <int L, typename T>
//    void Shader::setUniform(const std::string& name, const iglm::Vector<L, T>& vector) const {
//        throw BadUniformValue(
//                "Cannot set uniform vector with size '" + std::to_string(L)
//                + "' and value type '" + Types::typeName<T>() + "' by name '" + name
//                + "' to shader with id '" + std::to_string(mId) + "'");
//    }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<2, float>& vector) const {
        glProgramUniform2fv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<2, double>& vector) const {
        glProgramUniform2dv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<2, int>& vector) const {
        glProgramUniform2iv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<2, uint>& vector) const {
        glProgramUniform2uiv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<3, float>& vector) const {
        glProgramUniform3fv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<3, double>& vector) const {
        glProgramUniform3dv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<3, int>& vector) const {
        glProgramUniform3iv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<3, uint>& vector) const {
        glProgramUniform3uiv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<4, float>& vector) const {
        glProgramUniform4fv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<4, double>& vector) const {
        glProgramUniform4dv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<4, int>& vector) const {
        glProgramUniform4iv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Vector<4, uint>& vector) const {
        glProgramUniform4uiv(mId, glGetUniformLocation(mId, name.c_str()), 1, iglm::valuePtr(vector)); }



//    template <int C, int R, typename T>
//    void Shader::setUniform(const std::string& name, const iglm::Matrix<C, R, T>& matrix) const {
//        throw BadUniformValue(
//                "Cannot set uniform matrix with size '" + std::to_string(C) + "x" + std::to_string(R)
//                + "' and value type '" + Types::typeName<T>() + "' by name '" + name
//                + "' to shader with id '" + std::to_string(mId) + "'");
//    }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<2, 2, float>& matrix) const {
        glProgramUniformMatrix2fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
//    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<2, 2, double>& matrix) const {
//        glProgramUniformMatrix2dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<2, 3, float>& matrix) const {
        glProgramUniformMatrix2x3fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<2, 3, double>& matrix) const {
        glProgramUniformMatrix2x3dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<2, 4, float>& matrix) const {
        glProgramUniformMatrix2x4fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<2, 4, double>& matrix) const {
        glProgramUniformMatrix2x4dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<3, 2, float>& matrix) const {
        glProgramUniformMatrix3x2fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<3, 2, double>& matrix) const {
        glProgramUniformMatrix3x2dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<3, 3, float>& matrix) const {
        glProgramUniformMatrix3fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<3, 3, double>& matrix) const {
        glProgramUniformMatrix3dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<3, 4, float>& matrix) const {
        glProgramUniformMatrix3x4fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<3, 4, double>& matrix) const {
        glProgramUniformMatrix3x4dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<4, 2, float>& matrix) const {
        glProgramUniformMatrix4x2fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<4, 2, double>& matrix) const {
        glProgramUniformMatrix4x2dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<4, 3, float>& matrix) const {
        glProgramUniformMatrix4x3fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<4, 3, double>& matrix) const {
        glProgramUniformMatrix4x3dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<4, 4, float>& matrix) const {
        glProgramUniformMatrix4fv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }
    template <> void Shader::setUniform(const std::string& name, const iglm::Matrix<4, 4, double>& matrix) const {
        glProgramUniformMatrix4dv(mId, glGetUniformLocation(mId, name.c_str()), 1, false, iglm::valuePtr(matrix)); }



    void Shader::setProjection(const iglm::Matrix4& projection) const {
        setUniform("projection", projection);
    }

    void Shader::setView(const iglm::Matrix4& view) const {
        setUniform("view", view);
    }

    void Shader::setModel(const iglm::Matrix4& model) const {
        setUniform("model", model);
    }

    void Shader::setProjview(const iglm::Matrix4& projview) const {
        setUniform("projview", projview);
    }

    void Shader::setViewmodel(const iglm::Matrix4& viewmodel) const {
        setUniform("viewmodel", viewmodel);
    }



    void Shader::use() const {
        glUseProgram(mId);
    }
}