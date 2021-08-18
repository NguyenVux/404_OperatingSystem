#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stddef.h>
#include <stdint.h>

class BITMAP
{
	public:
	uint8_t* Buffer;
	uint64_t Size;
	void init(uint8_t* buffer_addr,uint64_t size);
	bool operator[](uint64_t index);
	void set(uint64_t index,uint8_t value);
};


#endif