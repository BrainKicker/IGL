#include <IGL/Config/Compile.h>
#include <IGL/Graphics/2D/RenderTexture.h>

#include <IGL/Graphics/LowLevel/Mesh.h>


namespace igl {
    namespace d2 {


        RenderTexture::RenderTexture()
        : mFrameBuffer(GL_NONE), mRenderTexture(GL_NONE), mDepthBuffer(GL_NONE), mWidth(0), mHeight(0) {}

        RenderTexture::RenderTexture(uint width, uint height) throws(igl::d2::RenderTextureCreationException)
        : RenderTexture() {
            create(width, height);
        }

        RenderTexture::RenderTexture(RenderTexture&& other)
        : mFrameBuffer(other.mFrameBuffer),
        mRenderTexture(other.mRenderTexture),
        mDepthBuffer(other.mDepthBuffer),
        mWidth(other.mWidth), mHeight(other.mHeight) {
            other.mFrameBuffer = other.mRenderTexture = other.mDepthBuffer = GL_NONE;
            other.mWidth = other.mHeight = 0;
        }



        RenderTexture::~RenderTexture() {
            destroy();
        }



        RenderTexture& RenderTexture::operator=(RenderTexture&& other) {
            mFrameBuffer = other.mFrameBuffer;
            mRenderTexture = other.mRenderTexture;
            mDepthBuffer = other.mDepthBuffer;
            mWidth = other.mWidth;
            mHeight = other.mHeight;
            other.mFrameBuffer = other.mRenderTexture = other.mDepthBuffer = GL_NONE;
            other.mWidth = other.mHeight = 0;
            return *this;
        }



        void RenderTexture::create(uint width, uint height) throws(igl::d2::RenderTextureCreationException) {

            destroy();

            mWidth = width;
            mHeight = height;

            glGenFramebuffers(1, &mFrameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);

            glGenTextures(1, &mRenderTexture);
            glBindTexture(GL_TEXTURE_2D, mRenderTexture);

            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    width,
                    height,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glGenRenderbuffers(1, &mDepthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mRenderTexture, 0);

            static const std::vector<uint> drawBuffers { GL_COLOR_ATTACHMENT0 };
            glDrawBuffers(drawBuffers.size(), drawBuffers.data());

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                destroy();
                throw RenderTextureCreationException("Framebuffer error");
            }
        }



        void RenderTexture::destroy() {
            glDeleteFramebuffers(1, &mFrameBuffer);
            glDeleteTextures(1, &mRenderTexture);
            glDeleteRenderbuffers(1, &mDepthBuffer);
            mFrameBuffer = mRenderTexture = mDepthBuffer = GL_NONE;
            mWidth = mHeight = 0;
        }



        void RenderTexture::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
        }



        void RenderTexture::draw(const Mesh& mesh) const {
            bind();
            mesh.draw();
        }
    }
}