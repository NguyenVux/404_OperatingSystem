#ifndef __PAGE_TABLE_MANAGER_H__
#define __PAGE_TABLE_MANAGER_H__
#include <stddef.h>
#include <stdint.h>
#include "page_frame_allocator.h"
#include "Memory.h"
#include "page_map_indexer.h"
struct PageDirectoryEntry {
    uint64_t Present : 1;
    uint64_t ReadWrite : 1;
    uint64_t UserSuper : 1;
    uint64_t WriteThrough : 1;
    uint64_t CacheDisabled : 1;
    uint64_t Accessed : 1;
    uint64_t ignore0 : 1; 
    uint64_t LargerPages : 1;
    uint64_t ingore1 : 1;
    uint64_t Available : 3;
    uint64_t Address : 52;
};

struct alignas(0x1000) PageTable { 
    PageDirectoryEntry entries [512];
};
// }__attribute__((aligned(0x1000)));


class PageTableManager {
    public:
    PageTableManager(){}
    PageTableManager(PageTable* PML4Address);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory);
};


extern PageTable *PML4;
extern PageTableManager gPageTableManager;
#endif // __PAGE_TABLE_MANAGER_H__