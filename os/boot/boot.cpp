#include "boot.h"

void boot(void) {
	// allocate device storage
	os::dev = (peripherals_t*) calloc(sizeof(peripherals_t), 1);

	// initialize LCD display
	os::dev->out = new LCD(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
	os::display::init();

	// begin output
	os::dev->out->print(LIGHTOS_VERSION);
	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print("lcd initialized");
	#endif

	// link devices to system
	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print("/dev init");
	#endif

	// setup additional devices
	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print("/dev init input");
	#endif

	// initialize keypad input
	os::dev->in.init();
	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print(">init input esc");
	#endif
	bool err = os::dev->in.attachKey(KEYCTRL_KEYTYPE_ESC, PIN_ESC_KEY);
	if (err) { boot_fail(); }

	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print(">init input back");
	#endif
	err = os::dev->in.attachKey(KEYCTRL_KEYTYPE_BACK, PIN_BACK_KEY);
	if (err) { boot_fail(); }

	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print(">init input sel");
	#endif
	err = os::dev->in.attachKey(KEYCTRL_KEYTYPE_SELECT, PIN_SEL_KEY);
	if (err) { boot_fail(); }

	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print(">init input next");
	#endif
	err = os::dev->in.attachKey(KEYCTRL_KEYTYPE_NEXT, PIN_NEXT_KEY);
	if (err) { boot_fail(); }

	// initialize LEDs
	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print("/dev init led");
	#endif
	os::dev->leds = (ledstrips_t*) calloc(sizeof(ledstrips_t), 1);
	os::dev->leds->num_strips = NUM_STRIPS;
	os::dev->leds->strips = (Adafruit_NeoPixel**) malloc(sizeof(Adafruit_NeoPixel*) * os::dev->leds->num_strips);

	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print(">init led 0");
	#endif
	os::dev->leds->strips[0] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_1, STRIP_TYPE_RGB);
	os::dev->leds->strips[0]->begin();
	os::dev->leds->strips[0]->show();

	#ifndef FASTBOOT
	os::dev->out->setCursor(1, 0);
	os::dev->out->print(">init led 1");
	#endif
	os::dev->leds->strips[1] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_2, STRIP_TYPE_RGB);
	os::dev->leds->strips[1]->begin();
	os::dev->leds->strips[1]->show();

	// setup os modules
	os::ui::init();
	os::display::init();
}

void boot_fail(void) {
	os::dev->out->setCursor(0, 0);
	os::dev->out->print(">>BOOT  FAILED<<");
	delay(250);
	exit(1);
}
