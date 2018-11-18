#include "animations.h"
#include "colors.h"

void anim__white(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_WHITE);
}

void anim__soft_white(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_DIM_OFF_WHITE);
}

void anim__red(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_RED);
}

void anim__orn(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_ORANGE);
}

void anim__ylw(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_YELLOW);
}

void anim__grn(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_GREEN);
}

void anim__blu(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_BLUE);
}

void anim__prp(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_PURPLE);
}

void anim__pnk(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__color(strip, data, COLOR_PINK);
}

void _anim__color(Adafruit_NeoPixel* strip, AnimationData* data, uint32_t color) {
	// on initial case or overflow, update pixels
	if (data->counter == 0) {
		for (uint16_t i = 0; i < strip->numPixels(); i++) {
			strip->setPixelColor(i, color);
		}

		data->sys_flag |= FLAG_REQ_SHOW;
	}

	data->counter++;
}
