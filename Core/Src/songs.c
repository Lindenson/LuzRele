#include "songs.h"

const Note yesterday[] = { { FREQ_Z, 500 }, { FREQ_G, 500 }, { FREQ_F, 250 }, { FREQ_F, 500 },
	{ FREQ_Z, 250 }, { FREQ_A, 175 }, { FREQ_B, 175 }, { FREQ_CS, 175 },
	{ FREQ_D, 175 }, { FREQ_E, 175 }, { FREQ_F, 175 }, { FREQ_E, 250 },
	{ FREQ_D, 250 }, { FREQ_D, 500 }, { FREQ_Z, 250 }, { FREQ_D, 175 },
	{ FREQ_D, 175 }, { FREQ_C, 175 }, { FREQ_Bb, 175 }, { FREQ_A, 175 },
	{ FREQ_G, 175 }, { FREQ_Bb, 250 }, { FREQ_A, 250 }, { FREQ_A, 250 },
	{ FREQ_Z, 500 }, { FREQ_G, 250 }, { FREQ_F, 250 }, { FREQ_A, 250 },
	{ FREQ_G, 500 }, { FREQ_D, 175 }, { FREQ_F, 350 }, { FREQ_A, 250 },
	{ FREQ_A, 500 }, { FREQ_Z, 500 } };

const Note sweet_dreams[] = { { FREQ_Z, 500 }, { FREQ_F, 200 }, { FREQ_F, 250 }, { FREQ_D, 200 },
	{ FREQ_F, 200 }, { FREQ_F, 200 }, { FREQ_F, 90 }, { FREQ_E, 150 },
	{ FREQ_Z, 300 }, { FREQ_F, 180 }, { FREQ_F, 90 }, { FREQ_D, 90 },
	{ FREQ_F, 200 }, { FREQ_D, 200 }, { FREQ_F, 220 }, { FREQ_G, 200 },
	{ FREQ_F, 90 }, { FREQ_E, 220 }, { FREQ_Z, 200 }, { FREQ_E, 180 },
	{ FREQ_F, 200 }, { FREQ_F, 80 }, { FREQ_D, 120 }, { FREQ_F, 170 },
	{ FREQ_F, 80 }, { FREQ_D, 80 }, { FREQ_F, 170 }, { FREQ_G, 200 },
	{ FREQ_F, 100 }, { FREQ_E, 100 }, { FREQ_Z, 250 }, { FREQ_F, 200 },
	{ FREQ_D, 200 }, { FREQ_F, 200 }, { FREQ_D, 200 },
	{ FREQ_F, 200 }, { FREQ_F, 120 }, { FREQ_G, 70 }, { FREQ_E, 40 },
	{ FREQ_E, 340 }, { FREQ_Z, 2000 } };

#define YESTERDAY_LENGTH (sizeof(yesterday) / sizeof(yesterday[0]))
#define SWEET_DREAMS_LENGTH (sizeof(sweet_dreams) / sizeof(sweet_dreams[0]))

const Melody melody_yesterday = { yesterday, " Yesterday!", YESTERDAY_LENGTH };
const Melody melody_sweet_dreams = { sweet_dreams, "SweetDreams", SWEET_DREAMS_LENGTH };

const Melody melodies[] = { melody_sweet_dreams, melody_yesterday };
