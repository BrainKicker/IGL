#pragma once

#define IGL_MACRO_THROWS
#include <IGL/Config.h>

#include <IGL/System/Throwable/Error/RuntimeError.h>

#include <IGL/Graphics/Color.h>

#include <IGL/Window/Events/Event.h>
#include <IGL/Window/Events/Events.h>
#include <IGL/Window/View/View.h>

#include <string>


// pre-declaration
class GLFWwindow;


namespace igl {


    class WindowCreationError : public RuntimeError {
    public:
        WindowCreationError(const std::string& message = "") : RuntimeError(message) {}
    };


    class Window {

        GLFWwindow* mWindow;
        int mWidth, mHeight;
        std::string mTitle;

        sptr<View> mView = nullptr;

        Events mEvents;

        bool mDrawn = false;

    public:

        enum class CursorMode {
            NORMAL   = 0x00034001, // = GLFW_CURSOR_NORMAL
            HIDDEN   = 0x00034002, // = GLFW_CURSOR_HIDDEN
            DISABLED = 0x00034003  // = GLFW_CURSOR_DISABLED
        };

        explicit Window(int width, int height, const std::string& title) throws(igl::WindowCreationError);

        ~Window();

        GLFWwindow* getGLFWwindow();

        void destroy();

        int getWidth() const;
        int getHeight() const;

        const std::string& getTitle() const;
        void setTitle(const std::string& title);

        sptr<View> getView() const;
        void setView(const sptr<View>& view);

        bool isOpen() const;
        void close() const;

        void setCursorMode(CursorMode mode) const;
        CursorMode getCursorMode() const;

        Event pollEvent();
        Event waitEvent();
        Event waitEvent(double timeoutSeconds);

        void handleEvent(const Event& event);

        void clear(const Color& color = {}) const;

        void requestFocus() const;

        void draw();

        void display();
    };
}