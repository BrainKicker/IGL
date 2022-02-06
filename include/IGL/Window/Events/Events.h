#pragma once

#include <IGL/igl_compile_includes.h>

#include <IGL/Window/Events/Event.h>

namespace igl {

    class Events {

        GLFWwindow* mWindow = nullptr;
        std::queue<Event> mEvents;

    public:

        Events();

        ~Events();

        void attachWindow(GLFWwindow* window);
        void detachWindow();

        void pushEvent(const Event& event);

        Event pollEvent();
        Event waitEvent();
        Event waitEvent(double timeoutSeconds);
    };
}