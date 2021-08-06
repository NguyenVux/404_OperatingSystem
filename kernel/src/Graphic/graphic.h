#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
#include <stddef.h>
#include <stdint.h>

#define PSF_MAGIC 0x436

typedef struct{
	unsigned short magic;
	unsigned char mode;
	unsigned char charsize;
} PSF1_HEADER;


typedef struct{
	PSF1_HEADER* PSF1_HEADERl;
	void* glyph_BUFFER;
} PSF1_FONT;

struct FrameBuffer{
	void* Base_Adrress;
	size_t Buffer_Size;
	unsigned int width;
	unsigned int height;
	unsigned int Pixel_per_ScaneLine;
	int pixel_mode;
} ;
#endif // __GRAPHIC_H__