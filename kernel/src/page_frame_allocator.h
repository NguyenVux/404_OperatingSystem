#ifndef __PAGE_FRAME_ALLOCATOR_H__
#define __PAGE_FRAME_ALLOCATOR_H__
#include <stddef.h>
#include <stdint.h>
#include "efiMemory.h"
#include "bitmap.h"
#include "stdout.h"


#define EFI_CONVENTIONAL_MEMORY 7
class PageFrameAllocator
{
private:
	bool initialize =false;
	uint64_t freeMemory =0 ;
	uint64_t reservedMemory = 0;
	uint64_t usedMemory = 0;
	BITMAP page_bitmap;
	void FreePage(void* addr);
	void LockPage(void* addr);
	void FreePages(void* addr,uint64_t count);
	void LockPages(void* addr,uint64_t count);
public:
	PageFrameAllocator();
	void ReadEFIMemory(EFI_MEMORY_DESCRIPTOR* mMap,size_t mapSize,size_t DescriptorSize,uint64_t kernel_size,void* kernel_base);
	void ReservePage(void* addr);
	void unReservePage(void* addr);
	void ReservePages(void* addr,uint64_t count);
	void unReservePages(void* addr,uint64_t count);
	uint64_t getFreeMemory();
	uint64_t getReservedMemory();
	uint64_t getUsedMemory();

};





#endif // __PAGE_FRAME_ALLOCATOR_H__