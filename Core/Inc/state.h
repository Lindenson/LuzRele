#ifndef INC_STATE_H_
#define INC_STATE_H_
#include "buttons.h"

typedef struct {
	ButtonID_t last_button;
    int detected_move;
    int small_move;
    int relay_on;
    int melody_number;
    int stop_playing;
    int device_on;
    int welcome_mode;
    uint8_t debounce_flag;
    int time_counter_sec;
} SystemState;

extern volatile SystemState system_state;

#endif /* INC_STATE_H_ */
