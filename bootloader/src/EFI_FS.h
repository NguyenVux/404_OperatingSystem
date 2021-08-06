#ifndef _EFIFS_H
#define _EFIFS_H
#include "efi.h"
#include "efilib.h"
#include <stddef.h>
#include <stdint.h>

#define IN
#define OUT
extern EFI_FILE* 
	Load_file(
		IN EFI_FILE* directory ,
		IN CHAR16* PATH,
		IN EFI_HANDLE ImageHandle,
		IN EFI_SYSTEM_TABLE *SystemTable
		);


#endif