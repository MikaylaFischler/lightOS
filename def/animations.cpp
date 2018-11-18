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

/*!
	@brief Produces Red component of 32-bit RGB
	@param color 32-bit RGB color
	@return the Red component (8-bit) of a 32-bit color
*/
uint8_t redFromColor(uint32_t color) {
    return (color >> 16) & 0xFF;
}

/*!
	@brief Produces Green component of 32-bit RGB
	@param color 32-bit RGB color
	@return the Green component (8-bit) of a 32-bit color
*/
uint8_t greenFromColor(uint32_t color) {
    return (color >> 8) & 0xFF;
}

/*!
	@brief Produces Blue component of 32-bit RGB
	@param color 32-bit RGB color
	@return the Blue component (8-bit) of a 32-bit color
*/
uint8_t blueFromColor(uint32_t color) {
    return color & 0xFF;
}
