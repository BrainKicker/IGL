#include <IGL/Config/Compile.h>
#include <IGL/Window/Window.h>


namespace igl {


    Window::Window(int width, int height, const std::string& title) throws(igl::WindowCreationException)
    : mWidth(width), mHeight(height), mTitle(title) {

        if (glfwInit() != GLFW_TRUE)
            throw WindowCreationError("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, true);

        mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (mWindow == nullptr) {
            destroy();
            throw WindowCreationError("Failed to create window");
        }

        glewExperimental = true;

        if (glewInit() != GLEW_OK) {
            destroy();
            throw WindowCreationError("Failed to initialize GLEW");
        }

        requestFocus();

        glEnable(GL_DEPTH_TEST);

        mEvents.attachWindow(this);
    }



    Window::~Window() {
        destroy();
    }



    GLFWwindow* Window::getGLFWwindow() {
        return mWindow;
    }



    void Window::destroy() {
        mEvents.detachWindow();
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
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



    sptr<View> Window::getView() const {
        return mView;
    }

    void Window::setView(const sptr<View>& view) {
        mView = view;
    }



    bool Window::isOpen() const {
        return !glfwWindowShouldClose(mWindow);
    }

    void Window::close() const {
        glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
    }



    void Window::setCursorMode(CursorMode mode) const {
        glfwSetInputMode(mWindow, GLFW_CURSOR, (int) mode);
    }

    Window::CursorMode Window::getCursorMode() const {
        return (CursorMode) glfwGetInputMode(mWindow, GLFW_CURSOR);
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
                close();
                break;
            // TODO other cases
            default:
                break;
        }
    }



    void Window::clear(const Color& color) const {
        requestFocus();
        glClearColor(color.r, color.g, color.b, color.a);
    }



    void Window::requestFocus() const {
        glfwMakeContextCurrent(mWindow);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, mWidth, mHeight);
    }



    void Window::draw() {
        requestFocus();
        if (mView != nullptr)
            glBlitFramebuffer(0, 0, mView->getWidth(), mView->getHeight(), 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        mDrawn = true;
    }



    void Window::display() {
        if (mDrawn) {
            glfwSwapBuffers(mWindow);
            mDrawn = false;
        }
    }
}