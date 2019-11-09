#include <stddef.h>
#include <stdint.h>
 
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif
 

#define VGA_COLS 80
#define VGA_ROWS 25
#define TAB_WIDTH 8

#define WELCOME1 \
" Welcome my son\n \
Welcome to the machine\n \
Where have you been? It's alright, we know where you've been\n\n \
You've been in the pipeline, filling in time\n \
Provided with toys and 'Scouting for Boys'\n \
You bought a guitar to punish your ma\n \
And you didn't like school, and you know you're nobody's fool\n \
So welcome to the machine\n\n \
Welcome my son\n \
Welcome to the machine\n \
What did you dream ?\n \
It's alright we told you what to dream\n\n"

#define WELCOME2 \
" You dreamed of a big star\n \
He played a mean guitar\n \
He always ate in the steak bar\n \
He loved to drive in his Jaguar\n \
So welcome to the machine\n"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;
  
typedef struct MyKernelTerm {
	void (*putc)(struct MyKernelTerm* , char);
	void (*print)(struct MyKernelTerm*, const char*);
} MyKernelTerm;

static void MyKernelTermPutc(MyKernelTerm* term, char c)
{
	(void)(term);
	
	switch (c)
	{
		case '\n':
		{
			term_col = 0;
			term_row ++;
			break;
		}
 
		case '\t':
		{
			term_col += TAB_WIDTH;
			break;
		}
 
		default:
		{
			const size_t index = (VGA_COLS * term_row) + term_col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | c;
			term_col ++;
			break;
		}
	}
 
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row ++;
	}
 
	if (term_row >= VGA_ROWS)
	{
		term_col = 0;
		term_row = 0;
	}
}

static void MyKernelTermPrint(MyKernelTerm* term, const char* str)
{
	size_t i;
	for (i = 0; str[i] != '\0'; i ++)
	{
		term->putc(term, str[i]);
	}
}

MyKernelTerm myKernelTermNew(void) {
	MyKernelTerm myKernelTerm;
	int col;
	int row;
	
	for (col = 0; col < VGA_COLS; col ++)
	{
		for (row = 0; row < VGA_ROWS; row ++)
		{
			const size_t index = (VGA_COLS * row) + col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | ' ';
		}
	}
	
	myKernelTerm.putc = &MyKernelTermPutc;
	myKernelTerm.print = &MyKernelTermPrint;
	
	return myKernelTerm;
}

typedef struct MyKernel {
	MyKernelTerm term;
} MyKernel;

MyKernel myKernelNew(void) {
	MyKernel myKernel;
	myKernel.term = myKernelTermNew();
	
	return myKernel;
}
 
void kernel_main()
{
	MyKernel myKernel = myKernelNew();
 
	myKernel.term.print(&myKernel.term, WELCOME1);
	myKernel.term.print(&myKernel.term, WELCOME2);
}
