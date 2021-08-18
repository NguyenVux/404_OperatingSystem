#include "kernelUtil.h"

extern "C" int _fltused = 0;
void init_kernel(BootInfo* bootInfo) 
{
	console.init(bootInfo->buffer, bootInfo->font);
	stdout.init(&console, 0xffffffff);
	gPageFrameAllocator.init();
	gPageFrameAllocator.ReadEFIMemory(
	    (EFI_MEMORY_DESCRIPTOR *)bootInfo->map,
	    bootInfo->mMap_size,
	    bootInfo->Descriptor_size, bootInfo->kernel_size, (void *)bootInfo->kernel_base);
	uint64_t size = GetMemorySize((EFI_MEMORY_DESCRIPTOR *)bootInfo->map,
				      bootInfo->mMap_size / bootInfo->Descriptor_size,
				      bootInfo->Descriptor_size);
	PML4 = (PageTable*)gPageFrameAllocator.requestPage();
	memset(PML4, 0, 0x1000);
	gPageTableManager = PageTableManager(PML4);
	uint64_t s = (uint64_t)GetMemorySize((EFI_MEMORY_DESCRIPTOR*)bootInfo->map, bootInfo->mMap_size/bootInfo->Descriptor_size, bootInfo->Descriptor_size);
	for (uint64_t t = 0; t < size; t += 0x1000)
	{
		gPageTableManager.MapMemory((void *)t, (void *)t);
	}
	uint64_t fbBase = (uint64_t)bootInfo->buffer->Base_Adrress;
	uint64_t fbSize = (uint64_t)bootInfo->buffer->Buffer_Size + 0x1000;
	for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096)
	{
		gPageTableManager.MapMemory((void *)t, (void *)t);
	}
	
	GDTDescriptor gdtp;
	gdtp.Size = sizeof(DefaultGDT) -1;
	gdtp.Offset = (uint64_t)&DefaultGDT;
	LoadGDT(&gdtp);
	asm("mov %0, %%cr3"
	    :
	    : "r"(PML4));
	init_idt();
}

#define IDT_TA_InterruptGate 	0b10001110
#define IDT_TA_CallGate 	0b10001100
#define IDT_TA_TrapGate 	0b10001111
void init_idt() 
{
	gIdtr.limit = 0x0fff;
	gIdtr.offset = (uint64_t)gPageFrameAllocator.requestPage();
	IDT_ENTRY* interrupt_pageFault = (IDT_ENTRY*)(gIdtr.offset+0xE*sizeof(IDT_ENTRY));
	interrupt_pageFault->Set_offset((uint64_t)PageFault_handler);
	interrupt_pageFault->type_attr = IDT_TA_InterruptGate;
	interrupt_pageFault->selector = 0x08;

	asm("lidt %0" : :"m"(gIdtr));
}
