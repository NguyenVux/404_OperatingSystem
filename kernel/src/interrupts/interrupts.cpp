#include "interrupts/interrupts.h"
__attribute__((interrupt)) void PageFault_handler(struct interrupt_frame* frame) 
{
	stdout << endl << "Page fault you mother fucker" << endl;
	while(1);
}
