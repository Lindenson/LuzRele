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
    button_id_t detected = BUTTON_NONE;
    for (int i = 0; i < sizeof(button_map) / sizeof(button_map[0]); i++) {
        if (*button_map[i].button) {
            system_state->screen_state = MENU;
            detected = button_map[i].id;
        }
        *button_map[i].button = 0;
    }
    return detected;
}

void clean_debounce_flags(volatile system_state_t* system_state){
	system_state->last_button = BUTTON_NONE;
	system_state->small_move = 0;
	system_state->debounce_flag = 0;
}
