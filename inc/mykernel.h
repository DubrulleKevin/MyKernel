#ifndef HEADER_KERNEL
#define HEADER_KERNEL


#include "mykernelconsole.h"
 
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif

#define WELCOME1 \
"\t Welcome to the machine\n\n\
Welcome my son\n\
Welcome to the machine\n\
Where have you been? It's alright, we know where you've been\n\n\
You've been in the pipeline, filling in time\n\
Provided with toys and 'Scouting for Boys'\n\
You bought a guitar to punish your ma\n\
And you didn't like school, and you know you're nobody's fool\n\
So welcome to the machine\n\n\
Welcome my son\n\
Welcome to the machine\n\
What did you dream ?\n\
It's alright we told you what to dream\n\n"

#define WELCOME2 \
"You dreamed of a big star\n\
He played a mean guitar\n\
He always ate in the steak bar\n\
He loved to drive in his Jaguar\n\
So welcome to the machine\n"


typedef struct MyKernel {
	MyKernelConsole console;
} MyKernel;

MyKernel myKernelNew(void);

#endif