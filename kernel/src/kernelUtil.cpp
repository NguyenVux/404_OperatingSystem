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
	asm("mov %0, %%cr3"
	    :
	    : "r"(PML4));
}
