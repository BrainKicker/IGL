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

        void setWindow(GLFWwindow* window);
        void removeWindow();

        void pushEvent(const Event& event);

        Event pollEvent();
        Event waitEvent();
    };
}