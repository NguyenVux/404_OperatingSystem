#include "stddef.h"
#include "stdint.h"
#include "efiMemory.h"
#include "stdout.h"
#include "page_frame_allocator.h"
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
	PageFrameAllocator page_frame_allocator;
	console.init(bootInfo.buffer,bootInfo.font);
	stdout.init(&console,0xffffffff);
	page_frame_allocator.ReadEFIMemory(
		(EFI_MEMORY_DESCRIPTOR*)bootInfo.map,
		bootInfo.mMap_size,
		bootInfo.Descriptor_size,bootInfo.kernel_size,(void*)bootInfo.kernel_base);
	int segment_count = bootInfo.mMap_size/bootInfo.Descriptor_size;
	stdout << "Free memory size:"<< page_frame_allocator.getFreeMemory()/1024 << " KB\r\n"
		<< "Used memory: " << (page_frame_allocator.getUsedMemory()/1024)<<" KB\r\n"
		<< "Reserved size:" <<page_frame_allocator.getReservedMemory()/1024 << "KB"<<"\r\n"
		<< "kernel Base: " << (uint64_t)bootInfo.kernel_base << endl;
	stdout.flush();
}
