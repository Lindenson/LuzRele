#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "stm32f4xx_hal.h"

typedef enum {
    BUTTON_NONE = 0,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_OK,
    BUTTON_CANCEL,
} ButtonID_t;


typedef struct {
    uint8_t up;
    uint8_t down;
    uint8_t ok;
    uint8_t cancel;
} ButtonState_t;

extern volatile ButtonState_t buttons;
extern volatile uint8_t debounce_flag;
extern volatile ButtonID_t last_button;

#endif
