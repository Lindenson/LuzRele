#ifndef INC_STATE_H_
#define INC_STATE_H_
#include <buttons.h>


typedef enum {
	NONE = 0,
    TIMER_ON,
    TUMBLER_OFF,
    TUMBLER_ON,
} event_t;

typedef enum {
	OFF = 0,
    ON_TIMER,
    ON_TUMBLER,
} relay_state_t;

typedef enum {
	IDLE  = 0,
	STOP,
    PLAY,
} music_state_t;

typedef enum {
	MENU = 0,
    WAITING_MENU,
    WELCOME,
	WAITING_WELCOME,
} screen_state_t;

typedef struct {
    button_id_t last_button;
    unsigned int detected_move;
    unsigned int small_move;
    uint8_t debounce_flag;

    unsigned int time_counter_sec;
    unsigned int melody_number;
    unsigned int menu_update_counter;

    event_t event;
    relay_state_t relay_state;
    music_state_t music_state;
    screen_state_t screen_state;
} system_state_t;

#endif /* INC_STATE_H_ */
