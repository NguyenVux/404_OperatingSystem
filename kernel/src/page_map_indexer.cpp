#include "paging/page_map_indexer.h"
PageMapIndexer::PageMapIndexer(void* _virtualAddress) 
{
    uint64_t virtualAddress = (uint64_t)_virtualAddress;
    virtualAddress >>= 12;
    P_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    PT_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    PD_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    PDP_i = virtualAddress & 0x1ff;
}
