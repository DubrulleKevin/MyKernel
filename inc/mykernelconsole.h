#ifndef HEADER_KERNEL_CONSOLE
#define HEADER_KERNEL_CONSOLE


#include <stdint.h>


typedef enum MyKernelConsolePort {
	COM1 = 0x3f8
} MyKernelConsolePort;

typedef struct MyKernelConsole {
	void (*putc)(struct MyKernelConsole* console, const char c);
	void (*puts)(struct MyKernelConsole* console, const char* str);
	char (*getc)(struct MyKernelConsole* console);
	
	MyKernelConsolePort port;
} MyKernelConsole;

MyKernelConsole myKernelConsoleNew(const MyKernelConsolePort port);


#endif