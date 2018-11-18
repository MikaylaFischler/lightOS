#ifndef LIGHT_OS_H_
#define LIGHT_OS_H_

// OS core
#include "sys/oscore.h"
#include "sys/os.cpp"

// share
#include "share/free_memory.c"

// OS modules
#include "sys/os.ui.cpp"
#include "sys/os.display.cpp"
#include "sys/os.led_ctrl.cpp"
#include "sys/os.led_ctrl.anim_select.cpp"

// peripherals
#include "dev/KeyControl.cpp"
#include "dev/LCD.cpp"

// animations
#include "../def/include.h"

// boot
#include "boot/boot.cpp"

#endif
