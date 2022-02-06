#include "IGL/IGL.h"

int main() {
    std::cout << "Hello, World!\n";
    igl::Window window(1000, 500, "Window");
    while (!window.shouldClose()) {
        igl::Event event = window.pollEvent();
        switch (event.type) {
            case igl::Event::Closed:
                window.setShouldClose(true);
                break;
            default:
                window.handleEvent(event);
                break;
        }
    }
}