
#include "screen.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "menu.h"
#include <stdio.h>

void screenMessage(const char *message) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(15, 10);
	ssd1306_WriteString((char *)message, Font_11x18, White);
	ssd1306_UpdateScreen();
}


void showOptions() {
	char buffer[128];
	snprintf(buffer, sizeof(buffer),
        "Dev: %s Tmr: %d",
        settings.device_state ? "On" : "Off",
        settings.timer_duration);

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(buffer, Font_6x8, White);

    snprintf(buffer, sizeof(buffer),
        "Mel: %s Night: %s",
        settings.melody_state ? "On" : "Off",
        settings.night_mode_state ? "On" : "Off");

    ssd1306_SetCursor(0, 22);
    ssd1306_WriteString(buffer, Font_6x8, White);

    snprintf(buffer, sizeof(buffer),
        "Lv: %d%%", settings.night_mode_level);

    ssd1306_SetCursor(0, 44);
    ssd1306_WriteString(buffer, Font_6x8, White);
    ssd1306_UpdateScreen();
}


