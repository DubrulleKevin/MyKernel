#include "mykernel.h"

	
MyKernel myKernelNew(void) {
	MyKernel myKernel;
	
	myKernel.console = myKernelConsoleNew(COM1);
	
	return myKernel;
}
