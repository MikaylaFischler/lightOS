#ifndef LIGHT_OS_CORE_H_
#define LIGHT_OS_CORE_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../dev/KeyControl.hpp"
#include "../dev/LCD.hpp"

struct __peripherals {
	KeyControl* keys;
	LCD* lcd;
	Adafruit_NeoPixel** leds;
};

typedef struct __peripherals peripherals_t;

#include "os.hpp"

struct __instance {
	os* sys;
	peripherals_t* peripherals;
};

typedef struct __instance instance_t;

instance_t* lightos_inst;

#endif
