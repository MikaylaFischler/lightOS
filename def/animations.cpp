#include "animations.h"

uint32_t _anim__clr_cycle(uint8_t state) {
	state = 255 - state;
	if (state < 85) {
		return color(255 - state * 3, 0, state * 3);
	} else if (state < 170) {
		state -= 85;
		return color(0, state * 3, 255 - state * 3);
	} else {
		state -= 170;
		return color(state * 3, 255 - state * 3, 0);
	}
}

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint32_t) r << 16) | ((uint32_t) g <<  8) | b;
}
