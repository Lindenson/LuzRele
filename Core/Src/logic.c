#include <logic.h>

void handle_event(event_t event, volatile system_state_t* system_state) {
    switch (event) {
        case TUMBLER_ON:
            if (system_state->relay_state == OFF) {
                stop_timer();
                start_relay();
                system_state->relay_state = ON_TUMBLER;
            }
        break;
        case TURNED_OFF:
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
				system_state->screen_state = TO_WELCOME;
				system_state->music_state = PLAY;
			} else if (system_state->relay_state == ON_TIMER) {
				start_timer();
			}
        break;
    }
}

void update_music_state(volatile system_state_t* system_state, volatile menu_settings_t* settings) {
    switch (system_state->music_state) {
        case PLAY:
        	if (settings->melody_state) {
				uint8_t melody_index = system_state->melody_number ^ 1;
				system_state->melody_number = melody_index;
				play_melody(melodies[melody_index], system_state);
        	}
        break;
        case IDLE:
        case STOP:
        break;
    }
}

void update_screen_state(volatile system_state_t* system_state) {
    switch (system_state->screen_state) {
        case TO_WELCOME: screen_message("Welcome!"); system_state->screen_state = WELCOME;
        break;
        case TO_MENU: main_menu(); system_state->screen_state = MENU;
        break;
        case MENU:
        case WELCOME:
        break;
    }
}


void event_logic(volatile menu_settings_t* settings, volatile system_state_t* system_state, volatile button_state_t* buttons) {
	handle_menu(detect_button_press(buttons, system_state));

	event_t event = settings->device_state? TUMBLER_ON : TURNED_OFF;
	if (!event && is_dark() && system_state->detected_move) event = TIMER_ON;
	system_state->detected_move &= ~1;

    handle_event(event, system_state);
    update_music_state(system_state, settings);
    update_screen_state(system_state);
}


//from INTERRUPTS
void stop_timed_relay(volatile system_state_t* system_state) {
	system_state->time_counter_sec = 0;
	system_state->relay_state = ON_TUMBLER;
}


void return_to_menu_after_delay(volatile system_state_t* system_state) {
	if (system_state->menu_update_counter++ < MENU_TIMEOUT_SEC) return;
	system_state->menu_update_counter = 0;
	if (system_state->screen_state == WELCOME) system_state->screen_state = TO_MENU;
}
