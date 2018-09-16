#ifndef LIGHT_OS_BOOT_C_
#define LIGHT_OS_BOOT_C_

#include "../../conf/config.h"

void boot(instance_t* instance) {
	// allocate device storage
	instance->dev = (peripherals_t*) calloc(sizeof(peripherals_t), 1);

	// initialize LCD display
	instance->dev->out.init(1, PIN_LCD_RS, 255, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7, 0, 0, 0, 0);
	instance->dev->out.begin(2, 16);
	instance->dev->out.clear();

	// begin output
	instance->dev->out.print(LIGHTOS_VERSION);
	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print("lcd initialized");
	#endif

	// link devices to system
	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print("/dev init");
	#endif
	instance->sys->__attach(instance->dev);

	// setup additional devices
	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print("/dev init input");
	#endif

	// initialize keypad input
	instance->dev->in.init();
	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print(">init input esc");
	#endif
	instance->dev->in.init(KEYCTRL_KEYTYPE_ESC, PIN_ESC_KEY);

	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print(">init input back");
	#endif
	instance->dev->in.init(KEYCTRL_KEYTYPE_BACK, PIN_BACK_KEY);

	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print(">init input sel");
	#endif
	instance->dev->in.init(KEYCTRL_KEYTYPE_SELECT, PIN_SEL_KEY);

	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print(">init input next");
	#endif
	instance->dev->in.init(KEYCTRL_KEYTYPE_NEXT, PIN_NEXT_KEY);

	// initialize LEDs
	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print("/dev init led");
	#endif
	instance->dev->leds = malloc(sizeof(Adafruit_NeoPixel*) * NUM_STRIPS));

	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print(">init led 0");
	#endif
	instance->dev->leds[0] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_1, STRIP_TYPE_RGB);
	instance->dev->leds[0]->begin();
	instance->dev->leds[0]->show();

	#ifndef FASTBOOT
	instance->dev->out.setCursor(1, 0);
	instance->dev->out.print(">init led 1");
	#endif
	instance->dev->leds[1] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_2, STRIP_TYPE_RGB);
	instance->dev->leds[1]->begin();
	instance->dev->leds[1]->show();
}

#endif
