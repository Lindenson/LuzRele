#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "buttons.h"

typedef struct {
    int device_state;
    int timer_duration;
    int melody_state;
    int night_mode_state;
    int night_mode_level;
} menu_settings_t;

extern volatile menu_settings_t settings;

void Setup_menu();
void handle_button(button_id_t btn);
void currentMenuScreen();
void main_menu();

#endif /* INC_MENU_H_ */
