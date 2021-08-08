#ifndef __EFIMEMORY_H__
#define __EFIMEMORY_H__
#include <stddef.h>
#include <stdint.h>
extern const char* EFI_MEMORY_TYPE_STRINGS[];
struct EFI_MEMORY_DESCRIPTOR{
    uint32_t                          Type;           // Field size is 32 bits followed by 32 bit pad
    void* physical_addr;
    void* virtual_addr;
    uint64_t numpages;
    uint64_t attribs;
};

extern uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR*,uint64_t entries,uint64_t descriptor_size);
#endif // __EFIMEMORY_H__