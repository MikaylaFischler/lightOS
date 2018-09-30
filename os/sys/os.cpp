#include "os.hpp"
#include "os.ui.hpp"
#include "os.display.hpp"
#include "os.led_ctrl.hpp"

void os::step(void) {
	ui::update();
	display::update();
	led_ctrl::update();
}

void os::reboot(void) {

}
