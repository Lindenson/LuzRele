#include <buttons.h>
#include <melody.h>
#include <menu.h>
#include <screen.h>
#include <songs.h>
#include <state.h>
#include "logic.h"

extern void stop_timer();
extern void start_timer();
extern void start_relay();
extern void stop_relay();
extern void stop_melody();
extern int is_dark();


void handle_event(volatile system_state_t* system_state) {
    switch (system_state->event) {
        case TUMBLER_ON:
            if (system_state->relay_state == OFF) {
                system_state->relay_state = ON_TUMBLER;
                stop_timer();
                start_relay();
            }
        break;
        case TUMBLER_OFF:
            if (system_state->relay_state == ON_TUMBLER) {
                system_state->relay_state = OFF;
                stop_relay();
            }
        break;
        case TIMER_ON:
			if (system_state->relay_state == OFF) {
				system_state->relay_state = ON_TIMER;
				system_state->screen_state = WELCOME;
				system_state->music_state = PLAY;
				start_relay();
				start_timer();
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
        	system_state->music_state = IN_PROCESS;
        	break;
        case IN_PROCESS: break;
        case STOP: break;
    }
}

void update_screen_state(volatile system_state_t* system_state) {
    switch (system_state->screen_state) {
        case WELCOME: screen_message("Welcome"); system_state->screen_state = WAITING; break;
        case MENU: main_menu(); system_state->screen_state = WAITING; break;
        case WAITING: break;
    }
}

button_id_t detect_button_press(volatile button_state_t* buttons) {
    if (buttons->up) {
        buttons->up = 0;
        return BUTTON_UP;
    }
    if (buttons->down) {
        buttons->down = 0;
        return BUTTON_DOWN;
    }
    if (buttons->ok) {
        buttons->ok = 0;
        return BUTTON_OK;
    }
    if (buttons->cancel) {
        buttons->cancel = 0;
        return BUTTON_CANCEL;
    }
    return BUTTON_NONE;
}


void logic(volatile menu_settings_t* settings, volatile system_state_t* system_state, volatile button_state_t* buttons) {
	handle_button(detect_button_press(buttons));

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


