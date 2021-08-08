#include "efiMemory.h"

const char* EFI_MEMORY_TYPE_STRINGS[] = {
    "EfiReservedMemoryType",
    "EfiLoaderCode",
    "EfiLoaderData",
    "EfiBootServicesCode",
    "EfiBootServicesData",
    "EfiRuntimeServicesCode",
    "EfiRuntimeServicesData",
    "EfiConventionalMemory",
    "EfiUnusableMemory",
    "EfiACPIReclaimMemory",
    "EfiACPIMemoryNVS",
    "EfiMemoryMappedIO",
    "EfiMemoryMappedIOPortSpace",
    "EfiPalCode"
};

extern uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* ptr,uint64_t entries,uint64_t descriptor_size) 
{
    static uint64_t byte_size = 0;
    if(byte_size >0) return byte_size;
    for(int i=0; i < entries; ++i)
	{
		byte_size+= ptr->numpages*4096;
		ptr = (EFI_MEMORY_DESCRIPTOR*)((uint8_t*)ptr+descriptor_size);
	}
    return byte_size;
}