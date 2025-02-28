#include "menu.h"
#include "buttons.h"
#include "state.h"
#include "screen.h"
#include "logic.h"

extern void stop_timer();
extern void start_timer();
extern void start_relay();
extern void stop_relay();
extern void start_melody();
extern void start_timed_relay();


void logic(volatile MenuSettings * settings, volatile SystemState *state, volatile ButtonState_t *buttons) {

	if (settings->device_state) {
		stop_timer();
		start_relay();
		state->device_on = 1;

	} else if (state->detected_move) {
		start_timer();
		state->detected_move = 0;
		start_timed_relay();

	} else if (state->device_on) {
		stop_relay();
		state->device_on = 0;
	}

	if (buttons->up) {
		handle_button(BUTTON_UP);
		buttons->up = 0;
	}
	if (buttons->down) {
		handle_button(BUTTON_DOWN);
		buttons->down = 0;
	}
	if (buttons->ok) {
		handle_button(BUTTON_OK);
		buttons->ok = 0;
	}
	if (buttons->cancel) {
		handle_button(BUTTON_CANCEL);
		buttons->cancel = 0;
	}
}
