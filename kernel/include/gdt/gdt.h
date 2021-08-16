#ifndef __GDT_H__
#define __GDT_H__

#include <stdint.h>
#include <404OSdef.h>
struct GDT_ENTRY
{
	uint16_t Limit0;
	uint16_t Base0;
	uint8_t Base1;
	uint8_t AccessByte;
	uint8_t Limit1_Flags;
	uint8_t Base2;
}__attribute__((packed));


struct GDT_descriptor
{
	uint16_t Size;
    	uint64_t Offset;
}__attribute__((packed));

struct GDT {
    GDT_ENTRY Null; //0x00
    GDT_ENTRY KernelCode; //0x08
    GDT_ENTRY KernelData; //0x10
    GDT_ENTRY UserNull;
    GDT_ENTRY UserCode;
    GDT_ENTRY UserData;
}__attribute__((packed));


extern GDT DefaultGDT;

extern "C" void LoadGDT(GDT_descriptor* gdtDescriptor);
#endif // __GDT_H__