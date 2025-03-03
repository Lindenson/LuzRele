#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "stm32f4xx_hal.h"

typedef enum {
    BUTTON_NONE = 0,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_OK,
    BUTTON_CANCEL,
} button_id_t;


typedef struct {
    uint8_t up;
    uint8_t down;
    uint8_t ok;
    uint8_t cancel;
} button_state_t;

extern volatile button_state_t buttons;
extern volatile uint8_t debounce_flag;
extern volatile button_id_t last_button;

#endif
