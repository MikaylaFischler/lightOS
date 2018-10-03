#ifndef LIGHT_OS_OS_H_
#define LIGHT_OS_OS_H_

#include "oscore.h"

namespace os {
	peripherals_t* dev;
	uint8_t last_processed_input = 0;

	void step(void);
	void process_input(void);
};

#endif
