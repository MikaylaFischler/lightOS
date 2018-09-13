#ifndef LIGHT_OS_OS_H_
#define LIGHT_OS_OS_H_

#include "oscore.h"

class os {
private:
	static void __step_ui(struct instance_t* instance);
	static void __step_display(struct instance_t* instance);
	static void __step_leds(struct instance_t* instance);

	struct instance_t* instance;

	os(void) {};
	~os(void) {};
public:
	class ui;
	class display;
	class led_controller;

	static void __sync(struct instance_t* instance);

	static void step(void);
};

#endif
