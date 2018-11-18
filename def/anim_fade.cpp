#include "animations.h"
#include "colors.h"

void anim__white_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_WHITE);
}

void anim__soft_white_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_DIM_OFF_WHITE);
}

void anim__red_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_RED);
}

void anim__orn_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_ORANGE);
}

void anim__ylw_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_YELLOW);
}

void anim__grn_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_GREEN);
}

void anim__blu_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_BLUE);
}

void anim__prp_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_PURPLE);
}

void anim__pnk_fade(Adafruit_NeoPixel* strip, AnimationData* data) {
	_anim__fade(strip, data, COLOR_PINK);
}

void _anim__fade(Adafruit_NeoPixel* strip, AnimationData* data, uint32_t color) {
	// on initial case or overflow, update pixels
	if (data->i == 255) {
		if (data->i == 0) { data->j = 25; }
		data->i = 1;

		if (data->j == 255) {
			data->l_flag &= ~0x1;
		} else if (data->j == 25) {
			data->l_flag |= 0x1;
		}

		if (data->l_flag & 0x1) {
			data->j++;
		} else {
			data->j--;
		}

		for (uint16_t i = 0; i < strip->numPixels(); i++) {
			strip->setPixelColor(i, (uint16_t) redFromColor(color) * data->j / 255,
									(uint16_t) greenFromColor(color) * data->j / 255,
									(uint16_t) blueFromColor(color) * data->j / 255);
		}

		data->sys_flag |= FLAG_REQ_SHOW;
	}

	data->i++;
}
