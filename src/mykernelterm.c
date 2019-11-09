#include "mykernelterm.h"


static void myKernelTermPutc(MyKernelTerm* myKernelTerm, char c)
{
	switch (c)
	{
		case '\n':
		{
			myKernelTerm->term_col = 0;
			myKernelTerm->term_row ++;
			break;
		}
 
		case '\t':
		{
			myKernelTerm->term_col += TAB_WIDTH;
			break;
		}
 
		default:
		{
			const size_t index = (VGA_COLS * myKernelTerm->term_row) + myKernelTerm->term_col;
			myKernelTerm->vga_buffer[index] = ((uint16_t)myKernelTerm->term_color << 8) | c;
			myKernelTerm->term_col ++;
			break;
		}
	}
 
	if (myKernelTerm->term_col >= VGA_COLS)
	{
		myKernelTerm->term_col = 0;
		myKernelTerm->term_row ++;
	}
 
	if (myKernelTerm->term_row >= VGA_ROWS)
	{
		myKernelTerm->term_col = 0;
		myKernelTerm->term_row = 0;
	}
}

static void myKernelTermPrint(MyKernelTerm* term, const char* str)
{
	size_t i;
	for (i = 0; str[i] != '\0'; i ++)
	{
		term->putc(term, str[i]);
	}
}

MyKernelTerm myKernelTermNew(void) {
	MyKernelTerm myKernelTerm;
	
	int col, row;
	
	myKernelTerm.putc = &myKernelTermPutc;
	myKernelTerm.print = &myKernelTermPrint;
	
	myKernelTerm.vga_buffer = (uint16_t*)0xB8000;
	myKernelTerm.term_col = 0;
	myKernelTerm.term_row = 0;
	myKernelTerm.term_color = 0x0F;
	
	for (col = 0; col < VGA_COLS; col ++)
	{
		for (row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			myKernelTerm.vga_buffer[index] = ((uint16_t)myKernelTerm.term_color << 8) | ' ';
		}
	}
	
	return myKernelTerm;
}
