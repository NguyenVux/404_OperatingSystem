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
    console.clear(0);
	stdout <<"Kernel: " << (uint64_t)&gdtp << endl;
	stdout << "packed size: " << sizeof(GDTEntry) << endl;
	stdout << "packed size: " << sizeof(GDTDescriptor) << endl;
	stdout << "pixel mode: " << bootInfo.buffer->pixel_mode << endl;
	stdout << "buffer size: " << bootInfo.buffer->Buffer_Size << endl;
	stdout << "pixel perline: " << bootInfo.buffer->Pixel_per_ScaneLine << endl;
	stdout << "height: " << bootInfo.buffer->height << endl;
	//asm("int $0xe");
	//console.clear(0);
	while(1){};
}
