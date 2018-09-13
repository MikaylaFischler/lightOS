#ifndef LIGHT_OS_CORE_H_
#define LIGHT_OS_CORE_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "os.hpp"
#include "../dev/KeyControl.hpp"
#include "../dev/LCD.hpp"

struct peripherals_t {
	KeyControl* keys;
	LCD* display;
	Adafruit_NeoPixel** leds;
};

struct instance_t {
	os* sys;
	peripherals_t* peripherals;
};

struct instance_t* lightos_inst;

#endif
