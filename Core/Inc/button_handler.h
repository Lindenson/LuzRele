#ifndef INC_BUTTONS_HANDLER_H_
#define INC_BUTTONS_HANDLER_H_
#include <buttons.h>
#include <state.h>

button_id_t detect_button_press(volatile button_state_t* buttons, volatile system_state_t* system_state);
void clean_debounce_flags(volatile system_state_t* system_state);

#endif
