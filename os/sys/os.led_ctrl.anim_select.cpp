#include "os.ui.hpp"

void os::ui::__anim_select(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[- AnimSelect -]"));
	}

	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = *state;
	}

	if (first_call || input) {
		switch (*state) {
			case ASEL__CAT_COLOR:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<- SolidColor ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to solid color animation selection
					// spawn_child();
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ASEL__CAT_FADE;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the prev option
					state[0] = ASEL__CAT_SPECIAL;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
			case ASEL__CAT_FADE:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-    Fade    ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to fade animations
					// spawn_child();
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ASEL__CAT_RIPPLE;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the prev option
					state[0] = ASEL__CAT_COLOR;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
			case ASEL__CAT_RIPPLE:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-   Ripple   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to ripple animations
					// spawn_child();
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ASEL__CAT_SPARKLE;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the prev option
					state[0] = ASEL__CAT_FADE;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
			case ASEL__CAT_SPARKLE:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-  Sparkle   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to ripple animations
					// spawn_child();
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ASEL__CAT_RAINBOW;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the prev option
					state[0] = ASEL__CAT_RIPPLE;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
			case ASEL__CAT_RAINBOW:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-  Rainbow   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to ripple animations
					// spawn_child();
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ASEL__CAT_SPECIAL;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the prev option
					state[0] = ASEL__CAT_SPARKLE;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
			case ASEL__CAT_SPECIAL:
				if (first_call) {
					os::display::setCursor(0, 1);
					os::display::print(F("<-  Special   ->"));
				}

				if (input & KEYCTRL_KEY_SELECT) {
					// go to ripple animations
					// spawn_child();
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option
					state[0] = ASEL__CAT_COLOR;
				} else if (input & KEYCTRL_KEY_BACK) {
					// scroll to the prev option
					state[0] = ASEL__CAT_RAINBOW;
				} else if (input & KEYCTRL_KEY_ESC) { esc(); }
				break;
		}
	}
}

void os::ui::__anim_strip_select(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if ((*state) != (*prev) || input) {}
}
