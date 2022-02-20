#include <IGL/Config/Compile.h>
#include <IGL/Graphics/2D/Texture.h>


namespace igl {
    namespace d2 {


        Texture::Texture() : mId(GL_NONE), mWidth(0), mHeight(0) {}

        Texture::Texture(const std::string& filename) throws(igl::TextureCreationException) : Texture() {
            load(filename);
        }

        Texture::Texture(Texture&& other) : mId(other.mId), mWidth(other.mWidth), mHeight(other.mHeight) {
            other.mId = GL_NONE;
            other.mWidth = other.mHeight = 0;
        }



        Texture::~Texture() {
            destroy();
        }



        Texture& Texture::operator=(Texture&& other) {

            destroy();

            mId = other.mId;
            mWidth = other.mWidth;
            mHeight = other.mHeight;

            other.mId = GL_NONE;
            other.mWidth = other.mHeight = 0;

            return *this;
        }



        void Texture::load(const std::string& filename) throws(igl::TextureCreationException) {

            destroy();

            uint* image = (uint*) SOIL_load_image(
                    filename.c_str(),
                    (int*)&mWidth,
                    (int*)&mHeight,
                    nullptr,
                    SOIL_LOAD_RGBA);

            if (image == nullptr)
                throw TextureCreationException("Failed to read file");

            for (uint j = 0; j < mHeight/2; ++j)
                for (uint i = 0; i < mWidth; ++i)
                    std::swap(image[j*mWidth+i], image[(mHeight-1-j)*mWidth+i]);

            glGenTextures(1, &mId);
            glBindTexture(GL_TEXTURE_2D, mId);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    mWidth,
                    mHeight,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    image);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, GL_NONE);

            SOIL_free_image_data((uchar*)image);
        }



        void Texture::destroy() {
            glDeleteTextures(1, &mId);
            mId = GL_NONE;
            mWidth = mHeight = 0;
        }



        void Texture::bind() const {
            glBindTexture(GL_TEXTURE_2D, mId);
        }
    }
}