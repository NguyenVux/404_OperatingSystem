#ifndef __IDT_H__
#define __IDT_H__
#include <stdint.h>


#define IDT_TA_InterruptGate 	0b10001110
#define IDT_TA_CallGate 	0b10001100
#define IDT_TA_TrapGate 	0b10001111
struct IDT_ENTRY
{
	uint16_t offset0;
	uint16_t selector;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset1;
	uint32_t offset2;
	uint32_t ignore;
	void Set_offset(uint64_t offset);
	uint64_t Get_offset();
};




struct IDTR
{
	uint16_t limit;
	uint64_t offset;
} __attribute__((packed));

extern IDTR gIdtr;

#endif // __IDT_H__