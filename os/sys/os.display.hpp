#ifndef LIGHT_OS_DISPLAY_H_
#define LIGHT_OS_DISPLAY_H_

#include <string.h>
#include "os.hpp"
#include "../dev/LCD.hpp"

#define DISP_CMD_PRINT_C	0x01	// character print
#define DISP_CMD_PRINT_I	0x02	// integer print
#define DISP_CMD_PRINT_L	0x03	// long integer print
#define DISP_CMD_PRINT_S	0x04	// string print
#define DISP_CMD_PRINT_F	0x05	// string-in-flash print (__FlashStringHelper)

#define DISP_CMD_CURSOR		0x10	// set the cursor
#define DISP_CMD_HOME 		0x20	// set home
#define DISP_CMD_CLEAR		0x30	// clear display (and home)

class os::display {
private:
	struct cmd_t {
		uint8_t command;
		size_t data_length;
		uint8_t base;
		void* data;
		struct os::display::cmd_t* next;
	};

	typedef struct os::display::cmd_t cmd_t;
	static cmd_t* cmd_queue;

	static void __queue_cmd(uint8_t command, void* data, size_t size, uint8_t base);

	display(void) {};
	~display(void) {};
public:
	static void init(void);
	static void update(void);

	static void print(char data, uint8_t base);
	static void print(int data,  uint8_t base);
	static void print(long data, uint8_t base);
	static void print(char* data);
	static void print(const __FlashStringHelper* data);

	static void setCursor(uint8_t column, uint8_t row);
	static void home(void);
	static void clear(void);
};

#endif
