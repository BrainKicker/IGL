#include <IGL/Window/Events/Events.h>


namespace igl {


    static std::map<GLFWwindow*,Events*> sMap;


    void registerEvents(GLFWwindow* window, Events* events) {
        sMap[window] = events;
    }

    void unregisterEvents(GLFWwindow* window) {
        sMap.erase(window);
    }


    void callback(GLFWwindow* window, const std::function<Event()>& eventGen) {
        Events* events = sMap[window];
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
        callback(window, [&]() { return Event{ Event::Closed }; });
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
        callback(window, [&]() { return Event{ Event::WindowRefresh }; });
    }
    void windowContentScaleCallback(GLFWwindow* window, float x, float y) {
        callback(window, [&]() {
            return Event{ Event::WindowContentScale, { .windowContentScale = { x, y } } }; });
    }


    Events::Events() {}



    Events::~Events() {
        removeWindow();
    }



    void Events::setWindow(GLFWwindow* window) {

        removeWindow();

        mWindow = window;

        registerEvents(window, this);

        glfwSetKeyCallback(window, keyCallback);
        glfwSetCharCallback(window, charCallback);
        glfwSetCharModsCallback(window, charModsCallback);
        glfwSetScrollCallback(window, scrollCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, cursorPosCallback);
        glfwSetCursorEnterCallback(window, cursorEnterCallback);
        glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
        glfwSetWindowCloseCallback(window, windowCloseCallback);
        glfwSetWindowFocusCallback(window, windowFocusCallback);
        glfwSetWindowIconifyCallback(window, windowIconifyCallback);
        glfwSetWindowMaximizeCallback(window, windowMaximizeCallback);
        glfwSetWindowPosCallback(window, windowPosCallback);
        glfwSetWindowRefreshCallback(window, windowRefreshCallback);
        glfwSetWindowContentScaleCallback(window, windowContentScaleCallback);
    }

    void Events::removeWindow() {

        if (mWindow == nullptr)
            return;

        unregisterEvents(mWindow);

        glfwSetKeyCallback(mWindow, nullptr);
        glfwSetCharCallback(mWindow, nullptr);
        glfwSetCharModsCallback(mWindow, nullptr);
        glfwSetScrollCallback(mWindow, nullptr);
        glfwSetWindowSizeCallback(mWindow, nullptr);
        glfwSetMouseButtonCallback(mWindow, nullptr);
        glfwSetCursorPosCallback(mWindow, nullptr);
        glfwSetCursorEnterCallback(mWindow, nullptr);
        glfwSetFramebufferSizeCallback(mWindow, nullptr);
        glfwSetWindowCloseCallback(mWindow, nullptr);
        glfwSetWindowFocusCallback(mWindow, nullptr);
        glfwSetWindowIconifyCallback(mWindow, nullptr);
        glfwSetWindowMaximizeCallback(mWindow, nullptr);
        glfwSetWindowPosCallback(mWindow, nullptr);
        glfwSetWindowRefreshCallback(mWindow, nullptr);
        glfwSetWindowContentScaleCallback(mWindow, nullptr);

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
            return { Event::NO_EVENT };
        glfwMakeContextCurrent(mWindow);
        glfwPollEvents();
        if (mEvents.empty())
            return { Event::NO_EVENT };
        return pop(mEvents);
    }

    Event Events::waitEvent() {
        if (mWindow == nullptr)
            return { Event::NO_EVENT };
        glfwMakeContextCurrent(mWindow);
        glfwWaitEvents();
        return pop(mEvents);
    }
}