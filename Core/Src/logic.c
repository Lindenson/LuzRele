#include "menu.h"
#include "buttons.h"
#include "state.h"
#include "screen.h"
#include "melody.h"
#include "songs.h"
#include "logic.h"

extern void stop_timer();
extern void start_timer();
extern void start_relay();
extern void stop_relay();
extern void stop_melody();


void handle_event(SystemState system_state) {
    switch (system_state.event) {
        case TUMBLER_ON:
            if (system_state.relay_state == OFF) {
                system_state.relay_state = ON_TUMBLER;
                stop_timer();
                start_relay();
            }
        break;
        case TUMBLER_OFF:
            if (system_state.relay_state != OFF) {
                system_state.relay_state = OFF;
                if (system_state.relay_state == ON_TIMER) stop_timer();
                stop_relay();
            }
        break;
        case TIMER_ON:
            if (system_state.relay_state == OFF) {
                system_state.relay_state = ON_TIMER;
                system_state.screen_state = WELCOME;
                system_state.music_state = PLAY;
                start_relay();
                start_timer();
            } else if (system_state.relay_state == ON_TIMER) {
                start_timer();
            }
        break;
        case NONE:
        break;
    }
}

void update_music_state(SystemState system_state) {
    switch (system_state.music_state) {
        case PLAY:
        	if (settings.melody_state) play_melody(melodies[system_state.melody_number ^= 1], system_state);
        	system_state.music_state = IN_PROCESS;
        	break;
        case IN_PROCESS: break;
        case STOP: break;
    }
}

void update_screen_state(SystemState system_state) {
    switch (system_state.screen_state) {
        case WELCOME: screenMessage("Welcome"); system_state.screen_state = WAITING; break;
        case MENU: currentMenuScreen(); system_state.screen_state = WAITING; break;
        case WAITING: break;
    }
}



void logic(volatile MenuSettings settings, volatile SystemState system_state, volatile ButtonState_t buttons) {

	if (settings.device_state) {
		system_state.event = TUMBLER_ON;
	}
	else if (system_state.detected_move) {
		system_state.event = TIMER_ON;
	}
	else {
		system_state.event = TUMBLER_OFF;
	}

	if (buttons.up) {
		handle_button(BUTTON_UP);
		buttons.up = 0;
	}
	if (buttons.down) {
		handle_button(BUTTON_DOWN);
		buttons.down = 0;
	}
	if (buttons.ok) {
		handle_button(BUTTON_OK);
		buttons.ok = 0;
	}
	if (buttons.cancel) {
		handle_button(BUTTON_CANCEL);
		buttons.cancel = 0;
	}

	handle_event(system_state);
	update_music_state(system_state);
	update_screen_state(system_state);
}
