#ifndef _GOP_H
#define _GOP_H
#include <stddef.h>
#include <stdint.h>
#include <efi.h>
#include <efilib.h>
#include "EFI_FS.h"

#define IN
#define OUT

typedef struct{
	void* Base_Adrress;
	size_t Buffer_Size;
	unsigned int width;
	unsigned int height;
	unsigned int Pixel_per_ScaneLine;
	int pixel_mode;
} FrameBuffer;
extern int init_GOP(
				IN EFI_HANDLE ImageHandle,
				IN EFI_SYSTEM_TABLE *SystemTable,
				OUT FrameBuffer* fBuffer
				);




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
extern 
PSF1_FONT* Load_font(
				EFI_FILE* directory,
				CHAR16* PATH,
				EFI_HANDLE ImageHandle,
				EFI_SYSTEM_TABLE *SystemTable
				);
#endif