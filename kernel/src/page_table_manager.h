#ifndef __PAGE_TABLE_MANAGER_H__
#define __PAGE_TABLE_MANAGER_H__
#include <stddef.h>
#include <stdint.h>
#include "page_frame_allocator.h"
#include "Memory.h"
#include "page_map_indexer.h"
struct PageDirectoryEntry {
    bool Present : 1;
    bool ReadWrite : 1;
    bool UserSuper : 1;
    bool WriteThrough : 1;
    bool CacheDisabled : 1;
    bool Accessed : 1;
    bool ignore0 : 1; 
    bool LargerPages : 1;
    bool ingore1 : 1;
    uint8_t Available : 3;
    uint64_t Address : 52;
};

struct PageTable { 
    PageDirectoryEntry entries [512];
}__attribute__((aligned(0x1000)));


class PageTableManager {
    public:
    PageTableManager(PageTable* PML4Address);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory);
};
#endif // __PAGE_TABLE_MANAGER_H__