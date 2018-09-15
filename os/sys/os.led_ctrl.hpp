#ifndef LIGHT_OS_LEDCTRL_H_
#define LIGHT_OS_LEDCTRL_H_

#include "os.hpp"

struct os::led_ctrl::anim_reg;
typedef struct os::led_ctrl::anim_reg RegisteredAnimation;

class os::led_ctrl {
private:
	static uint8_t usedBy[2];
	static RegisteredAnimation* registry;

	led_ctrl(void);
	~led_ctrl(void);
public:
	struct anim_reg {
		uint8_t id;
		Animation* animation;
		struct os::led_ctrl::anim_reg last;
		struct os::led_ctrl::anim_reg next;
	};

	static void queue(uint8_t anim_id);

	static void registerAnimation(Animation* anim, anim_id);
	static RegisteredAnimation* getAnimationList(void);
};

#endif
