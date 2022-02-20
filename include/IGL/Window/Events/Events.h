#pragma once

#include <IGL/Config.h>

#include <IGL/Window/Events/Event.h>

#include <queue>


namespace igl {


    // pre-declaration
    class Window;


    class Events {

        Window* mWindow = nullptr;
        std::queue<Event> mEvents;

    public:

        Events() = default;

        ~Events();

        void attachWindow(Window* window);
        void detachWindow();

        void pushEvent(const Event& event);

        Event pollEvent();
        Event waitEvent();
        Event waitEvent(double timeoutSeconds);
    };
}