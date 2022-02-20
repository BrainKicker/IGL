#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Exception/ExceptionWithStackTrace.h>


namespace igl {
    namespace d2 {


        class TextureCreationException : public ExceptionWithStackTrace {
        public:
            TextureCreationException(const std::string& message) : ExceptionWithStackTrace(message) {}
        };


        class Texture {

            uint mId;
            uint mWidth, mHeight;

        public:

            Texture();
            explicit Texture(const std::string& filename) throws(igl::TextureCreationException);
            Texture(Texture&& other);

            ~Texture();

            Texture& operator=(Texture&& other);

            void load(const std::string& filename) throws(igl::TextureCreationException);

            void destroy();

            void bind() const;
        };
    }

    using Texture2D = d2::Texture;
}