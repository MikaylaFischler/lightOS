#ifndef LIGHT_OS_LEDCTRL_H_
#define LIGHT_OS_LEDCTRL_H_

#include <Adafruit_NeoPixel.h>
#include "os.hpp"
#include "../../conf/config.h"

#define ID_STRIP_NULL 0x0

#define FLAG_REQ_SHOW 0x80

namespace os {
	namespace led_ctrl {
		struct anim_data {
			uint8_t i, j, k, l_flag;
			uint16_t counter;
			uint8_t sys_flag;
		};

		typedef struct os::led_ctrl::anim_data AnimationData;

		struct anim_reg {
			uint8_t id;
			const __FlashStringHelper* name;
			void (*anim)(Adafruit_NeoPixel*, AnimationData*);
			struct os::led_ctrl::anim_reg* next;
		};

		typedef struct os::led_ctrl::anim_reg RegisteredAnimation;

		static void init(void);
		static void run(uint8_t anim_id, uint8_t strip_id);
		static void update(void);

		static void registerAnimation(void (*anim)(Adafruit_NeoPixel*, AnimationData*), uint8_t anim_id, const __FlashStringHelper* name);
		static RegisteredAnimation* getAnimationList(void);
		static uint8_t getAnimationCount(void);

		static AnimationData* data[NUM_STRIPS];
		static RegisteredAnimation* running[NUM_STRIPS];
		static RegisteredAnimation* registry_head;
		static RegisteredAnimation* registry_tail;

		static uint8_t anim_count;
		static uint8_t cur_run;

		static RegisteredAnimation* search_registry(uint8_t id, RegisteredAnimation* entry);
	};
};


#endif
