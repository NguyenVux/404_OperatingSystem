#ifndef __KERNELUTIL_H__
#define __KERNELUTIL_H__
#include "stddef.h"
#include "stdint.h"
#include "Memory.h"
#include "stdout.h"
#include "paging/page_frame_allocator.h"
#include "paging/page_table_manager.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "pic/pic.h"
#include "gdt/gdt.h"
struct BootInfo
{
	FrameBuffer *buffer;
	PSF1_FONT *font;
	void *map;
	uint64_t mMap_size;
	uint64_t Descriptor_size;
	uint64_t kernel_size;
	void *kernel_base;
};
extern void init_kernel(BootInfo* bootInfo);
//extern void init_memory(BootInfo* bootInfo);
extern void init_idt();
extern void remapPIC();
#endif // __KERNELUTIL_H__