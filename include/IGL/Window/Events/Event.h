#pragma once

#include <IGL/Config.h>


namespace igl {


    struct Event {

        struct SizeEvent {
            int width;
            int height;
        };

        struct KeyEvent {
            int key;
            int scancode;
            int action;
            int mods;
        };

        struct SymbolEvent {
            uint32 unicode;
        };

        struct SymbolModsEvent {
            uint32 unicode;
            int mods;
        };

        struct MouseMoveEvent {
            double x;
            double y;
        };

        struct MouseButtonEvent {
            int button;
            int action;
            int mods;
        };

        struct JoystickEvent {
            int id;
            int event;
        };

        struct ScrollEvent {
            double x;
            double y;
        };

        struct CursorEnterEvent {
            bool entered;
        };

        struct FrameBufferSizeEvent {
            int width;
            int height;
        };

        struct FocusEvent {
            bool focused;
        };

        struct IconifyEvent {
            bool iconified;
        };

        struct MaximizeEvent {
            bool maximized;
        };

        struct WindowPosEvent {
            int x;
            int y;
        };

        struct WindowContentScaleEvent {
            float x;
            float y;
        };

        enum EventType {

            NO_EVENT,

            Closed,
            Resized,
            Focus,
            Char,
            CharMods,
            Key,
            MouseMove,
            MouseButton,
            Joystick,
            Scroll,
            CursorEnter,
            FrameBufferSize,
            Iconify,
            Maximize,
            WindowMove,
            WindowRefresh,
            WindowContentScale,

            COUNT
        };

        EventType type;

        union {
            SizeEvent size;
            KeyEvent key;
            SymbolEvent symbol;
            SymbolModsEvent symbolMods;
            MouseMoveEvent mouseMove;
            MouseButtonEvent mouseButton;
            JoystickEvent joystick;
            ScrollEvent scroll;
            CursorEnterEvent cursorEnter;
            FrameBufferSizeEvent frameBufferSize;
            FocusEvent focus;
            IconifyEvent iconify;
            MaximizeEvent maximize;
            WindowPosEvent windowPos;
            WindowContentScaleEvent windowContentScale;
        };
    };
}