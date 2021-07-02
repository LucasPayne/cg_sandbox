
void check_quit_key(KeyboardEvent e, KeyboardKeyCode keycode)
{
    if (e.action == KEYBOARD_PRESS) {
        if (e.key.code == keycode) {
            exit(EXIT_SUCCESS);
        }
    }
}
