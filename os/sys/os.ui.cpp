#include "os.ui.hpp"

void os::ui::init(void) {
	ui_stack = (ui_state_t*) malloc(sizeof(ui_state_t));

	ui_stack->state = ROOT__STATUS;
	ui_stack->prev_state = NULL_STATE;
	ui_stack->handler = __root;
	ui_stack->parent = NULL;

	input = UI_INPUT_IDLE;
}

void os::ui::update(void) {
	ui_stack->handler(&(ui_stack->state), &(ui_stack->prev_state), &(ui_stack->data));
	first_call = false;
	input = UI_INPUT_IDLE;
}

void os::ui::stepOut(void) { input = UI_STEP_OUT; }
void os::ui::stepPrev(void) { input = UI_STEP_PREV; }
void os::ui::stepNext(void) { input = UI_STEP_NEXT; }
void os::ui::select(void) { input = UI_SELECT; }

void os::ui::spawn_child(uint8_t state, void (*handler)(uint8_t*,uint8_t*,uint16_t*), uint16_t data) {
	ui_state_t* new_iface = (ui_state_t*) malloc(sizeof(ui_state_t));
	new_iface->state = state;
	new_iface->prev_state = NULL_STATE;
	new_iface->data = data;
	new_iface->handler = handler;
	new_iface->parent = ui_stack;
	ui_stack->prev_state = NULL_STATE; // null old interface previous state in order for clean return
	ui_stack = new_iface;
}

void os::ui::esc(void) {
	if (ui_stack) {
		ui_state_t* temp = ui_stack;
		ui_stack = temp->parent;
		free(temp);
	}
}

void os::ui::__root(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[-- light OS --]"));
	}

	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = state[0];
	}

	if (first_call || input) {
		switch (*state) {
			case ROOT__STATUS: // root home screen (select for status)
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-   Status   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to status display
					spawn_child(STATUS__OVERVIEW, __status);
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__ANIM_SELECT;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__SLEEP;
				}
				break;
			case ROOT__ANIM_SELECT: // root animation selection mode
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<- AnimSelect ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to animation selection
					spawn_child(ASEL__FIRST, __anim_select);
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__CONFIG;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__STATUS;
				}
				break;
			case ROOT__CONFIG: // root config mode
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-   Config   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to config
					spawn_child(CONFIG__SYSTEM, __config);
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__SLEEP;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__ANIM_SELECT;
				}
				break;
			case ROOT__SLEEP: // root sleep mode
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-   Sleep    ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to sleep mode
					spawn_child(SLEEP__ON, __sleep);
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__STATUS;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__CONFIG;
				}
				break;
		}
	}
}

void os::ui::__status(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if ((*state) != (*prev) || input) {}
}

void os::ui::__config(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[--- CONFIG ---]"));
	}

	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = *state;
	}

	if (first_call || input) {
		switch (*state) {
			case CONFIG__SYSTEM:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-   System   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to system configuration
					// spawn_child(SLEEP__ON, __sleep);
				} else if ((input & KEYCTRL_KEY_NEXT) || (input & KEYCTRL_KEY_BACK)) {
					// scroll to the next option
					state[0] = CONFIG__STRIP;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
			case CONFIG__STRIP:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-   Strips   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to system configuration
					spawn_child(CONFIG__S_SEL, __config_strip_select);
				} else if ((input & KEYCTRL_KEY_NEXT) || (input & KEYCTRL_KEY_BACK)) {
					// scroll to the next option
					state[0] = CONFIG__SYSTEM;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
		}
	}
}

void os::ui::__config_strip_select(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[ STRIP SELECT ]"));
	}

	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = *state;
	}

	if (first_call || input) {
		switch (*state) {
			case CONFIG__S_SEL:
				if (input & KEYCTRL_KEY_SELECT) {
					// go to system configuration
					spawn_child(CONFIG__S_BRIGHT, __config_brightness, (*data));
				} else if (input & KEYCTRL_KEY_NEXT) {
					// increment strip number
					data[0]++;
					if (data[0] >= os::dev->leds->num_strips)  { data[0] = 0; }
				} else if (input & KEYCTRL_KEY_BACK) {
					// decrement strip number
					if (data[0] == 0)  { data[0] = os::dev->leds->num_strips; }
					data[0]--;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); break; }

				os::display::setCursor(0, 1);

				if (*data < 10) {
					os::display::print(F("<- strip  00"));
				} else if (*data < 100) {
					os::display::print(F("<- strip  0"));
				} else {
					os::display::print(F("<- strip  "));
				}

				os::display::print((int) (*data));
				os::display::print(F(" ->"));

				break;
		}
	}
}

void os::ui::__config_brightness(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[- BRIGHTNESS -]"));
	}

	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = *state;
		uint8_t strip_id = (*data);
		(*data) = strip_id << 8;
		(*data) |= os::dev->leds->strips[strip_id]->getBrightness() & 0x00FF;
	}

	if (first_call || input) {
		switch (*state) {
			case CONFIG__S_BRIGHT:
				if ((input & KEYCTRL_KEY_SELECT) || (input & KEYCTRL_KEY_ESC)) {
					// done
					esc(); break;
				} else if (input & KEYCTRL_KEY_NEXT) {
					// increment brightness
					if ((data[0] & 0xFF) < 255)  { data[0] += 15; }
				} else if (input & KEYCTRL_KEY_BACK) {
					// decrement brightness
					if ((data[0] & 0xFF) > 0)  { data[0] -= 15; }
				}

				os::display::setCursor(0, 1);

				uint8_t num_dots = (data[0] & 0xFF) / 21;
				char* str = (char*) malloc(sizeof(char) * 17);
				str[0] = '-';
				str[1] = ' ';
				str[14] = ' ';
				str[15] = '+';
				str[16] = '\0';

				for (uint8_t i = 2; i < 14; i++) {
					if (i < (num_dots + 2)) {
						str[i] = 'o';
					} else { str[i] = ' '; }
				}

				os::display::print(str);
				free(str);

				os::dev->leds->strips[(*data) >> 8]->setBrightness(data[0]);
				os::dev->leds->strips[(*data) >> 8]->show();

				break;
		}
	}
}

void os::ui::__sleep(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if ((*state) != (*prev) || input) {}
}
