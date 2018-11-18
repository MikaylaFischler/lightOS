/*!
	@file free_memory.c
	@brief Calculate free memory on arduino ARM and AVR.
	Operates based on if "__arm__" or if "__SAM3X8E__" is defined.
*/

#include <Arduino.h>
#include "free_memory.h"

#if defined (__arm__) && defined (__SAM3X8E__) // Arduino Due compatible
// arduino due free memory from here by user 'sync'
// https://stackoverflow.com/questions/17723733/arduino-due-conditional-compilation-constant-for-custom-library

/*!
	@brief Calculate free memory in bytes.
	@return integer bytes free
*/
int freeMemory() {
	char *heapend = sbrk(0);
	register char * stack_ptr asm ("sp");
	struct mallinfo mi = mallinfo();

	return stack_ptr - heapend + mi.fordblks;
}

/*!
	@brief Prints test results showing dynamic RAM in use,
   		static RAM in use, stack RAM in use, and an estimate at free memory.
*/
void testfreememory() {
	char *heapend = sbrk(0);
	register char * stack_ptr asm ("sp");
	struct mallinfo mi = mallinfo();

	delay(100);
	printf("\nDynamic RAM used: %d\n",mi.uordblks);
	delay(100);
	printf("Program Static RAM used %d\n",&_end - ramstart);
	delay(100);
	printf("Stack RAM used %d\n\n",ramend - stack_ptr);
	delay(100);
	printf("My guess at free mem: %d\n",stack_ptr - heapend + mi.fordblks);
	delay(100);
}

#else // for other boards (assumed AVR)

extern unsigned int __heap_start; //!< start of heap memory
extern void *__brkval; //!< pointer to last memory address

/*!
	@brief The free list structure as maintained by the avr-libc memory allocation routines.
 */
struct __freelist {
	size_t sz;
	struct __freelist *nx;
};

extern struct __freelist *__flp; //!< the head of the free list structure

/*!
	@brief Calculates the size of the free list
*/
int freeListSize() {
	struct __freelist* current;
	int total = 0;

	for (current = __flp; current; current = current->nx) {
		total += 2; /* Add two bytes for the memory block's header  */
		total += (int) current->sz;
	}

	return total;
}

/*!
	@brief Calculate free memory in bytes
	@return integer bytes free
*/
int freeMemory() {
	int free_memory;

	if ((int) __brkval == 0) {
		free_memory = ((int) &free_memory) - ((int) &__heap_start);
	} else {
		free_memory = ((int) &free_memory) - ((int) __brkval);
		free_memory += freeListSize();
	}

	return free_memory;
}

#endif
