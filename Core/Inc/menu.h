#ifndef INC_MENU_H_
#define INC_MENU_H_

#include <stdio.h>
#include <screen.h>
#include <buttons.h>

typedef struct {
    int device_state;
    int timer_duration;
    int melody_state;
    int night_mode_state;
    int night_mode_level;
} menu_settings_t;

void setup_menu();
void handle_menu(button_id_t btn);
void currentMenuScreen();
void main_menu();

#endif /* INC_MENU_H_ */
