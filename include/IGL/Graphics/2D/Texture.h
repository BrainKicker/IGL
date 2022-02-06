#pragma once

#include <IGL/igl_compile_includes.h>

#include <IGL/System.h>

namespace igl {
    namespace d2 {


        class TextureCreationException : public MessageException {
        public:
            TextureCreationException(const std::string& message) : MessageException(message) {}
        };


        class Texture {

            uint mId = GL_NONE;
            uint mWidth = 0, mHeight = 0;

            void glDelete();

        public:

            explicit Texture(const std::string& filename);
            Texture(Texture&& other);

            ~Texture();

            Texture& operator=(Texture&& other);

            void load(const std::string& filename);

            void bind() const;
        };
    }
}