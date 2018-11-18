#ifndef LIGHT_OS_BOOT_H_
#define LIGHT_OS_BOOT_H_

#include <Arduino.h>
#include "../../conf/config.h"
#include "../../def/animations.h"
#include "../share/free_memory.h"

void boot(void);
void boot_fail(void);

void register_animations(void);

#endif
