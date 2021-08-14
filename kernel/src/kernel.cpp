#include "stddef.h"
#include "stdint.h"
#include "Memory.h"
#include "stdout.h"
#include "page_frame_allocator.h"
#include "page_table_manager.h"
extern "C" int _fltused = 0;

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

BootInfo Boot_info;

Stdout stdout;
extern "C" void _start(BootInfo bootInfo)
{
	char a[] = "TEST";
	Console console;
	console.init(bootInfo.buffer, bootInfo.font);
	stdout.init(&console, 0xffffffff);
	gPageFrameAllocator.init();
	gPageFrameAllocator.ReadEFIMemory(
	    (EFI_MEMORY_DESCRIPTOR *)bootInfo.map,
	    bootInfo.mMap_size,
	    bootInfo.Descriptor_size, bootInfo.kernel_size, (void *)bootInfo.kernel_base);
	int segment_count = bootInfo.mMap_size / bootInfo.Descriptor_size;
	uint64_t memory_size;
	stdout << "Free memory size:" << gPageFrameAllocator.getFreeMemory() / 1024 << " KB\r\n"
	       << "Used memory: " << (gPageFrameAllocator.getUsedMemory() / 1024) << " KB\r\n"
	       << "Reserved size:" << gPageFrameAllocator.getReservedMemory() / 1024 << "KB"
	       << "\r\n"
	       << "kernel Base: " << (uint64_t)bootInfo.kernel_base << endl
	       << "buffer base:" << (uint64_t)bootInfo.buffer->Base_Adrress << endl;
	stdout << "HELLO" << endl;
	uint64_t size = GetMemorySize((EFI_MEMORY_DESCRIPTOR *)bootInfo.map,
				      bootInfo.mMap_size / bootInfo.Descriptor_size,
				      bootInfo.Descriptor_size);
	PageTable *PML4 = (PageTable *)gPageFrameAllocator.requestPage();
	memset(PML4, 0, 0x1000);

	PageTableManager pageTableManager = PageTableManager(PML4);
	uint64_t s = (uint64_t)GetMemorySize((EFI_MEMORY_DESCRIPTOR*)bootInfo.map, bootInfo.mMap_size/bootInfo.Descriptor_size, bootInfo.Descriptor_size);
	stdout << "Memory size: " << s << "BYTE" << endl << "PML4 addr: " << (uint64_t)PML4 << endl;
	for (uint64_t t = 0; t < s; t += 0x1000)
	{
		pageTableManager.MapMemory((void *)t, (void *)t);
	}
	stdout << "finish identity mapping: " << (uint64_t)&(PML4->entries[1]) << endl;
	uint64_t fbBase = (uint64_t)bootInfo.buffer->Base_Adrress;
	uint64_t fbSize = (uint64_t)bootInfo.buffer->Buffer_Size + 0x1000;
	stdout << "Struct size: " << sizeof(PageDirectoryEntry) << endl;
	for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096)
	{
		pageTableManager.MapMemory((void *)t, (void *)t);
	}
	stdout.flush();
	asm("mov %0, %%cr3"
	    :
	    : "r"(PML4));
	pageTableManager.MapMemory((void*)0x100000,(void*)0x15000);
	int* t = (int*)0x100000;
	*t = 20;
	stdout << "TEST" << *t << endl;
}
