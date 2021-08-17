#include "kernelUtil.h"
#include "gdt/gdt.h"




extern "C" void _start(BootInfo bootInfo)
{
	char a[] = "TEST";
	int segment_count = bootInfo.mMap_size / bootInfo.Descriptor_size;
	init_kernel(&bootInfo);
	uint64_t memory_size;
	GDTDescriptor gdtp;
	gdtp.Size = sizeof(GDT) -1;
	gdtp.Offset = (uint64_t)&DefaultGDT;
	stdout <<"Kernel: " << (uint64_t)&gdtp << endl;
	stdout << "packed size: " << sizeof(GDTEntry) << endl;
	stdout << "packed size: " << sizeof(GDTDescriptor) << endl;
	while(1){};
}
