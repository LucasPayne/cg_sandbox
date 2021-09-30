#include "interactive_graphics_context.h"
#include <ctype.h>//tolower
#include <stdio.h>//EOF

int KeyboardKey::to_char(KeyboardKey key)
{
    switch (key.code) {
        case KEY_Q: return 'q';
        case KEY_W: return 'w';
        case KEY_E: return 'e';
        case KEY_R: return 'r';
        case KEY_T: return 't';
        case KEY_Y: return 'y';
        case KEY_U: return 'u';
        case KEY_I: return 'i';
        case KEY_O: return 'o';
        case KEY_P: return 'p';
        case KEY_A: return 'a';
        case KEY_S: return 's';
        case KEY_D: return 'd';
        case KEY_F: return 'f';
        case KEY_G: return 'g';
        case KEY_H: return 'h';
        case KEY_J: return 'j';
        case KEY_K: return 'k';
        case KEY_L: return 'l';
        case KEY_Z: return 'z';
        case KEY_X: return 'x';
        case KEY_C: return 'c';
        case KEY_V: return 'v';
        case KEY_B: return 'b';
        case KEY_N: return 'n';
        case KEY_M: return 'm';
    }
    return EOF;
}
int KeyboardKey::from_char(char c)
{
    char lower_c = tolower(c);
    switch (lower_c) {
        case 'q': return KEY_Q;
        case 'w': return KEY_W;
        case 'e': return KEY_E;
        case 'r': return KEY_R;
        case 't': return KEY_T;
        case 'y': return KEY_Y;
        case 'u': return KEY_U;
        case 'i': return KEY_I;
        case 'o': return KEY_O;
        case 'p': return KEY_P;
        case 'a': return KEY_A;
        case 's': return KEY_S;
        case 'd': return KEY_D;
        case 'f': return KEY_F;
        case 'g': return KEY_G;
        case 'h': return KEY_H;
        case 'j': return KEY_J;
        case 'k': return KEY_K;
        case 'l': return KEY_L;
        case 'z': return KEY_Z;
        case 'x': return KEY_X;
        case 'c': return KEY_C;
        case 'v': return KEY_V;
        case 'b': return KEY_B;
        case 'n': return KEY_N;
        case 'm': return KEY_M;
    }
    return EOF;
}

void InputState::keyboard_handler(KeyboardEvent e)
{
    if (e.action == KEYBOARD_PRESS) {
        keyboard.key_flags[e.key.code] |= 1;
    } else if (e.action == KEYBOARD_RELEASE) {
        keyboard.key_flags[e.key.code] &= ~1;
    }
}
void InputState::mouse_handler(MouseEvent e)
{
    if (e.action == MOUSE_BUTTON_PRESS) {
        mouse.button_flags[e.button.code] |= 1;
    }
    if (e.action == MOUSE_BUTTON_RELEASE) {
        mouse.button_flags[e.button.code] &= ~1;
    }
}

bool MouseState::down(MouseButtonCode code) const
{
    return (button_flags[code] & 1) != 0;
}
bool KeyboardState::down(KeyboardKeyCode code) const
{
    return (key_flags[code] & 1) != 0;
}
