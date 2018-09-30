#ifndef LIGHT_OS_OS_H_
#define LIGHT_OS_OS_H_

#include "oscore.h"

namespace os {
	peripherals_t* dev;

	void step(void);
	void reboot(void);
};

#endif
