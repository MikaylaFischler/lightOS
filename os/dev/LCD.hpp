#ifndef LCD_HPP_
#define LCD_HPP_

/**
 *	Device code for LiquidCrystal compatible devices.
 *  Based off of the LiquidCrystal library and modified in order to allow for use without system-wide delays
 * 	@note This version is static.
 */

#include <inttypes.h>
#include "Print.h"

// commands
#define LCD_CLEARDISPLAY 	0x01
#define LCD_RETURNHOME 		0x02
#define LCD_ENTRYMODESET 	0x04
#define LCD_DISPLAYCONTROL 	0x08
#define LCD_CURSORSHIFT 	0x10
#define LCD_FUNCTIONSET 	0x20
#define LCD_SETCGRAMADDR 	0x40
#define LCD_SETDDRAMADDR 	0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 			0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 	0x04
#define LCD_DISPLAYOFF 	0x00
#define LCD_CURSORON 	0x02
#define LCD_CURSOROFF 	0x00
#define LCD_BLINKON 	0x01
#define LCD_BLINKOFF 	0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 	0x00
#define LCD_MOVERIGHT 	0x04
#define LCD_MOVELEFT 	0x00

// flags for function set
#define LCD_8BITMODE 	0x10
#define LCD_4BITMODE 	0x00
#define LCD_2LINE 		0x08
#define LCD_1LINE 		0x00
#define LCD_5x10DOTS 	0x04
#define LCD_5x8DOTS 	0x00

class LCD : public Print {
private:
	static void send(uint8_t, uint8_t);
	static void write4bits(uint8_t);
	static void write8bits(uint8_t);
	static void pulseEnable();

	static uint8_t _rs_pin; 		// LOW: command.  HIGH: character.
	static uint8_t _rw_pin; 		// LOW: write to LCD.  HIGH: read from LCD.
	static uint8_t _enable_pin; 	// activated by a HIGH pulse.
	static uint8_t _data_pins[8];

	static uint8_t _displayfunction;
	static uint8_t _displaycontrol;
	static uint8_t _displaymode;

	static uint8_t _initialized;

	static uint8_t _numlines;
	static uint8_t _row_offsets[4];

	LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
	LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
public:
	static void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
				uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	static void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

	static void clear();
	static void home();

	static void noDisplay();
	static void display();
	static void noBlink();
	static void blink();
	static void noCursor();
	static void cursor();
	static void scrollDisplayLeft();
	static void scrollDisplayRight();
	static void leftToRight();
	static void rightToLeft();
	static void autoscroll();
	static void noAutoscroll();

	static void setRowOffsets(int row1, int row2, int row3, int row4);
	static void createChar(uint8_t, uint8_t[]);
	static void setCursor(uint8_t, uint8_t);
	virtual size_t write(uint8_t);
	static void command(uint8_t);

	using Print::write;
};

#endif
