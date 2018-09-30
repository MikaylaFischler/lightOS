#ifndef KEY_CONTROL_HPP_
#define KEY_CONTROL_HPP_

#include <Arduino.h>
#include <inttypes.h>

#define KEYCTRL_NUM_KEYS 4

#define KEYCTRL_KEYTYPE_ESC 0x0
#define KEYCTRL_KEYTYPE_BACK 0x1
#define KEYCTRL_KEYTYPE_SELECT 0x2
#define KEYCTRL_KEYTYPE_NEXT 0x3

#define KEYCTRL_KEY_ESC 0x1
#define KEYCTRL_KEY_BACK 0x2
#define KEYCTRL_KEY_SELECT 0x4
#define KEYCTRL_KEY_NEXT 0x8

/*!
 * TODO debounce ISRs to make this correct
 * @note One press worth of history is kept (in the high four bits).
 */
class KeyControl {
private:
	static uint8_t keys[KEYCTRL_NUM_KEYS];

	KeyControl() {};
	~KeyControl() {};
public:
	static void init(void);
	static bool attachKey(uint8_t key_type, uint8_t key_port);

	// alternate way of reading (in comparison to exposed variable)
	static uint8_t getKeyState(void);
	static uint8_t getLastKeyState(void);

	// public for ISRs
	static volatile uint8_t key_state_mask;

	static void __key_esc_isr(void);
	static void __key_back_isr(void);
	static void __key_sel_isr(void);
	static void __key_next_isr(void);
};

#endif
