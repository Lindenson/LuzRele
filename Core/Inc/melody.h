#ifndef MELODY_H
#define MELODY_H

#include "stdint.h"
#include "math.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

#define TIMER_CLOCK 84000000U
#define PRESCALER 999U

typedef enum {
	FREQ_C = 261,
	FREQ_CS = 277,
	FREQ_D = 294,
	FREQ_DS = 311,
	FREQ_E = 330,
	FREQ_F = 349,
	FREQ_G = 392,
	FREQ_GS = 415,
	FREQ_A = 440,
	FREQ_Bb = 466,
	FREQ_B = 493,
	FREQ_Z = 0  // Пауза
} NoteFrequency;

typedef struct {
	uint16_t frequency;
	uint16_t duration;
} Note;

typedef struct {
	const Note *notes;
	const char *name;
	const int length;
} Melody;

void Sound_init();
void play_melody(Melody melody);
void stop_playing();

#endif // MELODY_H
