#include <logic.h>

void handle_event(volatile system_state_t* system_state) {
    switch (system_state->event) {
        case TUMBLER_ON:
            if (system_state->relay_state == OFF) {
                stop_timer();
                start_relay();
                system_state->relay_state = ON_TUMBLER;
            }
        break;
        case TUMBLER_OFF:
            if (system_state->relay_state == ON_TUMBLER) {
                stop_relay();
                system_state->relay_state = OFF;
            }
        break;
        case TIMER_ON:
			if (system_state->relay_state == OFF) {
				start_relay();
				start_timer();
				system_state->relay_state = ON_TIMER;
				system_state->screen_state = WELCOME;
				system_state->music_state = PLAY;
			} else if (system_state->relay_state == ON_TIMER) {
				start_timer();
			}
        break;
        case NONE:
        break;
    }
}

void update_music_state(volatile system_state_t* system_state, volatile menu_settings_t* settings) {
    switch (system_state->music_state) {
        case PLAY:
        	if (settings->melody_state) play_melody(melodies[system_state->melody_number ^= 1], system_state);
		break;
        case IDLE:
		break;
        case STOP:
		break;
    }
}

void update_screen_state(volatile system_state_t* system_state) {
    switch (system_state->screen_state) {
        case WELCOME: screen_message("Welcome"); system_state->screen_state = WAITING_WELCOME;
        break;
        case MENU: main_menu(); system_state->screen_state = WAITING_MENU;
        break;
        case WAITING_MENU:
		break;
        case WAITING_WELCOME:
		break;
    }
}


void logic(volatile menu_settings_t* settings, volatile system_state_t* system_state, volatile button_state_t* buttons) {
	handle_menu(detect_button_press(buttons, system_state));

	if (settings->device_state) {
	    system_state->event = TUMBLER_ON;
	} else if (!settings->device_state && system_state->detected_move) {
		if (is_dark()) system_state->event = TIMER_ON;
	} else {
	    system_state->event = TUMBLER_OFF;
	}
	system_state->detected_move &= 0;

    handle_event(system_state);
    update_music_state(system_state, settings);
    update_screen_state(system_state);
}


