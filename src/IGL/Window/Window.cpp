#include <IGL/Window/Window.h>


namespace igl {


    void Window::setCursorMode(int mode) const {
        glfwSetInputMode(mWindow, GLFW_CURSOR, mode);
    }



    void Window::swapBuffers() const {
        glfwSwapBuffers(mWindow);
    }



    Window::Window(int width, int height, const std::string& title)
            : mWidth(width), mHeight(height), mTitle(title) {

        if (glfwInit() != GLFW_TRUE)
            throw WindowCreationException("Failed to init GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, true);

        mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (mWindow == nullptr)
            throw WindowCreationException("Failed to create window");

        requestFocus();

        glewExperimental = true;

        if (glewInit() != GLEW_OK)
            throw WindowCreationException("Failed to initialize GLEW");

        glViewport(0, 0, width, height);

        mEvents.attachWindow(mWindow);
    }



    Window::~Window() {
        mEvents.detachWindow();
        glfwDestroyWindow(mWindow);
    }



    int Window::getWidth() const {
        return mWidth;
    }

    int Window::getHeight() const {
        return mHeight;
    }



    const std::string& Window::getTitle() const {
        return mTitle;
    }

    void Window::setTitle(const std::string& title) {
        glfwSetWindowTitle(mWindow, title.c_str());
        mTitle = title;
    }



    GLFWwindow* Window::getGLFWwindow() {
        return mWindow;
    }



    bool Window::shouldClose() const {
        return glfwWindowShouldClose(mWindow);
    }

    void Window::setShouldClose(bool flag) {
        glfwSetWindowShouldClose(mWindow, flag);
    }



    void Window::requestFocus() const {
        glfwMakeContextCurrent(mWindow);
    }



    Event Window::pollEvent() {
        return mEvents.pollEvent();
    }

    Event Window::waitEvent() {
        return mEvents.waitEvent();
    }

    Event Window::waitEvent(double timeoutSeconds) {
        return mEvents.waitEvent(timeoutSeconds);
    }



    void Window::handleEvent(const Event& event) {
        switch (event.type) {
            case Event::Closed:
                setShouldClose(true);
                break;
            // TODO other cases
            default:
                break;
        }
    }
}