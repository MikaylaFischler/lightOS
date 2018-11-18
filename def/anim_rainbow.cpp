#include "animations.h"

void anim__rainbow(Adafruit_NeoPixel* strip, AnimationData* data) {
	// on initial case or 1001, update pixels
	if (data->counter == 1001 || data->counter == 0) {
		data->counter = 1;

		for (uint16_t i = 0; i < strip->numPixels(); i++) {
			strip->setPixelColor(i, _anim__clr_cycle(data->j));
		}

		data->j++;

		data->sys_flag |= FLAG_REQ_SHOW;
	}

	data->counter++;
}

void anim__rainbow_flow(Adafruit_NeoPixel* strip, AnimationData* data) {
	// on initial case or 1001, update pixels
	if (data->counter == 1001 || data->counter == 0) {
		data->counter = 1;

		for (uint16_t i = 0; i < strip->numPixels(); i++) {
			strip->setPixelColor(i, _anim__clr_cycle((i + data->j) & 255));
		}

		data->j++;

		data->sys_flag |= FLAG_REQ_SHOW;
	}

	data->counter++;
}
