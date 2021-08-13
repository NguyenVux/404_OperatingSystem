#include "bitmap.h"


void BITMAP::init(uint8_t* location,uint64_t size) 
{
	Buffer = location;
	this->Size = size;
	uint64_t *arr = (uint64_t*) Buffer;
	for(uint64_t i =0; i < size;++i)
	{
		arr[i] = 0;
	}
}

bool BITMAP::operator[](uint64_t index) 
{
	uint64_t _index = index/8;
	uint8_t offset = 0b10000000 >> index%8; // shift mask bit to right locaiton
	return Buffer[_index]&offset;	
}

void BITMAP::set(uint64_t index,uint8_t value) 
{
	uint64_t _index = index/8;
	uint8_t offset = 0b10000000 >> index%8; // shift mask bit to right locaiton
	Buffer[_index]^=offset;	//xor to set bit at offset and index;
}
