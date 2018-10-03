#include "os.display.hpp"
int flag = 0;
/**
 * Initialize the LCD and display system.
 */
void os::display::init(void) {
	// initialize the LCD
	os::dev->out->begin(16, 2);
	os::dev->out->clear();

	// null the command queue
	cmd_queue = NULL;
	cmd_queue_tail = NULL;
}

void os::display::update(void) {
	if (cmd_queue) {
		cmd_t* cmd = cmd_queue;
		uint8_t* tmp = NULL;

		#ifdef DEBUG_VERBOSE
		Serial.println(">> os::display::update");
		Serial.print("HEAD @ 0x");
		Serial.println((uintptr_t) cmd_queue, HEX);
		Serial.print("TAIL @ 0x");
		Serial.println((uintptr_t) cmd_queue_tail, HEX);
		Serial.print("Running command @ 0x");
		Serial.println((uintptr_t) cmd, HEX);
		Serial.print("Containing Data at @ 0x");
		Serial.println((uintptr_t) cmd->data, HEX);
		#endif

		cmd_queue = cmd->next;

		switch (cmd->command) {
			case DISP_CMD_PRINT_C:
				os::dev->out->print(((char*) cmd->data)[0], cmd->base);
				free(cmd->data);
			break;
			case DISP_CMD_PRINT_I:
				os::dev->out->print(((int*) cmd->data)[0], cmd->base);
				free(cmd->data);
			break;
			case DISP_CMD_PRINT_L:
				os::dev->out->print(((long*) cmd->data)[0], cmd->base);
				free(cmd->data);
			break;
			case DISP_CMD_PRINT_S:
				os::dev->out->print((char*) cmd->data);
				free(cmd->data);
			break;
			case DISP_CMD_PRINT_F:
				os::dev->out->print((const __FlashStringHelper*) cmd->data);
			break;
			case DISP_CMD_CURSOR:
				tmp = (uint8_t*) cmd->data;
				os::dev->out->setCursor(tmp[0], tmp[1]);
				free(cmd->data);
			break;
			case DISP_CMD_HOME:
				os::dev->out->home();
			break;
			case DISP_CMD_CLEAR:
				os::dev->out->clear();
			break;
		}

		#ifdef DEBUG_VERBOSE
		Serial.print("HEAD @ 0x");
		Serial.println((uintptr_t) cmd_queue, HEX);
		Serial.print("TAIL @ 0x");
		Serial.println((uintptr_t) cmd_queue_tail, HEX);
		#endif

		free(cmd);

		#ifdef DEBUG_VERBOSE
		Serial.print("Free'd @ 0x");
		Serial.println((uintptr_t) cmd, HEX);
		#endif

		cmd = NULL;
	}
}

void os::display::print(char data, uint8_t base) {
	size_t size = sizeof(char);
	char* val = (char*) malloc(size);
	val[0] = data;

	void* _data = (void*) val;

	__queue_cmd(DISP_CMD_PRINT_C, _data, size, base);
}

void os::display::print(int data, uint8_t base) {
	size_t size = sizeof(int);
	int* val = (int*) malloc(size);
	val[0] = data;

	void* _data = (void*) val;

	__queue_cmd(DISP_CMD_PRINT_I, _data, size, base);
}

void os::display::print(long data, uint8_t base) {
	size_t size = sizeof(long);
	long* val = (long*) malloc(size);
	val[0] = data;

	void* _data = (void*) val;

	__queue_cmd(DISP_CMD_PRINT_L, _data, size, base);
}

void os::display::print(char* data) {
	size_t size = strlen(data);
	char* string = (char*) malloc(sizeof(long) * size);

	for (size_t i = 0; i < size; i++) { string[i] = data[i]; }

	void* _data = (void*) string;

	__queue_cmd(DISP_CMD_PRINT_S, _data, size, 0);
}

void os::display::print(const __FlashStringHelper* data) {
	__queue_cmd(DISP_CMD_PRINT_F, (void*) data, 0, 0);
}

void os::display::setCursor(uint8_t column, uint8_t row) {
	size_t size = sizeof(uint8_t) * 2;
	uint8_t* data = (uint8_t*) malloc(size);

	data[0] = column;
	data[1] = row;

	void* _data = (void*) data;

	__queue_cmd(DISP_CMD_CURSOR, _data, size, 0);
}

void os::display::home(void) { __queue_cmd(DISP_CMD_HOME, NULL, 0, 0); }
void os::display::clear(void) { __queue_cmd(DISP_CMD_CLEAR, NULL, 0, 0); }

void os::display::__queue_cmd(uint8_t command, void* data, size_t size, uint8_t base) {
	cmd_t* cmd = (cmd_t*) malloc(sizeof(cmd_t));

	cmd->command = command;
	cmd->data_length = size;
	cmd->base = base;
	cmd->data = data;
	cmd->next = NULL;

	#ifdef DEBUG_VERBOSE
	Serial.println(">> os::display::__queue_cmd");
	Serial.print("HEAD @ 0x");
	Serial.println((uintptr_t) cmd_queue, HEX);

	Serial.print("TAIL @ 0x");
	Serial.println((uintptr_t) cmd_queue_tail, HEX);

	Serial.print("Queueing command @ 0x");
	Serial.println((uintptr_t) cmd, HEX);
	#endif

	if (cmd_queue) {
		cmd_queue_tail->next = cmd;
		cmd_queue_tail = cmd;
	} else {
		cmd_queue = cmd;
		cmd_queue_tail = cmd;
	}

	#ifdef DEBUG_VERBOSE
	Serial.print("HEAD @ 0x");
	Serial.println((uintptr_t) cmd_queue, HEX);

	Serial.print("TAIL @ 0x");
	Serial.println((uintptr_t) cmd_queue_tail, HEX);
	#endif
}
