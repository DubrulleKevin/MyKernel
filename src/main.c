#include <stddef.h>

#include "mykernel.h"

size_t strlen(const char* s) {
	size_t i = 0;

	while (s[i] != '\0') {
		i++;
	}

	return i;
}

int strcmp(const char* a, const char* b) {
	size_t i, j;

	for (i = 0; i < strlen(a); i++) {
		for (j = 0; j < strlen(b); j++) {
			if (a[i] != b[j]) {
				return 1;
			}
		}
	}

	return 0;
}

void kernel_main()
{
	MyKernel myKernel = myKernelNew();
	MyKernelConsole* console = &myKernel.console;
 
	console->puts(console, WELCOME1);
	console->puts(console, WELCOME2);
}
