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
	PageTable* PML4;
	PageTableManager pTManager(PML4);
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
		<< "kernel Base: " << (uint64_t)bootInfo.kernel_base << endl;
	stdout.flush();
}
