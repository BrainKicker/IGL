#include <IGL/Config/Compile.h>
#include <IGL/Window/Events/Events.h>

#include <IGL/Window/Window.h>


namespace igl {


    static std::map<GLFWwindow*,Events*> sEventsMap;


    void registerEvents(GLFWwindow* window, Events* events) {
        sEventsMap[window] = events;
    }

    void unregisterEvents(GLFWwindow* window) {
        sEventsMap.erase(window);
    }


    void callback(GLFWwindow* window, const Instantiator<Event>& eventGen) {
        Events* events = sEventsMap[window];
        if (events == nullptr)
            return;
        events->pushEvent(eventGen());
    }


    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        callback(window, [&]() {
            return Event{ Event::Key, { .key = { key, scancode, action, mods } } }; });
    }
    void charCallback(GLFWwindow* window, uint32 unicode) {
        callback(window, [&]() {
            return Event{ Event::Char, { .symbol = { unicode } } }; });
    }
    void charModsCallback(GLFWwindow* window, uint32 unicode, int mods) {
        callback(window, [&]() {
            return Event{ Event::CharMods, { .symbolMods = { unicode, mods } } }; });
    }
    void scrollCallback(GLFWwindow* window, double x, double y) {
        callback(window, [&]() {
            return Event{ Event::Scroll, { .scroll={ x, y } } }; });
    }
    void windowSizeCallback(GLFWwindow* window, int width, int height) {
        callback(window, [&]() {
            return Event{ Event::Resized, { .size={ width, height } } }; });
    }
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        callback(window, [&]() {
            return Event{ Event::MouseButton, { .mouseButton = { button, action, mods } } }; });
    }
    void cursorPosCallback(GLFWwindow* window, double x, double y) {
        callback(window, [&]() {
            return Event{ Event::MouseMove, { .mouseMove = { x, y } } }; });
    }
    void cursorEnterCallback(GLFWwindow* window, int entered) {
        callback(window, [&]() {
            return Event{ Event::CursorEnter, { .cursorEnter = { entered == GLFW_TRUE } } }; });
    }
    void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
        callback(window, [&]() {
            return Event{ Event::FrameBufferSize, { .frameBufferSize = { width, height } } }; });
    }
    void windowCloseCallback(GLFWwindow* window) {
        callback(window, [&]() { return Event{ Event::Closed, {} }; });
    }
    void windowFocusCallback(GLFWwindow* window, int focused) {
        callback(window, [&]() {
            return Event{ Event::Focus, { .focus = { focused == GLFW_TRUE } } }; });
    }
    void windowIconifyCallback(GLFWwindow* window, int iconified) {
        callback(window, [&]() {
            return Event{ Event::Iconify, { .iconify = { iconified == GLFW_TRUE } } }; });
    }
    void windowMaximizeCallback(GLFWwindow* window, int maximized) {
        callback(window, [&]() {
            return Event{ Event::Maximize, { .maximize = { maximized == GLFW_TRUE } } }; });
    }
    void windowPosCallback(GLFWwindow* window, int x, int y) {
        callback(window, [&]() {
            return Event{ Event::WindowMove, { .windowPos = { x, y } } }; });
    }
    void windowRefreshCallback(GLFWwindow* window) {
        callback(window, [&]() { return Event{ Event::WindowRefresh, {} }; });
    }
    void windowContentScaleCallback(GLFWwindow* window, float x, float y) {
        callback(window, [&]() {
            return Event{ Event::WindowContentScale, { .windowContentScale = { x, y } } }; });
    }



    Events::~Events() {
        detachWindow();
    }



    void Events::attachWindow(Window* window) {

        detachWindow();

        mWindow = window;

        GLFWwindow* glfwWindow = window->getGLFWwindow();

        registerEvents(glfwWindow, this);

        glfwSetKeyCallback(glfwWindow, keyCallback);
        glfwSetCharCallback(glfwWindow, charCallback);
        glfwSetCharModsCallback(glfwWindow, charModsCallback);
        glfwSetScrollCallback(glfwWindow, scrollCallback);
        glfwSetWindowSizeCallback(glfwWindow, windowSizeCallback);
        glfwSetMouseButtonCallback(glfwWindow, mouseButtonCallback);
        glfwSetCursorPosCallback(glfwWindow, cursorPosCallback);
        glfwSetCursorEnterCallback(glfwWindow, cursorEnterCallback);
        glfwSetFramebufferSizeCallback(glfwWindow, frameBufferSizeCallback);
        glfwSetWindowCloseCallback(glfwWindow, windowCloseCallback);
        glfwSetWindowFocusCallback(glfwWindow, windowFocusCallback);
        glfwSetWindowIconifyCallback(glfwWindow, windowIconifyCallback);
        glfwSetWindowMaximizeCallback(glfwWindow, windowMaximizeCallback);
        glfwSetWindowPosCallback(glfwWindow, windowPosCallback);
        glfwSetWindowRefreshCallback(glfwWindow, windowRefreshCallback);
        glfwSetWindowContentScaleCallback(glfwWindow, windowContentScaleCallback);
    }

    void Events::detachWindow() {

        if (mWindow == nullptr)
            return;

        GLFWwindow* glfWwindow = mWindow->getGLFWwindow();

        unregisterEvents(glfWwindow);

        glfwSetKeyCallback(glfWwindow, nullptr);
        glfwSetCharCallback(glfWwindow, nullptr);
        glfwSetCharModsCallback(glfWwindow, nullptr);
        glfwSetScrollCallback(glfWwindow, nullptr);
        glfwSetWindowSizeCallback(glfWwindow, nullptr);
        glfwSetMouseButtonCallback(glfWwindow, nullptr);
        glfwSetCursorPosCallback(glfWwindow, nullptr);
        glfwSetCursorEnterCallback(glfWwindow, nullptr);
        glfwSetFramebufferSizeCallback(glfWwindow, nullptr);
        glfwSetWindowCloseCallback(glfWwindow, nullptr);
        glfwSetWindowFocusCallback(glfWwindow, nullptr);
        glfwSetWindowIconifyCallback(glfWwindow, nullptr);
        glfwSetWindowMaximizeCallback(glfWwindow, nullptr);
        glfwSetWindowPosCallback(glfWwindow, nullptr);
        glfwSetWindowRefreshCallback(glfWwindow, nullptr);
        glfwSetWindowContentScaleCallback(glfWwindow, nullptr);

        mWindow = nullptr;
    }



    void Events::pushEvent(const Event& event) {
        mEvents.push(event);
    }



    template <typename T>
    T pop(std::queue<T>& q) {
        T t = q.front();
        q.pop();
        return t;
    }

    Event Events::pollEvent() {
        if (mWindow == nullptr)
            return { Event::NO_EVENT, {} };
        if (mEvents.empty()) {
            glfwMakeContextCurrent(mWindow->getGLFWwindow());
            glfwPollEvents();
        }
        if (mEvents.empty())
            return { Event::NO_EVENT, {} };
        return pop(mEvents);
    }

    Event Events::waitEvent() {
        if (mWindow == nullptr)
            return { Event::NO_EVENT, {} };
        if (mEvents.empty()) {
            glfwMakeContextCurrent(mWindow->getGLFWwindow());
            glfwWaitEvents();
        }
        return pop(mEvents);
    }

    Event Events::waitEvent(double timeoutSeconds) {
        if (mWindow == nullptr)
            return { Event::NO_EVENT, {} };
        if (mEvents.empty()) {
            glfwMakeContextCurrent(mWindow->getGLFWwindow());
            glfwWaitEventsTimeout(timeoutSeconds);
        }
        if (mEvents.empty())
            return { Event::NO_EVENT, {} };
        return pop(mEvents);
    }
}