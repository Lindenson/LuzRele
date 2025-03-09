#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_


#include <menu.h>
#include <screen.h>
#include <state.h>
#include <buttons.h>
#include <songs.h>
#include <melody.h>
#include <button_handler.h>

extern void stop_timer();
extern void start_timer();
extern void start_relay();
extern void stop_relay();
extern void stop_melody();
extern int is_dark();

#define MENU_TIMEOUT_SEC 3

void event_logic(volatile menu_settings_t* settings, volatile system_state_t* system_state, volatile button_state_t* buttons);
void stop_timed_relay(volatile system_state_t* system_state);
void return_to_menu_after_delay(volatile system_state_t* system_state);

#endif /* INC_LOGIC_H_ */
