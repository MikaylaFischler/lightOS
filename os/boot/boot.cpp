#include "boot.h"

void boot(void) {
	// allocate device storage
	os::dev = (peripherals_t*) calloc(sizeof(peripherals_t), 1);

	#ifdef DEBUG
	Serial.begin(115200);
	Serial.println(F("[~~~~~~~~~~     lightOS     ~~~~~~~~~~]"));
	Serial.print(F("System Version: "));
	Serial.println(F(LIGHTOS_VERSION));
	Serial.println(F(""));
	Serial.println(F("Boot initiated in DEBUG mode..."));
	#endif

	// initialize LCD display
	os::dev->out = new LCD(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
	os::display::init();

	// begin output
	os::dev->out->print(F(LIGHTOS_VERSION));
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("lcd initialized "));
	delay(500);
	#endif
	#ifdef DEBUG
	Serial.println(F("LCD Initialized..."));
	#endif

	// link devices to system
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("/dev init       "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Initializing devices..."));
	#endif

	// setup additional devices
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("/dev init input "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Initializing inputs..."));
	#endif

	// initialize keypad input
	os::dev->in.init();
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init input esc "));
	delay(200);
	#endif
	uint8_t status = os::dev->in.attachKey(KEYCTRL_KEYTYPE_ESC, PIN_ESC_KEY);
	#ifndef FASTBOOT
		if (status != 0) {
			switch (status) {
				case 1:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> out of range "));
				break;
				case 2:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> intrpt used  "));
				break;
			}

			boot_fail();
		}
	#else
		if (status != 0) { boot_fail(); }
	#endif
	#ifdef DEBUG
	Serial.println(F("\t> Init Escape Key..."));
	#endif

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init input back"));
	delay(200);
	#endif
	status = os::dev->in.attachKey(KEYCTRL_KEYTYPE_BACK, PIN_BACK_KEY);
	#ifndef FASTBOOT
		if (status != 0) {
			switch (status) {
				case 1:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> out of range "));
				break;
				case 2:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> intrpt used  "));
				break;
			}

			boot_fail();
		}
	#else
		if (status != 0) { boot_fail(); }
	#endif
	#ifdef DEBUG
	Serial.println(F("\t> Init Back Key..."));
	#endif

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init input sel "));
	delay(200);
	#endif
	status = os::dev->in.attachKey(KEYCTRL_KEYTYPE_SELECT, PIN_SEL_KEY);
	#ifndef FASTBOOT
		if (status != 0) {
			switch (status) {
				case 1:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> out of range "));
				break;
				case 2:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> intrpt used  "));
				break;
			}

			boot_fail();
		}
	#else
		if (status != 0) { boot_fail(); }
	#endif
	#ifdef DEBUG
	Serial.println(F("\t> Init Select Key..."));
	#endif

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init input next"));
	delay(200);
	#endif
	status = os::dev->in.attachKey(KEYCTRL_KEYTYPE_NEXT, PIN_NEXT_KEY);
	#ifndef FASTBOOT
		if (status != 0) {
			switch (status) {
				case 1:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> out of range "));
				break;
				case 2:
					os::dev->out->setCursor(0, 1);
					os::dev->out->print(F("!> intrpt used  "));
				break;
			}

			boot_fail();
		}
	#else
		if (status != 0) { boot_fail(); }
	#endif
	#ifdef DEBUG
	Serial.println(F("\t> Init Next Key..."));
	#endif

	// initialize LEDs
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("/dev init led   "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Initializing LEDs..."));
	#endif
	os::dev->leds = (ledstrips_t*) calloc(sizeof(ledstrips_t), 1);
	os::dev->leds->num_strips = NUM_STRIPS;
	os::dev->leds->strips = (Adafruit_NeoPixel**) malloc(sizeof(Adafruit_NeoPixel*) * os::dev->leds->num_strips);

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init led 0     "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("\t>Initializing Strip 0..."));
	#endif
	os::dev->leds->strips[0] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_1, STRIP_TYPE_RGB);
	os::dev->leds->strips[0]->begin();
	os::dev->leds->strips[0]->show();

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init led 1     "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("\t>Initializing Strip 1..."));
	#endif
	os::dev->leds->strips[1] = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_STRIP_2, STRIP_TYPE_RGB);
	os::dev->leds->strips[1]->begin();
	os::dev->leds->strips[1]->show();

	// setup remaining os modules

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init os.ui     "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Initializing UI..."));
	#endif
	os::ui::init();

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init os.ledctrl"));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Initializing LED Control..."));
	#endif
	os::led_ctrl::init();

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">reg animations"));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Registering LED animations..."));
	#endif
	register_animations();

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">boot complete  "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println(F("Boot Sequence Finished."));
	Serial.println(F(""));
	#endif

	// clear input status
	os::dev->in.clearKeys();

	// start timer interrupt
	os::dev->in.start();
}

void boot_fail(void) {
	#ifdef DEBUG
	Serial.println(F("Fatal Boot Failure!"));
	#endif
	os::dev->out->setCursor(0, 0);
	os::dev->out->print(F(">>BOOT  FAILED<<"));
	delay(250);
	exit(1);
}

void register_animations(void) {
	// basic color animations
	os::led_ctrl::registerAnimation(anim__white, ANIMATION_WHITE, F("<-   White    ->"));
	os::led_ctrl::registerAnimation(anim__soft_white, ANIMATION_SOFT_WHITE, F("<- Soft White ->"));
	os::led_ctrl::registerAnimation(anim__red, ANIMATION_RED, F("<-    Red     ->"));
	os::led_ctrl::registerAnimation(anim__orn, ANIMATION_ORANGE, F("<-   Orange   ->"));
	os::led_ctrl::registerAnimation(anim__ylw, ANIMATION_YELLOW, F("<-   Yellow   ->"));
	os::led_ctrl::registerAnimation(anim__grn, ANIMATION_GREEN, F("<-   Green    ->"));
	os::led_ctrl::registerAnimation(anim__blu, ANIMATION_BLUE, F("<-    Blue    ->"));
	os::led_ctrl::registerAnimation(anim__prp, ANIMATION_PURPLE, F("<-   Purple   ->"));
	os::led_ctrl::registerAnimation(anim__pnk, ANIMATION_PINK, F("<-    Pink    ->"));

	// fade animations
	os::led_ctrl::registerAnimation(anim__white_fade, ANIMATION_WHITE_FADE, F("<-   White    ->"));
	os::led_ctrl::registerAnimation(anim__soft_white_fade, ANIMATION_SOFT_WHITE_FADE, F("<- Soft White ->"));
	os::led_ctrl::registerAnimation(anim__red_fade, ANIMATION_RED_FADE, F("<-    Red     ->"));
	os::led_ctrl::registerAnimation(anim__orn_fade, ANIMATION_ORANGE_FADE, F("<-   Orange   ->"));
	os::led_ctrl::registerAnimation(anim__ylw_fade, ANIMATION_YELLOW_FADE, F("<-   Yellow   ->"));
	os::led_ctrl::registerAnimation(anim__grn_fade, ANIMATION_GREEN_FADE, F("<-   Green    ->"));
	os::led_ctrl::registerAnimation(anim__blu_fade, ANIMATION_BLUE_FADE, F("<-    Blue    ->"));
	os::led_ctrl::registerAnimation(anim__prp_fade, ANIMATION_PURPLE_FADE, F("<-   Purple   ->"));
	os::led_ctrl::registerAnimation(anim__pnk_fade, ANIMATION_PINK_FADE, F("<-    Pink    ->"));
}
