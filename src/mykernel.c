#include "mykernel.h"

	
MyKernel myKernelNew(void) {
	MyKernel myKernel;
	myKernel.term = myKernelTermNew();
	
	return myKernel;
}
