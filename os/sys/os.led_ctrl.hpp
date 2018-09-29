#ifndef LIGHT_OS_LEDCTRL_H_
#define LIGHT_OS_LEDCTRL_H_

#include <Adafruit_NeoPixel.h>
#include "os.hpp"
#include "../../conf/config.h"

#define ID_STRIP_NULL 0x0

class os::led_ctrl {
public:
	struct anim_reg {
		uint8_t id;
		uint8_t num_strips;
		uint8_t* strip_req;
		void (*anim)(Adafruit_NeoPixel**);
		struct os::led_ctrl::anim_reg* next;
	};

	typedef struct os::led_ctrl::anim_reg RegisteredAnimation;

	static void init(void);
	static void run(uint8_t anim_id);
	static void update(void);

	static void registerAnimation(void (*anim)(Adafruit_NeoPixel**), uint8_t anim_id);
	static RegisteredAnimation* getAnimationList(void);
private:
	static RegisteredAnimation* running[NUM_STRIPS];
	static RegisteredAnimation* registry_head;
	static RegisteredAnimation* registry_tail;

	static uint8_t cur_run;

	static RegisteredAnimation* search_registry(uint8_t id);

	led_ctrl(void);
	~led_ctrl(void);
};


#endif
