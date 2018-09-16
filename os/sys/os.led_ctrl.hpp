#ifndef LIGHT_OS_LEDCTRL_H_
#define LIGHT_OS_LEDCTRL_H_

#include "os.hpp"

class os::led_ctrl {
public:
	struct anim_reg {
		uint8_t id;
		uint8_t num_strips;
		uint8_t* strip_req;
		void (*anim)(Adafruit_NeoPixel**);
		struct os::led_ctrl::anim_reg* last;
		struct os::led_ctrl::anim_reg* next;
	};

	typedef struct os::led_ctrl::anim_reg RegisteredAnimation;

	static void queue(uint8_t anim_id);

	static void registerAnimation(void (*anim)(Adafruit_NeoPixel**), uint8_t anim_id);
	static RegisteredAnimation* getAnimationList(void);
private:
	static uint8_t running[2];
	static RegisteredAnimation* registry;

	led_ctrl(void);
	~led_ctrl(void);
};


#endif
