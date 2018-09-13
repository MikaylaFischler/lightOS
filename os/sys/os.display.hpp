#ifndef LIGHT_OS_DISPLAY_H_
#define LIGHT_OS_DISPLAY_H_

#include "os.hpp"

#define DISP_CMD_PRINT_C 0x08
#define DISP_CMD_PRINT_I 0x09
#define DISP_CMD_PRINT_L 0x0A
#define DISP_CMD_PRINT_S 0x0C

#define DISP_CMD_CURSOR 0x10
#define DISP_CMD_HOME 	0x20
#define DISP_CMD_CLEAR	0x80

class os::display {
private:
	struct cmd_t {
		uint8_t command;
		size_t data_length;
		uint8_t base;
		void* data;
		struct os::display::cmd_t* next;
	};

	static struct os::display::cmd_t* cmd_queue;

	display(void) {};
	~display(void) {};
public:
	static void init(void);
	static void update(void);

	static void print(char data, uint8_t base);
	static void print(int data,  uint8_t base);
	static void print(long data, uint8_t base);
	static void print(char* string);

	static void setCursor(uint8_t column, uint8_t row);
	static void home(void);
	static void clear(void);
};

#endif
