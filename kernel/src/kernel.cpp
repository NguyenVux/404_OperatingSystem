#include "stdout.h"
#include "stddef.h"
#include "stdint.h"

extern "C" int _fltused = 0;
struct EFI_MEMORY_DESCRIPTOR{
    uint32_t                          Type;           // Field size is 32 bits followed by 32 bit pad
    uint32_t                          Pad;
    uint64_t            PhysicalStart;  // Field size is 64 bits
    uint64_t             VirtualStart;   // Field size is 64 bits
    uint64_t                          NumberOfPages;  // Field size is 64 bits
    uint64_t                          Attribute;      // Field size is 64 bits
};
struct BootInfo
{
	FrameBuffer* buffer;
	PSF1_FONT* font;
	EFI_MEMORY_DESCRIPTOR *map;
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
	stdout << "descriptor size:" << Boot_info.Descriptor_size << "\r\n";
	stdout << "Map size:" << Boot_info.mMap_size << "\r\n";
	stdout << "map count size:" << Boot_info.mMap_size/Boot_info.Descriptor_size << "\r\n";
	stdout << "Test float:" << (float)1.25 << "\r\n";
	stdout.flush();
	while (1)
	{
		/* code */
	}
	
}
