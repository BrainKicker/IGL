#pragma once

#include <IGL/Config.h>

#include <IGL/Graphics/RenderTarget.h>


namespace igl {


    class View : public RenderTarget {

        uint mWidth, mHeight;

    public:

        virtual ~View() {
            View::destroy();
        }

        virtual void destroy() {}

        uint getWidth() const {
            return mWidth;
        }
        void setWidth(uint width) {
            mWidth = width;
        }

        uint getHeight() const {
            return mHeight;
        }
        void setHeight(uint height) {
            mHeight = height;
        }
    };
}