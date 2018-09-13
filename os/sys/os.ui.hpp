#ifndef LIGHT_OS_UI_H_
#define LIGHT_OS_UI_H_

#include "os.hpp"

#define UI_STEP_OUT 	0x1
#define UI_STEP_PREV 	0x2
#define UI_SELECT 		0x4
#define UI_STEP_NEXT 	0x8

class os::ui {
private:
	void step(uint8_t command);
	void __root(uint8_t state);
	void __anim_select(uint8_t state);
	void __config(uint8_t state);

	struct ui_state_t {
		uint8_t state;
		void (*handler)(void);
		struct os::ui::ui_state_t* below;
	};

	static struct os::ui::ui_state_t* ui_stack;
	static struct instance_t* instance;

	ui(void) {};
	~ui(void) {};
public:
	static void __sync(struct instance_t* instance);

	static void init(void);
	static void restart(void);

	static void stepOut(void);
	static void stepPrev(void);
	static void stepNext(void);
	static void select(void);
};

#endif