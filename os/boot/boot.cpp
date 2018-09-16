#ifndef LIGHT_OS_BOOT_C_
#define LIGHT_OS_BOOT_C_

#include "boot.h"

void boot(instance_t* instance) {
	// allocate device storage
	instance->dev = (peripherals_t*) calloc(sizeof(peripherals_t), 1);

	// initialize LCD display
	instance->dev->out = new LCD(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
	instance->dev->out->begin(2, 16);
	instance->dev->out->clear();

	// begin output
	instance->dev->out->print(LIGHTOS_VERSION);
	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print("lcd initialized");
	#endif

	// link devices to system
	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print("/dev init");
	#endif
	instance->sys->__attach(instance->dev);

	// setup additional devices
	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print("/dev init input");
	#endif

	// initialize keypad input
	instance->dev->in.init();
	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print(">init input esc");
	#endif
	bool err = instance->dev->in.attachKey(KEYCTRL_KEYTYPE_ESC, PIN_ESC_KEY);
	if (err) { boot_fail(instance->dev->out); }

	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print(">init input back");
	#endif
	err = instance->dev->in.attachKey(KEYCTRL_KEYTYPE_BACK, PIN_BACK_KEY);
	if (err) { boot_fail(instance->dev->out); }

	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print(">init input sel");
	#endif
	err = instance->dev->in.attachKey(KEYCTRL_KEYTYPE_SELECT, PIN_SEL_KEY);
	if (err) { boot_fail(instance->dev->out); }

	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print(">init input next");
	#endif
	err = instance->dev->in.attachKey(KEYCTRL_KEYTYPE_NEXT, PIN_NEXT_KEY);
	if (err) { boot_fail(instance->dev->out); }

	// initialize LEDs
	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print("/dev init led");
	#endif
	instance->dev->leds = (ledstrips_t*) calloc(sizeof(ledstrips_t), 1);
	instance->dev->leds->num_strips = NUM_STRIPS;
	instance->dev->leds->strips = (Adafruit_NeoPixel**) malloc(sizeof(Adafruit_NeoPixel*) * instance->dev->leds->num_strips);

	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print(">init led 0");
	#endif
	instance->dev->leds->strips[0] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_1, STRIP_TYPE_RGB);
	instance->dev->leds->strips[0]->begin();
	instance->dev->leds->strips[0]->show();

	#ifndef FASTBOOT
	instance->dev->out->setCursor(1, 0);
	instance->dev->out->print(">init led 1");
	#endif
	instance->dev->leds->strips[1] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_2, STRIP_TYPE_RGB);
	instance->dev->leds->strips[1]->begin();
	instance->dev->leds->strips[1]->show();
}

void boot_fail(LCD* out) {
	out->setCursor(0, 0);
	out->print(">>BOOT  FAILED<<");
	delay(250);
	exit(1);
}

#endif
