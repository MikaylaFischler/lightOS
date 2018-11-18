#include "os.ui.hpp"

void os::ui::__anim_cat_select(uint8_t* state, uint8_t* prev, uint16_t* data) {
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
					spawn_child(ASEL__COLOR_FIRST, __anim_select_color);
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
					spawn_child(ASEL__FADE_FIRST, __anim_select_fade);
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
					spawn_child(ASEL__RIPPLE_FIRST, __anim_select_ripple);
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
					// go to sparkle animations
					spawn_child(ASEL__SPARKLE_FIRST, __anim_select_sparkle);
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
					// go to rainbow animations
					spawn_child(ASEL__RAINBOW_FIRST, __anim_select_rainbow);
				} else if (input & KEYCTRL_KEY_NEXT) {
					// scroll to the next option (skip special until implemented)
					state[0] = ASEL__CAT_RAINBOW;
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
					// go to special animations
					spawn_child(ASEL__SPECIAL_FIRST, __anim_select_special);
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

void os::ui::__anim_select_common(uint8_t* state, uint8_t* prev, uint8_t first, uint8_t last) {
	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = *state;
	}

	if (first_call || input) {
		RegisteredAnimation* anim = os::led_ctrl::get(*state);

		if (first_call) {
			os::display::setCursor(0, 1);
			os::display::print(anim->name);
		}

		if (input & KEYCTRL_KEY_SELECT) {
			// go to solid color animation selection
			spawn_child(ASEL__STRIP_SEL, __anim_strip_select, *state);
		} else if (input & KEYCTRL_KEY_NEXT) {
			// scroll to the next option
			if (state[0] == last) {
				state[0] = first;
			} else {
				state[0]++;
			}
		} else if (input & KEYCTRL_KEY_BACK) {
			// scroll to the prev option
			if (state[0] == first) {
				state[0] = last;
			} else {
				state[0]--;
			}
		} else if (input & KEYCTRL_KEY_ESC) { esc(); }
	}
}

void os::ui::__anim_select_color(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[- SolidColor -]"));
	}

	__anim_select_common(state, prev, ASEL__COLOR_FIRST, ASEL__COLOR_LAST);
}

void os::ui::__anim_select_fade(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[---- Fade ----]"));
	}

	__anim_select_common(state, prev, ASEL__FADE_FIRST, ASEL__FADE_LAST);
}

void os::ui::__anim_select_ripple(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[--- Ripple ---]"));
	}

	__anim_select_common(state, prev, ASEL__RIPPLE_FIRST, ASEL__RIPPLE_LAST);
}

void os::ui::__anim_select_sparkle(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[-  Sparkle   -]"));
	}

	__anim_select_common(state, prev, ASEL__SPARKLE_FIRST, ASEL__SPARKLE_LAST);
}

void os::ui::__anim_select_rainbow(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[-  Rainbow   -]"));
	}

	__anim_select_common(state, prev, ASEL__RAINBOW_FIRST, ASEL__RAINBOW_LAST);
}

void os::ui::__anim_select_special(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[-  Special   -]"));
	}

	__anim_select_common(state, prev, ASEL__SPECIAL_FIRST, ASEL__SPECIAL_LAST);
}

void os::ui::__anim_strip_select(uint8_t* state, uint8_t* prev, uint16_t* data) {
	if (prev[0] == NULL_STATE) {
		os::display::clear();
		os::display::print(F("[ STRIP SELECT ]"));
	}

	if ((*state) != (*prev)) {
		first_call = true;
		prev[0] = *state;
	}

	if (first_call || input) {
		if (input & KEYCTRL_KEY_SELECT) {
			// set the animation for that strip
			os::led_ctrl::run((uint8_t) (*data), (*state));
		} else if (input & KEYCTRL_KEY_NEXT) {
			// increment strip number
			state[0]++;
			if (state[0] > os::dev->leds->num_strips)  { state[0] = 1; }
		} else if (input & KEYCTRL_KEY_BACK) {
			// decrement strip number
			if (state[0] == 1)  { state[0] = os::dev->leds->num_strips + 1; }
			state[0]--;
		} else if (input & KEYCTRL_KEY_ESC) { esc(); }

		os::display::setCursor(0, 1);

		int strip = (*state) - 1;

		if (strip < 10) {
			os::display::print(F("<- strip  00"));
		} else if (strip < 100) {
			os::display::print(F("<- strip  0"));
		} else {
			os::display::print(F("<- strip  "));
		}

		os::display::print(strip);
		os::display::print(F(" ->"));
	}
}
