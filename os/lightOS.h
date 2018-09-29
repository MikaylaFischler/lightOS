#ifndef LIGHT_OS_H_
#define LIGHT_OS_H_

// OS core
#include "sys/oscore.h"
#include "sys/os.cpp"

// OS modules
#include "sys/os.ui.hpp"
#include "sys/os.display.cpp"
#include "sys/os.led_ctrl.hpp"

// peripherals
#include "dev/KeyControl.cpp"
#include "dev/LCD.cpp"

// boot
#include "boot/boot.cpp"

#endif
