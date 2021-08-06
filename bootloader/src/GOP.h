#ifndef _GOP_H
#define _GOP_H
#include <stddef.h>
#include <stdint.h>
#include <efi.h>
#include <efilib.h>


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

#endif