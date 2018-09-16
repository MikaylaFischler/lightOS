#ifndef LIGHT_OS_CORE_H_
#define LIGHT_OS_CORE_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../dev/KeyControl.hpp"
#include "../dev/LCD.hpp"

struct __ledstrips {
	uint8_t num_strips;
	Adafruit_NeoPixel** leds;
};

typedef struct __ledstrips ledstrips_t;

struct __peripherals {
	KeyControl in;
	LCD out;
	ledstrips_t* leds;
};

typedef struct __peripherals peripherals_t;

// must be AFTER peripherals_t definition
#include "os.hpp"

struct __instance {
	os* sys;
	peripherals_t* dev;
};

typedef struct __instance instance_t;

instance_t* lightos_inst;

#endif
