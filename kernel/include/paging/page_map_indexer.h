#ifndef _PAGE_MAP_INDEXER_H
#define _PAGE_MAP_INDEXER_H
#include <stdint.h>
#include "404OSdef.h"
class PageMapIndexer {
    public:
        PageMapIndexer(void* virtualAddress);
        uint64_t PDP_i;
        uint64_t PD_i;
        uint64_t PT_i;
        uint64_t P_i;
};
#endif