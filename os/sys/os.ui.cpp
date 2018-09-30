#include "os.ui.hpp"

void os::ui::init(void) {
	ui_stack = (ui_state_t*) malloc(sizeof(ui_state_t));

	ui_stack->state = ROOT__STATUS;
	ui_stack->prev_state = NULL_STATE;
	ui_stack->handler = __root;
	ui_stack->parent = NULL;

	input = UI_INPUT_IDLE;
}

void os::ui::update(void) { ui_stack->handler(&(ui_stack->state), &(ui_stack->prev_state)); }

void os::ui::stepOut(void) { step(UI_STEP_OUT); }
void os::ui::stepPrev(void) { step(UI_STEP_PREV); }
void os::ui::stepNext(void) { step(UI_STEP_NEXT); }
void os::ui::select(void) { step(UI_SELECT); }

void os::ui::step(uint8_t command) {
	input = command;
	update();
	input = UI_INPUT_IDLE;
}

void os::ui::spawn_child(uint8_t state, void (*handler)(uint8_t*,uint8_t*)) {
	ui_state_t* new_iface = (ui_state_t*) malloc(sizeof(ui_state_t));
	new_iface->state = state;
	new_iface->prev_state = NULL_STATE;
	new_iface->handler = handler;
	new_iface->parent = ui_stack;
	ui_stack = new_iface;
}

void os::ui::__root(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {
		switch (*state) {
			case ROOT__STATUS: // root home screen (select for status)
				os::display::clear();
				os::display::print(F("--- light OS ---"));
				os::display::setCursor(1, 0);
				os::display::print(F("<-  Status  ->"));

				if (input & KEYCTRL_KEY_SELECT) {
					// go to status display
					ui_state_t* status = (ui_state_t*) malloc(sizeof(ui_state_t));
					status->state = STATUS__OVERVIEW;
					status->prev_state = NULL_STATE;
					status->handler = __status;
					status->parent = ui_stack;
					ui_stack = status;
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__ANIM_SELECT;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__SLEEP;
				}
				break;
			case ROOT__ANIM_SELECT: // root animation selection mode
				os::display::setCursor(1, 0);
				os::display::print(F("<- AnimSelect ->"));

				if (input & KEYCTRL_KEY_SELECT) {
					// go to animation selection
					ui_state_t* anim_select = (ui_state_t*) malloc(sizeof(ui_state_t));
					anim_select->state = ASEL__FIRST;
					anim_select->prev_state = NULL_STATE;
					anim_select->handler = __anim_select;
					anim_select->parent = ui_stack;
					ui_stack = anim_select;
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__CONFIG;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__STATUS;
				}
				break;
			case ROOT__CONFIG: // root config mode
				os::display::setCursor(1, 0);
				os::display::print(F("<-   Config   ->"));

				if (input & KEYCTRL_KEY_SELECT) {
					// go to config
					ui_state_t* config = (ui_state_t*) malloc(sizeof(ui_state_t));
					config->state = CONFIG__BRIGHTNESS;
					config->prev_state = NULL_STATE;
					config->handler = __config;
					config->parent = ui_stack;
					ui_stack = config;
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ROOT__SLEEP;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the previous option
					state[0] = ROOT__ANIM_SELECT;
				}
				break;
			case ROOT__SLEEP: // root sleep mode
				os::display::setCursor(1, 0);
				os::display::print(F("<-   Sleep    ->"));

				if (input & KEYCTRL_KEY_SELECT) {
					// go to sleep mode
					ui_state_t* sleep = (ui_state_t*) malloc(sizeof(ui_state_t));
					sleep->state =SLEEP__ON;
					sleep->prev_state = NULL_STATE;
					sleep->handler = __sleep;
					sleep->parent = ui_stack;
					ui_stack = sleep;
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

void os::ui::__status(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {}
}

void os::ui::__anim_select(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {}
}

void os::ui::__anim_strip_select(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {}
}

void os::ui::__config(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {}
}

void os::ui::__conf_brightness(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {}
}

void os::ui::__sleep(uint8_t* state, uint8_t* prev) {
	if ((*state) != (*prev) || input) {}
}
