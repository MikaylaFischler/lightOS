void os::led_ctrl::init(void) {
	registry_head = NULL;
	registry_tail = NULL;

	cur_run = 0;
	for (int i = 0; i < os::dev->leds->num_strips; i++) { running[i] = 0 }
}

void os::led_ctrl::run(uint8_t anim_id) {
	RegisteredAnimation* entry = search_registry(anim_id, registry_head);

	// if the animation was found
	if (entry) {
		// add the animation to the running list
		for (int i = 0; i < entry->num_strips; i++) {
			running[entry->strip_req[i] - 1] = entry;
		}
	}
}

void os::led_ctrl::update(void) {
	RegisteredAnimation* current = runnung[cur_run];
	current->anim(os::dev->leds->strips[cur_run]);

	if (++cur_run > os::dev->leds->num_strips) { cur_run = 0; }
}

void os::led_ctrl::registerAnimation(void (*anim)(Adafruit_NeoPixel**), uint8_t anim_id, uint8_t num_strips, uint8_t* strip_req) {
	RegisteredAnimation* reg = malloc(sizeof(RegisteredAnimation));

	reg->id = anim_id;
	reg->num_strips = num_strips;
	reg->strip_req = strip_req;
	reg->anim = anim;

	if (registry_head) {
		registry_tail->next = reg;
		registry_tail = reg;
	} else {
		registry_head = registry_tail = reg;
	}
}

RegisteredAnimation* os::led_ctrl::getAnimationList(void) { return registry_head; }

RegisteredAnimation* os::led_ctrl::search_registry(uint8_t id, RegisteredAnimation* entry) {
	if (entry) {
		if (entry->id == id) { return entry; }
		return search_registry(id, entry->next);
	} else { return NULL; }
}
