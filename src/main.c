#include "mykernel.h"


void kernel_main()
{
	MyKernel myKernel = myKernelNew();
 
	myKernel.term.print(&myKernel.term, WELCOME1);
	myKernel.term.print(&myKernel.term, WELCOME2);
}
