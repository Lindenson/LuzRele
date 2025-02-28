#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "buttons.h"

typedef struct {
    int device_state;
    int timer_duration;
    int melody_state;
    int night_mode_state;
    int night_mode_level;
} MenuSettings;

extern volatile MenuSettings settings;

void handle_button(ButtonID_t btn);
void Setup_menu();
void currentMenuScreen();

#endif /* INC_MENU_H_ */
