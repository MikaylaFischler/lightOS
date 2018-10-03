#ifndef LIGHT_OS_UI_H_
#define LIGHT_OS_UI_H_

#include "os.hpp"

#define UI_INPUT_IDLE	0x0
#define UI_STEP_OUT 	0x1
#define UI_STEP_PREV 	0x2
#define UI_SELECT 		0x4
#define UI_STEP_NEXT 	0x8

/**
	@details heirarchy:
	root
	 |- status
	 |- anim_select
	 ||- strip_select
	 |- config
	 ||- strip specific (select)
	 |||- brightness
	 |- sleep
*/

#define NULL_STATE			0

#define ROOT__STATUS		1
#define ROOT__ANIM_SELECT	2
#define ROOT__CONFIG		3
#define ROOT__SLEEP			4

#define STATUS__OVERVIEW	1

#define ASEL__FIRST			0x1
#define ASEL__LAST			(os::led_ctrl::getAnimationCount())

#define CONFIG__SYSTEM		1
#define CONFIG__STRIP		2
#define CONFIG__S_SEL		1
#define CONFIG__S_BRIGHT	1

#define SLEEP__ON			1

namespace os {
	namespace ui {
		static void spawn_child(uint8_t state, void (*handler)(uint8_t*,uint8_t*,uint16_t*), uint16_t data = 0);
		static void esc(void);

		static void __root(uint8_t* state, uint8_t* prev, uint16_t* data);					// tier 0
		static void __status(uint8_t* state, uint8_t* prev, uint16_t* data);				// tier 1
		static void __anim_select(uint8_t* state, uint8_t* prev, uint16_t* data);			// tier 1
		static void __anim_strip_select(uint8_t* state, uint8_t* prev, uint16_t* data);		// tier 2
		static void __config(uint8_t* state, uint8_t* prev, uint16_t* data);				// tier 1
		static void __config_strip_select(uint8_t* state, uint8_t* prev, uint16_t* data);	// tier 2
		static void __config_brightness(uint8_t* state, uint8_t* prev, uint16_t* data);		// tier 3
		static void __sleep(uint8_t* state, uint8_t* prev, uint16_t* data);					// tier 1

		struct ui_state_t {
			uint8_t state;
			uint8_t prev_state;
			uint16_t data;
			void (*handler)(uint8_t*,uint8_t*,uint16_t*);
			struct os::ui::ui_state_t* parent;
		};

		typedef struct os::ui::ui_state_t ui_state_t;
		static ui_state_t* ui_stack;
		static uint8_t input;
		static uint8_t first_call;

		static void init(void);
		static void update(void);

		static void stepOut(void);
		static void stepPrev(void);
		static void stepNext(void);
		static void select(void);
	};
};

#endif
