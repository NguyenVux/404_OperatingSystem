#include "stddef.h"
#include "stdint.h"
#include "Memory.h"
#include "stdout.h"
#include "page_frame_allocator.h"
#include "page_table_manager.h"
extern "C" int _fltused = 0;

struct BootInfo
{
	FrameBuffer* buffer;
	PSF1_FONT* font;
	void *map;
	uint64_t mMap_size;
	uint64_t Descriptor_size;
	uint64_t kernel_size;
    	void* kernel_base;
};

BootInfo Boot_info;

Stdout stdout;
extern "C" void _start(BootInfo bootInfo)
{
	char a[]="TEST";
	Console console;
	console.init(bootInfo.buffer,bootInfo.font);
	stdout.init(&console,0xffffffff);
	gPageFrameAllocator.init();
	gPageFrameAllocator.ReadEFIMemory(
		(EFI_MEMORY_DESCRIPTOR*)bootInfo.map,
		bootInfo.mMap_size,
		bootInfo.Descriptor_size,bootInfo.kernel_size,(void*)bootInfo.kernel_base);
	int segment_count = bootInfo.mMap_size/bootInfo.Descriptor_size;
	uint64_t memory_size;
	stdout << "Free memory size:"<< gPageFrameAllocator.getFreeMemory()/1024 << " KB\r\n"
		<< "Used memory: " << (gPageFrameAllocator.getUsedMemory()/1024)<<" KB\r\n"
		<< "Reserved size:" <<gPageFrameAllocator.getReservedMemory()/1024 << "KB"<<"\r\n"
		<< "kernel Base: " << (uint64_t)bootInfo.kernel_base << endl
		<< "buffer base:" <<(uint64_t)bootInfo.buffer->Base_Adrress <<endl;
	stdout << "HELLO" << endl;
	uint64_t size = GetMemorySize((EFI_MEMORY_DESCRIPTOR*)bootInfo.map,
		bootInfo.mMap_size/bootInfo.Descriptor_size,
		bootInfo.Descriptor_size);
	PageTable* PML4;
	stdout << "HELLO" << endl;
	PageTableManager pTManager(PML4);
	PML4 = (PageTable*)gPageFrameAllocator.requestPage();
	memset(PML4, 0, 0x1000);
	for(uint64_t t = 0; t < size; t +=0x1000)
	{
		pTManager.MapMemory((void*)t,(void*)t);
	}
	stdout << "HELLO" << endl;
	// uint64_t base = (uint64_t)bootInfo.buffer->Base_Adrress;
	// uint64_t bsize = bootInfo.buffer->Buffer_Size;
	// for(uint64_t t = base; t < base+bsize;t+=0x1000)
	// {
	// 	pTManager.MapMemory((void*)t,(void*)t);
	// }
	asm("mov %0,%%cr3" : :"r"(PML4));
	// stdout << "HELLO" << endl;
	// stdout.flush();
	while(1){}
}
