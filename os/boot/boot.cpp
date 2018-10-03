#include "boot.h"

void boot(void) {
	// allocate device storage
	os::dev = (peripherals_t*) calloc(sizeof(peripherals_t), 1);

	#ifdef DEBUG
	Serial.begin(115200);
	Serial.println("[~~~~~~~~~~     lightOS     ~~~~~~~~~~]");
	Serial.print("System Version: ");
	Serial.println(LIGHTOS_VERSION);
	Serial.println("");
	Serial.println("Boot initiated in DEBUG mode...");
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
	Serial.println("LCD Initialized...");
	#endif

	// link devices to system
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("/dev init       "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println("Initializing devices...");
	#endif

	// setup additional devices
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("/dev init input "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println("Initializing inputs...");
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
	Serial.println("\t> Init Escape Key...");
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
	Serial.println("\t> Init Back Key...");
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
	Serial.println("\t> Init Select Key...");
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
	Serial.println("\t> Init Next Key...");
	#endif

	// initialize LEDs
	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F("/dev init led   "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println("Initializing LEDs...");
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
	Serial.println("\t>Initializing Strip 0...");
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
	Serial.println("\t>Initializing Strip 1...");
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
	Serial.println("Initializing UI...");
	#endif
	os::ui::init();

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">init os.ledctrl"));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println("Initializing LED Control...");
	#endif
	os::led_ctrl::init();

	#ifndef FASTBOOT
	os::dev->out->setCursor(0, 1);
	os::dev->out->print(F(">boot complete  "));
	delay(200);
	#endif
	#ifdef DEBUG
	Serial.println("Boot Sequence Finished.");
	Serial.println("");
	#endif

	// clear input status
	os::dev->in.clearKeys();

	// start timer interrupt
	os::dev->in.start();
}

void boot_fail(void) {
	#ifdef DEBUG
	Serial.println("Fatal Boot Failure!");
	#endif
	os::dev->out->setCursor(0, 0);
	os::dev->out->print(F(">>BOOT  FAILED<<"));
	delay(250);
	exit(1);
}
