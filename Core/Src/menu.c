#include <stdio.h>
#include <screen.h>
#include <buttons.h>
#include <menu.h>

volatile menu_settings_t settings = {
    .device_state = 0,
    .timer_duration = 15,
    .melody_state = 0,
    .night_mode_state = 1,
    .night_mode_level = 1
};
volatile int settingsShown = 0;

void action_on()   { settings.device_state = 1;}
void action_off()  { settings.device_state = 0; }
void action_30s()  { settings.timer_duration = 15; }
void action_1m()   { settings.timer_duration = 30; }
void action_2m()   { settings.timer_duration = 60; }
void action_melody_on()  { settings.melody_state = 1; }
void action_melody_off() { settings.melody_state = 0; }
void action_night_on()   { settings.night_mode_state = 1; }
void action_night_off()  { settings.night_mode_state = 0; }
void action_level_5()  { settings.night_mode_level = 1; }
void action_level_10()   { settings.night_mode_level = 4; }
void action_level_30()   { settings.night_mode_level = 10; }
void action_show_options() {settingsShown = 1; showOptions();}

typedef void (*MenuCallback)();

typedef struct MenuItem {
    const char *name;
    struct MenuItem *parent;
    struct MenuItem *next;
    struct MenuItem *prev;
    struct MenuItem *child;
    MenuCallback callback;
} MenuItem;

MenuItem menu_welcome = {"Menu", NULL, NULL, NULL, NULL, NULL};
MenuItem menu_device  = {"Device", &menu_welcome, NULL, NULL, NULL, NULL};
MenuItem menu_timer   = {"Timer", &menu_welcome, NULL, &menu_device, NULL, NULL};
MenuItem menu_melody  = {"Melody", &menu_welcome, NULL, &menu_timer, NULL, NULL};
MenuItem menu_night   = {"Night mode", &menu_welcome, NULL, &menu_melody, NULL, NULL};
MenuItem menu_show_options = {"Options", &menu_welcome, NULL, &menu_night, NULL, action_show_options};

MenuItem menu_device_on  = {"On", &menu_device, NULL, NULL, NULL, action_on};
MenuItem menu_device_off = {"Off", &menu_device, NULL, &menu_device_on, NULL, action_off};

MenuItem menu_timer_30s = {"15s", &menu_timer, NULL, NULL, NULL, action_30s};
MenuItem menu_timer_1m  = {"30s", &menu_timer, NULL, &menu_timer_30s, NULL, action_1m};
MenuItem menu_timer_2m  = {"1m", &menu_timer, NULL, &menu_timer_1m, NULL, action_2m};

MenuItem menu_melody_on  = {"On", &menu_melody, NULL, NULL, NULL, action_melody_on};
MenuItem menu_melody_off = {"Off", &menu_melody, NULL, &menu_melody_on, NULL, action_melody_off};

MenuItem menu_night_on  = {"On", &menu_night, NULL, NULL, NULL, action_night_on};
MenuItem menu_night_off = {"Off", &menu_night, NULL, &menu_night_on, NULL, action_night_off};
MenuItem menu_night_level = {"Level", &menu_night, NULL, &menu_night_off, NULL, NULL};

MenuItem menu_level_5 = {"0.1L", &menu_night_level, NULL, NULL, NULL, action_level_5};
MenuItem menu_level_10 = {"0.5L", &menu_night_level, NULL, &menu_level_5, NULL, action_level_10};
MenuItem menu_level_30 = {"1.0L", &menu_night_level, NULL, &menu_level_10, NULL, action_level_30};


volatile MenuItem *currentMenu = NULL;


void Setup_menu() {
    menu_welcome.child = &menu_device;

    menu_device.next = &menu_timer;
    menu_timer.next = &menu_melody;
    menu_melody.next = &menu_night;
    menu_night.next = &menu_show_options;

    menu_device.child = &menu_device_on;
    menu_device_on.next = &menu_device_off;

    menu_timer.child = &menu_timer_30s;
    menu_timer_30s.next = &menu_timer_1m;
    menu_timer_1m.next = &menu_timer_2m;

    menu_melody.child = &menu_melody_on;
    menu_melody_on.next = &menu_melody_off;

    menu_night.child = &menu_night_on;
    menu_night_on.next = &menu_night_off;
    menu_night_off.next = &menu_night_level;

    menu_night_level.child = &menu_level_5;
    menu_level_5.next = &menu_level_10;
    menu_level_10.next = &menu_level_30;

    currentMenu = &menu_welcome;
    screen_message(currentMenu->name);
}

void handle_button(button_id_t btn) {
	if (!btn) return;

	volatile MenuItem *lastMenu = currentMenu;
	settingsShown = 0;
    switch (btn) {
        case BUTTON_UP:
            if (currentMenu->prev) {
                currentMenu = currentMenu->prev;
            } else {
                while (lastMenu->next) {
                    lastMenu = lastMenu->next;
                }
                currentMenu = lastMenu;
            }
            break;

        case BUTTON_DOWN:
            if (currentMenu->next) {
                currentMenu = currentMenu->next;
            } else {
                while (lastMenu->prev) {
                    lastMenu = lastMenu->prev;
                }
                currentMenu = lastMenu;
            }
            break;

        case BUTTON_OK:
            if (currentMenu->child)
                currentMenu = currentMenu->child;
            else if (currentMenu->callback)
                currentMenu->callback();
            break;

        case BUTTON_CANCEL:
            if (currentMenu->parent)
                currentMenu = currentMenu->parent;
            break;

        case BUTTON_NONE:
            break;
    }
    if (!settingsShown) currentMenuScreen();
}

void currentMenuScreen(){
    screen_message(currentMenu->name);
}

void main_menu(){
	currentMenu = &menu_welcome;
    screen_message(currentMenu->name);
}
