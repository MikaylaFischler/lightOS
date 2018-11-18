#ifndef LIGHT_OS_UI_H_
#define LIGHT_OS_UI_H_

#include "os.hpp"
#include "../../def/animations.h"

#define UI_INPUT_IDLE	0x0
#define UI_STEP_OUT 	0x1
#define UI_STEP_PREV 	0x2
#define UI_SELECT 		0x4
#define UI_STEP_NEXT 	0x8

/**
	@details heirarchy:						<br/>
	root									<br/>
	 |- status								<br/>
	 |- anim_category_select				<br/>
	 ||- animation select					<br/>
	 |||- strip select						<br/>
	 |- config								<br/>
	 ||- category (system or strip)			<br/>
	 |||- strip select						<br/>
	 ||||- brightness						<br/>
	 |- sleep								<br/>
*/

#define NULL_STATE			0

#define ROOT__STATUS		1
#define ROOT__ANIM_SELECT	2
#define ROOT__CONFIG		3
#define ROOT__SLEEP			4

#define STATUS__OVERVIEW	1

#define ASEL__CAT_COLOR		1
#define ASEL__CAT_FADE		2
#define ASEL__CAT_RIPPLE	3
#define ASEL__CAT_SPARKLE	4
#define ASEL__CAT_RAINBOW	5
#define ASEL__CAT_SPECIAL	6

#define ASEL__COLOR_FIRST	ANIMATION_WHITE
#define ASEL__COLOR_LAST	ANIMATION_PINK
#define ASEL__FADE_FIRST	ANIMATION_WHITE_FADE
#define ASEL__FADE_LAST		ANIMATION_PINK_FADE
#define ASEL__RIPPLE_FIRST	ANIMATION_WHITE_RIPPLE
#define ASEL__RIPPLE_LAST	ANIMATION_PINK_SYM_RIPPLE
#define ASEL__SPARKLE_FIRST	ANIMATION_WHITE_SPARKLE
#define ASEL__SPARKLE_LAST	ANIMATION_PINK_SPARKLE
#define ASEL__RAINBOW_FIRST	ANIMATION_RAINBOW
#define ASEL__RAINBOW_LAST	ANIMATION_RAINBOW_FLOW
#define ASEL__SPECIAL_FIRST	ANIMATION_WHITE
#define ASEL__SPECIAL_LAST	ANIMATION_PINK

#define ASEL__STRIP_SEL		1

#define CONFIG__SYSTEM		1
#define CONFIG__STRIP		2
#define CONFIG__S_SEL		1
#define CONFIG__S_BRIGHT	1

#define SLEEP__ON			1

using os::led_ctrl::RegisteredAnimation;

namespace os {
	namespace ui {
		static void spawn_child(uint8_t state, void (*handler)(uint8_t*,uint8_t*,uint16_t*), uint16_t data = 0);
		static void esc(void);

		static void __root(uint8_t* state, uint8_t* prev, uint16_t* data);					// tier 0
		static void __status(uint8_t* state, uint8_t* prev, uint16_t* data);				// tier 1
		static void __anim_cat_select(uint8_t* state, uint8_t* prev, uint16_t* data);		// tier 1
		static void __anim_select_color(uint8_t* state, uint8_t* prev, uint16_t* data);		// tier 2
		static void __anim_strip_select(uint8_t* state, uint8_t* prev, uint16_t* data);		// tier 3
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
