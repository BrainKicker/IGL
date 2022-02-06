#pragma once

#include <IGL/igl_compile_includes.h>

#include <IGL/System.h>

#include <IGL/Window/Events/Event.h>
#include <IGL/Window/Events/Events.h>

namespace igl {


    class WindowCreationException : public MessageException {
    public:
        WindowCreationException(const std::string& message = "") : MessageException(message) {}
    };


    class Window {

        GLFWwindow* mWindow;
        int mWidth, mHeight;
        std::string mTitle;

        Events mEvents;

        void setCursorMode(int mode) const;

        void swapBuffers() const;

    public:

        explicit Window(int width, int height, const std::string& title);

        ~Window();

        int getWidth() const;
        int getHeight() const;

        const std::string& getTitle() const;
        void setTitle(const std::string& title);

        GLFWwindow* getGLFWwindow();

        bool shouldClose() const;
        void setShouldClose(bool flag);

        void requestFocus() const;

        Event pollEvent();
        Event waitEvent();

        void handleEvent(const Event& event);
    };
}