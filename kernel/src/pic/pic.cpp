#include "pic/pic.h"
void outb(uint16_t port, uint8_t value) 
{
	asm volatile ("outb %0,%1": : "a"(value),"Nd"(port));
}


uint8_t intb(uint16_t port)
{
	uint8_t result = 0;
	asm volatile ("inb %1,%0"
	:"=a"(result)
	:"Nd"(port)
	);
	return result;
}

void iowait()
{
	asm volatile ("outb %%al,$0x80": : "a"(0));
}