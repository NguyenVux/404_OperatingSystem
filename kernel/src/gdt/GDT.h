#ifndef __GDT_H__
#define __GDT_H__
#include <stdint.h>
#include <stddef.h>
struct GDT 
{
	int a;
	uint64_t b;
} __attribute__((packed));
#endif // __GDT_H__