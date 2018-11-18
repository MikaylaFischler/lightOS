// MemoryFree library based on code posted here:
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
// Extended by Matthew Murdoch to include walking of the free list.
// Re-formatted and simplified for this use case by Mikayla Fischler

#ifndef FREE_MEMORY_H_
#define FREE_MEMORY_H_

#if defined (__arm__) && defined (__SAM3X8E__) // Arduino Due compatible

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

extern char _end;
extern "C" char *sbrk(int i);
char *ramstart = (char *) 0x20070000;
char *ramend   = (char *) 0x20088000;

void testfreememory();

#endif

int freeMemory();

int mem_available = 0;

#endif
