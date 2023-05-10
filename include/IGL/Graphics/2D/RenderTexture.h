#pragma once

#include <IGL/Config.h>

#include <IGL/System/Throwable/Exception/ExceptionWithStackTrace.h>
#include <IGL/Graphics/RenderTarget.h>


namespace igl {


    // pre-declaration
    class Mesh;


    namespace d2 {


        class RenderTextureCreationException : public ExceptionWithStackTrace {
        public:
            RenderTextureCreationException(const std::string& message) : ExceptionWithStackTrace(message) {}
        };


        class RenderTexture : public RenderTarget {

            uint mFrameBuffer;
            uint mRenderTexture;
            uint mDepthBuffer;
            uint mWidth, mHeight;

        public:

            RenderTexture();
            RenderTexture(uint width, uint height) throws(igl::d2::RenderTextureCreationException);
            RenderTexture(RenderTexture&& other);

            virtual ~RenderTexture();

            RenderTexture& operator=(RenderTexture&& other);

            void create(uint width, uint height) throws(igl::d2::RenderTextureCreationException);

            void destroy();

            void bind() const;

            void draw(const Mesh& mesh) const override;
        };
    }

    using RenderTexture2D = d2::RenderTexture;
}