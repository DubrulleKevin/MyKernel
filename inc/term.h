#ifndef HEADER_TERM
#define HEADER_TERM


#include <stddef.h>
#include <stdint.h>

#define VGA_COLS 80
#define VGA_ROWS 25
#define TAB_WIDTH 8


typedef struct MyKernelTerm {
	void (*putc)(struct MyKernelTerm* , char);
	void (*print)(struct MyKernelTerm*, const char*);
	
	volatile uint16_t* vga_buffer;
	int term_col;
	int term_row;
	uint8_t term_color;
} MyKernelTerm;

MyKernelTerm myKernelTermNew(void);


#endif