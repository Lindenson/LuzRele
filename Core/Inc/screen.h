
#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include <ssd1306.h>
#include <ssd1306_fonts.h>
#include <menu.h>
#include <stdio.h>
#include <math.h>

typedef struct {
	char text[32];
	int x;
	int y;
} message_item;

void screen_message(const char *message);
void screen_small_messages(message_item *items, size_t count);
void draw_waveform(uint16_t freq, char *name, uint8_t phase);

#endif /* INC_SCREEN_H_ */
