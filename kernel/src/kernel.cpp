#include "kernelUtil.h"





extern "C" void _start(BootInfo bootInfo)
{
	char a[] = "TEST";
	int segment_count = bootInfo.mMap_size / bootInfo.Descriptor_size;
	init_kernel(&bootInfo);
	uint64_t memory_size;
	stdout << "Free memory size:" << gPageFrameAllocator.getFreeMemory() / 1024 << " KB\r\n"
	       << "Used memory: " << (gPageFrameAllocator.getUsedMemory() / 1024) << " KB\r\n"
	       << "Reserved size:" << gPageFrameAllocator.getReservedMemory() / 1024 << "KB"
	       << "\r\n"
	       << "kernel Base: " << (uint64_t)bootInfo.kernel_base << endl
	       << "buffer base:" << (uint64_t)bootInfo.buffer->Base_Adrress << endl;
	stdout << "HELLO" << endl;
}
