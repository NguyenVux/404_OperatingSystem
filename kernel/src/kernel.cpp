#include "stdout.h"
#include "stddef.h"
#include "stdint.h"
#include "efiMemory/efiMemory.h"
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

extern "C" void _start(BootInfo bootInfo)
{
	char a[]="TEST";
	Console console;
	Stdout stdout;
	Boot_info.buffer = bootInfo.buffer;
	Boot_info.font = bootInfo.font;
	Boot_info.map = bootInfo.map;
	Boot_info.mMap_size = bootInfo.mMap_size;
	Boot_info.Descriptor_size = bootInfo.Descriptor_size;
	console.init(bootInfo.buffer,bootInfo.font);
	stdout.init(&console);
	int segment_count = Boot_info.mMap_size/Boot_info.Descriptor_size;
	stdout << "descriptor size:" << Boot_info.Descriptor_size << "\r\n";
	stdout << "Map size:" << Boot_info.mMap_size << "- address:" << EFI_MEMORY_TYPE_STRINGS[0] <<"\r\n";
	stdout.flush();
	EFI_MEMORY_DESCRIPTOR *ptr = (EFI_MEMORY_DESCRIPTOR*)Boot_info.map;
	const char* string= EFI_MEMORY_TYPE_STRINGS[0];
	for(int i=0; i < segment_count; ++i)
	{
		stdout << ptr->Type << "\r\n";
		stdout.flush();
		ptr = ((EFI_MEMORY_DESCRIPTOR*)(uint64_t)ptr+Boot_info.Descriptor_size);
	}
	stdout << "finish"; stdout.flush();
}
