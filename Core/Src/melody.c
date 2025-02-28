#include "main.h"
#include "melody.h"
#include "songs.h"
#include "state.h"


extern TIM_HandleTypeDef htim2;
volatile uint8_t phase;

static inline uint16_t get_ARR(uint16_t freq) {
	return (TIMER_CLOCK / (PRESCALER + 1)) / freq - 1;
}

void draw_waveform(uint16_t freq, char *name) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(name, Font_11x18, White);

	for (int x = 0; x < 128; x++) {
		int y = 50 + (int) (12 * sin((x + phase) * freq * 0.0005));
		ssd1306_DrawPixel(x, y, White);
	}
	ssd1306_UpdateScreen();
}

void play_note(uint16_t freq, uint16_t duration, const char *name, int withWave) {
	if (freq > 0) {
		uint16_t arr = get_ARR(freq);
		__HAL_TIM_SET_AUTORELOAD(&htim2, arr);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr / 2);
	} else {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	}
	if (withWave) draw_waveform(freq, (char*) name);
	phase += duration / 8;
	HAL_Delay(duration);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	HAL_Delay(100);
}

void Sound_init() {
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = PRESCALER;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = get_ARR(FREQ_Z);
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&htim2);

	TIM_OC_InitTypeDef sConfigOC = { 0 };
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = htim2.Init.Period / 2;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	play_note(FREQ_Z, 10, "", 0);
}


void play_melody(Melody melody) {
    system_state.stop_playing = 0;
    for (size_t i = 0; i < melody.length; i++) {
        if (system_state.stop_playing) {
            stop_playing();
            return;
        }
        play_note(melody.notes[i].frequency, melody.notes[i].duration, melody.name, i > 0);
    }
}

void stop_playing() {
    system_state.stop_playing = 1;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
}
