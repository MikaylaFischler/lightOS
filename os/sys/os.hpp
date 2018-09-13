#ifndef LIGHT_OS_OS_H_
#define LIGHT_OS_OS_H_

#include "oscore.h"

class os {
protected:
	static peripherals_t* peripherals;
private:
	static void __step_ui(peripherals_t* peripherals);
	static void __step_display(peripherals_t* peripherals);
	static void __step_leds(peripherals_t* peripherals);

	os(void) {};
	~os(void) {};
public:
	class ui;
	class display;
	class led_ctrl;

	static void __attach(peripherals_t* peripherals);

	static void step(void);
	static void reboot(void);
};

#endif
