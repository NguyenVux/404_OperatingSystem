#include "interrupts/IDT.h"



void IDT_ENTRY::Set_offset(uint64_t offset) 
{
	offset0 = (uint16_t)(offset & 0xffff);
	offset1 = (uint16_t)((offset >> 16) & 0xffff);
	offset2 = (uint32_t)((offset >> 32 )& 0xffffffff);
}


uint64_t IDT_ENTRY::Get_offset() 
{
	uint64_t result = 0;
	result |= (uint64_t)offset0; 
	result |= (uint64_t)offset1<<16; 
	result |= (uint64_t)offset0<<32; 
	return result;
}

IDTR gIdtr = {0,0};