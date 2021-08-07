#ifndef _EFIIO_H
#define _EFIIO_H
#include <efi.h>
#include <efilib.h>


#define HEX 0
#define BIN 1
#define DEC 2


extern CHAR16 buffer[2048];
extern CHAR16* num_table;
extern CHAR16* char8to16;
extern CHAR16* to_string(uint64_t input,int format);
extern CHAR16* CHAR16TO18(char* t);

#endif