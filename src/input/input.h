#ifndef INPUT_H
#define INPUT_H

enum KeyboardAction {
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
};
enum KeyboardKeys {
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_UP_ARROW,
    KEY_DOWN_ARROW,
    KEY_LEFT_ARROW,
    KEY_RIGHT_ARROW,
    KEY_LEFT_SHIFT,
    KEY_RIGHT_SHIFT,
    KEY_SPACE,
    KEYBOARD_NUM_KEYS
};
typedef uint8_t KeyboardKeyCode;
struct KeyboardKey {
    KeyboardKeyCode code;

    // Methods here return EOF when the mapping is invalid.
    static int to_char(KeyboardKey key);
    static int from_char(char c);
};

struct KeyboardEvent {
    KeyboardKey key;
    uint8_t action;
};

struct CursorState {
    float x;
    float y;
    float dx;
    float dy; // x,y,dx,dy are always available no matter the event.
};
enum MouseAction {
    MOUSE_BUTTON_PRESS,
    MOUSE_BUTTON_RELEASE,
    MOUSE_MOVE,
    MOUSE_SCROLL,
};
enum MouseButtons {
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_NUM_BUTTONS
};
typedef uint8_t MouseButtonCode;
struct MouseButton {
    uint8_t code;
};

struct MouseEvent {
    uint8_t action;
    MouseButton button;
    CursorState cursor; // No matter the event, this struct is filled.
    float scroll_y;
};

struct InputListener {
    bool listening;
    virtual void keyboard_handler(KeyboardEvent e) = 0;
    virtual void mouse_handler(MouseEvent e) = 0;
};

struct KeyboardState {
    // Each key has bit-flags to signify its state.
    // Starting with the least significant bit:
    //    Bit 0:  0:down    1:up
    // todo:
    //    Bit 1:  1 signifies the key become pressed one "input-cycle" ago (whatever manages the InputState handles this).
    //    Bit 2:  Same as above but for when the key is released.
    uint8_t key_flags[KEYBOARD_NUM_KEYS];
    bool down(KeyboardKeyCode code) const;
};
struct MouseState {
    uint8_t button_flags[MOUSE_NUM_BUTTONS];
    bool down(MouseButtonCode code) const;
};

// InputState listens to input events and tracks state, such as keys that are held down.
struct InputState : public InputListener {
    void keyboard_handler(KeyboardEvent e);
    void mouse_handler(MouseEvent e);
    KeyboardState keyboard;
    MouseState mouse;
};

#endif // INPUT_H
