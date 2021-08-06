#include "Graphic\graphic.h"
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
	uint32_t* pixel = (uint32_t*)bootInfo.buffer->Base_Adrress;
	uint64_t maxpx = bootInfo.buffer->height*bootInfo.buffer->Pixel_per_ScaneLine;
	uint32_t color = 0x00ffff;
	//for(color = 0; color  < 0xffffffff;color += 0xf)
	while(color > 0xff)
	{
		for(uint64_t i = 0; i <maxpx;++i)
		{	
			pixel[i] = color;
		}
		color--;
	}
	return color;
}
