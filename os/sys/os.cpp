#include "os.hpp"
#include "os.ui.hpp"
#include "os.display.hpp"
#include "os.led_ctrl.hpp"

void os::step(void) {
	// process user input
	process_input();

	// update subsystems
	ui::update();
	display::update();
	led_ctrl::update();
}

void os::process_input(void) {
	// stop interrupts
	noInterrupts();

	uint8_t input = os::dev->in.getKeyState();
	uint8_t last_input = os::dev->in.getLastKeyState();

	// re-enable interrupts
	interrupts();

	if ((input != last_input) && (input != last_processed_input)) {
		switch (input) {
			case KEYCTRL_KEY_ESC:
				ui::stepOut();
				break;
			case KEYCTRL_KEY_BACK:
				ui::stepPrev();
				break;
			case KEYCTRL_KEY_SELECT:
				ui::select();
				break;
			case KEYCTRL_KEY_NEXT:
				ui::stepNext();
				break;
		}

		#ifdef DEBUG
		Serial.print(F("Free Memory: "));
		Serial.println(freeMemory());
		Serial.print(F("KEY PRESSED: "));
		Serial.println(input, HEX);
		#endif

		last_processed_input = input;
	}
}
