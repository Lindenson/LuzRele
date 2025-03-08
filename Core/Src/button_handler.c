#include <button_handler.h>

button_id_t detect_button_press(volatile button_state_t* buttons, volatile system_state_t* system_state) {
    struct {
    	volatile uint8_t* button;
        button_id_t id;
    } button_map[] = {
		{ &buttons->cancel, BUTTON_CANCEL },
        { &buttons->up, BUTTON_UP },
        { &buttons->down, BUTTON_DOWN },
        { &buttons->ok, BUTTON_OK },
    };

    for (int i = 0; i < sizeof(button_map) / sizeof(button_map[0]); i++) {
        if (*button_map[i].button) {
            system_state->screen_state = WAITING_MENU;
            return button_map[i].id;
        }
        *button_map[i].button = 0;
    }
    return BUTTON_NONE;
}
