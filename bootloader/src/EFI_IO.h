#ifndef _EFIIO_H
#define _EFIIO_H
#include <efi.h>
#include <efilib.h>


#define HEX 0
#define BIN 1
#define DEC 2


extern CHAR16 buffer[1024];
extern CHAR16* num_table;
extern CHAR16* to_string(uint64_t input,int format);

#endif