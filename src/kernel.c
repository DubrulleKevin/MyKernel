#include "kernel.h"

	
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
