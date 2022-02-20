#include <IGL/IGL.h>


int main() {

    igl::Window window (1000, 500, "Window");

    window.clear(igl::Color::deepskyblue);

    while (window.isOpen()) {

        igl::Event event = window.pollEvent();

        switch (event.type) {
            default:
                window.handleEvent(event);
                break;
        }

        window.display();
    }
}