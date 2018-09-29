#ifndef LIGHT_OS_OS_H_
#define LIGHT_OS_OS_H_

#include "oscore.h"

class os {
private:
	static void __step_ui(void);
	static void __step_display(void);
	static void __step_leds(void);

	os(void) {};
	~os(void) {};
public:
	class ui;
	class display;
	class led_ctrl;

	static peripherals_t* dev;

	static void step(void);
	static void reboot(void);
};

#endif
