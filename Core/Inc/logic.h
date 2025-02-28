#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_

void stop_timer();
void start_timer();
void start_relay();
void stop_relay();
void start_melody();
void logic(volatile MenuSettings * settings, volatile SystemState *system_state, volatile ButtonState_t *buttons);

#endif /* INC_LOGIC_H_ */
