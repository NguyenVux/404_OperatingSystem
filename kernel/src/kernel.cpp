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
};

BootInfo Boot_info;

Stdout stdout;
extern "C" void _start(BootInfo bootInfo)
{
	char a[]="TEST";
	Console console;
	PageFrameAllocator page_frame_allocator;


	Boot_info.buffer = bootInfo.buffer;
	Boot_info.font = bootInfo.font;
	Boot_info.map = bootInfo.map;
	Boot_info.mMap_size = bootInfo.mMap_size;
	Boot_info.Descriptor_size = bootInfo.Descriptor_size;
	console.init(bootInfo.buffer,bootInfo.font);
	stdout.init(&console,0xffffffff);



	page_frame_allocator.ReadEFIMemory(
		(EFI_MEMORY_DESCRIPTOR*)Boot_info.map,
		Boot_info.mMap_size,
		Boot_info.Descriptor_size);
	int segment_count = Boot_info.mMap_size/Boot_info.Descriptor_size;
	stdout << "Free memory size:"<< page_frame_allocator.getFreeMemory()/1024 << " KB\r\n"
		<< "Used memory: " << (page_frame_allocator.getUsedMemory()/1024)<<" KB\r\n"
		<< "Reserved size:" <<page_frame_allocator.getReservedMemory()/1024 << "KB" << endl;
	stdout.flush();
}
