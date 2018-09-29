#include "os.hpp"
#include "os.display.hpp"
#include "os.led_ctrl.hpp"

void os::step(void) {
	__step_ui();
	display::update();
	led_ctrl::update();
}

void os::reboot(void) {

}

void os::__step_ui(void) {

}
