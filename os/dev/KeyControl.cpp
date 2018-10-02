#include "KeyControl.hpp"

volatile uint8_t KeyControl::key_state_mask = 0;
uint8_t* KeyControl::keys = NULL;

void KeyControl::init(void) {
	keys = (uint8_t*) malloc(sizeof(uint8_t) * KEYCTRL_NUM_KEYS);
	for (int i = 0; i < KEYCTRL_NUM_KEYS; i++) { keys[i] = 255; }
}

uint8_t KeyControl::attachKey(uint8_t key_type, uint8_t key_port) {
	// range safety
	if (key_type >= KEYCTRL_NUM_KEYS) { return 1; }

	// set the pin to input pullup
	pinMode(key_port, INPUT_PULLUP);

	// was this type already assigned?
	if (keys[key_type] != 255) { detachInterrupt(keys[key_type]); }

	// get interrupt number and attach interrupt
	uint32_t __interrupt = digitalPinToInterrupt(key_port);

	// did we already use this?
	for (int i = 0; i < KEYCTRL_NUM_KEYS; i++) { if (keys[i] == __interrupt) { return 2; } }

	// set up the interrupt service routine
	switch (key_type) {
		case KEYCTRL_KEYTYPE_ESC:
			attachInterrupt(__interrupt, KeyControl::__key_esc_isr, FALLING);
			break;
		case KEYCTRL_KEYTYPE_BACK:
			attachInterrupt(__interrupt, KeyControl::__key_back_isr, FALLING);
			break;
		case KEYCTRL_KEYTYPE_SELECT:
			attachInterrupt(__interrupt, KeyControl::__key_sel_isr, FALLING);
			break;
		case KEYCTRL_KEYTYPE_NEXT:
			attachInterrupt(__interrupt, KeyControl::__key_next_isr, FALLING);
			break;
	}

	keys[key_type] = __interrupt;
	return 0;
}

uint8_t KeyControl::getKeyState(void) { return key_state_mask & 0x0F; }
uint8_t KeyControl::getLastKeyState(void) { return (key_state_mask & 0xF0) >> 4; }

void KeyControl::__key_esc_isr(void) {
	key_state_mask <<= 4;
	key_state_mask |= KEYCTRL_KEY_ESC;
}

void KeyControl::__key_back_isr(void) {
	key_state_mask <<= 4;
	key_state_mask |= KEYCTRL_KEY_BACK;
}

void KeyControl::__key_sel_isr(void) {
	key_state_mask <<= 4;
	key_state_mask |= KEYCTRL_KEY_SELECT;
}

void KeyControl::__key_next_isr(void) {
	key_state_mask <<= 4;
	key_state_mask |= KEYCTRL_KEY_NEXT;
}
