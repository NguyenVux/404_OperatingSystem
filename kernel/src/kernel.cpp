#include "kernelUtil.h"
#include "gdt/gdt.h"




extern "C" void _start(BootInfo bootInfo)
{
	char a[] = "TEST";
	int segment_count = bootInfo.mMap_size / bootInfo.Descriptor_size;
	init_kernel(&bootInfo);
	uint64_t memory_size;
	stdout << "packed size: " << sizeof(GDT_ENTRY) << endl;
}
