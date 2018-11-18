#include "os.led_ctrl.hpp"

void os::led_ctrl::init(void) {
	registry_head = NULL;
	registry_tail = NULL;
	anim_count = 0;

	cur_run = 0;
	for (int i = 0; i < os::dev->leds->num_strips; i++) {
		data[i] = (AnimationData*) calloc(sizeof(AnimationData), 1);
		running[i] = NULL;
	}
}

void os::led_ctrl::run(uint8_t anim_id, uint8_t strip_id) {
	if (strip_id > ID_STRIP_NULL) {
		RegisteredAnimation* entry = search_registry(anim_id, registry_head);

		// if the animation was found
		if (entry) {
			// add the animation to the running list
			running[strip_id - 1] = entry;
		}
	}
}

void os::led_ctrl::update(void) {
	RegisteredAnimation* current = running[cur_run];
	if (current) { current->anim(os::dev->leds->strips[cur_run], data[cur_run]); }

	if (data[cur_run]->sys_flag & FLAG_REQ_SHOW) {
		os::dev->leds->strips[cur_run]->show();
		data[cur_run]->sys_flag &= ~FLAG_REQ_SHOW;
	}

	if (++cur_run >= os::dev->leds->num_strips) { cur_run = 0; }
}

void os::led_ctrl::registerAnimation(void (*anim)(Adafruit_NeoPixel*, AnimationData*), uint8_t anim_id, const __FlashStringHelper* name) {
	anim_count++;
	RegisteredAnimation* reg = (RegisteredAnimation*) malloc(sizeof(RegisteredAnimation));

	reg->id = anim_id;
	reg->name = name;
	reg->anim = anim;

	if (registry_head) {
		registry_tail->next = reg;
		registry_tail = reg;
	} else {
		registry_head = registry_tail = reg;
	}
}

os::led_ctrl::RegisteredAnimation* os::led_ctrl::getAnimationList(void) { return registry_head; }

uint8_t os::led_ctrl::getAnimationCount(void) { return anim_count; }

os::led_ctrl::RegisteredAnimation* os::led_ctrl::search_registry(uint8_t id, RegisteredAnimation* entry) {
	if (entry) {
		if (entry->id == id) { return entry; }
		return search_registry(id, entry->next);
	} else { return NULL; }
}
