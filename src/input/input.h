#ifndef INPUT_H
#define INPUT_H

enum KeyboardAction {
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
};
enum KeyboardSpecialKeys {
    KEY_SPACE,
    KEY_LEFT_SHIFT,
    KEY_RIGHT_SHIFT,
};
struct KeyboardEvent {
    bool is_special;
    char character;
    uint8_t special_key;
    uint8_t action;
};

struct CursorState {
    float x;
    float y;
    float dx;
    float dy; // x,y,dx,dy are always available no matter the event.
};
enum MouseAction {
    MOUSE_BUTTON,
    MOUSE_MOVE,
    MOUSE_SCROLL,
};
enum MouseButton {
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
};
struct MouseEvent {
    uint8_t action;
    uint8_t button;
    CursorState cursor; // No matter the event, this struct is filled.
    float scroll_y;
};

#endif // INPUT_H
