#include <screen.h>

void screen_message(const char *message) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(15, 10);
	ssd1306_WriteString((char *)message, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void screen_small_messages(message_item *items, size_t count) {
	ssd1306_Fill(Black);
	for (int i = 0; i < count; i++) {
		ssd1306_SetCursor(items[i].x, items[i].y);
		ssd1306_WriteString(items[i].text, Font_6x8, White);
	}
    ssd1306_UpdateScreen();
}

void draw_waveform(uint16_t freq, char *name, uint8_t phase) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(name, Font_11x18, White);

	for (int x = 0; x < 128; x++) {
		int y = 50 + (int) (12 * sin((x + phase) * freq * 0.0005));
		ssd1306_DrawPixel(x, y, White);
	}
	ssd1306_UpdateScreen();
}


