#include "mykernelconsole.h"


static void myKernelConsoleOutB(const uint16_t port, const uint8_t value) {
  __asm__ volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

static uint8_t myKernelConsoleInB(const uint16_t port) {
  uint8_t ret;
  __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

static int myKernelConsoleIsTransmitEmpty(const MyKernelConsolePort port) {
   return myKernelConsoleInB(port + 5) & 0x20;
}

static void myKernelConsolePutc(MyKernelConsole *console, const char c) {
	while (myKernelConsoleIsTransmitEmpty(console->port) == 0);
	if (c == '\n') {
		myKernelConsoleOutB(console->port,'\r');
	}
	myKernelConsoleOutB(console->port, c);
}

static void myKernelConsolePuts(MyKernelConsole* console, const char* str) {
	int i = 0;
	
	while (str[i] != '\0') {
		myKernelConsolePutc(console, str[i]);
		i++;
	}
}

static int myKernelConsoleSerialReceived(struct MyKernelConsole* console) {
	return myKernelConsoleInB(console->port + 5) & 1;
}

static char myKernelConsoleGetc(struct MyKernelConsole* console) {
	while (myKernelConsoleSerialReceived(console) == 0);
	
	return myKernelConsoleInB(console->port);
}


MyKernelConsole myKernelConsoleNew(const MyKernelConsolePort port) {
	MyKernelConsole myKernelConsole;
	
	myKernelConsole.putc = &myKernelConsolePutc;
	myKernelConsole.puts = &myKernelConsolePuts;
	myKernelConsole.getc = &myKernelConsoleGetc;
	
	myKernelConsole.port = port;
	
	myKernelConsoleOutB(port + 1, 0x00);
	myKernelConsoleOutB(port + 3, 0x80);
	myKernelConsoleOutB(port + 0, 0x03);
	myKernelConsoleOutB(port + 1, 0x00);
	myKernelConsoleOutB(port + 3, 0x03);
	myKernelConsoleOutB(port + 2, 0xC7);
	myKernelConsoleOutB(port + 4, 0x0B);
	
	myKernelConsolePutc(&myKernelConsole, '\n');
	
	return myKernelConsole;
}
