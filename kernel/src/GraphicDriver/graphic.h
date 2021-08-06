#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
#include <stddef.h>
#include <stdint.h>
struct FrameBuffer{
	void* Base_Adrress;
	size_t Buffer_Size;
	unsigned int width;
	unsigned int height;
	unsigned int Pixel_per_ScaneLine;
} ;
#endif // __GRAPHIC_H__