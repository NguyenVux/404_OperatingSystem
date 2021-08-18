#include "interrupts/interrupts.h"
__attribute__((interrupt)) void PageFault_handler(struct interrupt_frame* frame) 
{
	console.setCursor(0,0);
	console.clear(0x00ff0000);
	stdout << endl << "Page fault you mother fucker" << endl;
	while(1);
}
