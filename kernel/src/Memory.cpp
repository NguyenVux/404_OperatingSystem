#include "Memory.h"

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

void* memset(void* base,uint8_t value, uint64_t size) 
{
    char* _base = (char*)base;
    for(uint64_t i = 0; i < size; ++i)
    {
        _base[i] = value;
    }
    return base;
}

void* memcpy(void* dest,const void* src, uint64_t size) 
{
    char* _dest = (char*)dest;
    const char* _src = (char*)src;
    for(uint64_t i = 0; i < size; ++i)
    {
        *_dest = *_src;
        _dest++;
        _src++;
    }
    return dest;   
}