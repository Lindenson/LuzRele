#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_

void stop_timer();
void start_timer();
void start_relay();
void stop_relay();
void start_melody();
void logic(volatile menu_settings_t* settings, volatile system_state_t* system_state, volatile button_state_t* buttons);

#endif /* INC_LOGIC_H_ */
