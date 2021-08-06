#include "GraphicDriver\graphic.h"
#include "stddef.h"
#include "stdint.h"
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
	EFI_MEMORY_DESCRIPTOR *map;
	uint64_t mMap_size;
	uint64_t Descriptor_size;
};



extern "C" int _start(BootInfo bootInfo)
{
	uint64_t* pixel = (uint64_t*)bootInfo.buffer->Base_Adrress;
	uint64_t maxpx = bootInfo.buffer->height*bootInfo.buffer->Pixel_per_ScaneLine;
	for(uint64_t i = 0; i <maxpx/2;++i)
	{
		*pixel = 0xffffffffffffffff;
		pixel++;
	}
	asm("hlt");
	return 1;
}