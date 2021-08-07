#ifndef _PE_H
#define _PE_H

#define PE_SIG 0x00004550
#define PE_OPT_SIG 0x20B
#define DOS_MZ_SIG 0x5A4D
#include <stdint.h>
#include "EFI_FS.h"
typedef struct {
   uint16_t  e_magic;    ///< Magic number.
   uint16_t  e_cblp;     ///< Bytes on last page of file.
   uint16_t  e_cp;       ///< Pages in file.
   uint16_t  e_crlc;     ///< Relocations.
   uint16_t  e_cparhdr;  ///< Size of header in paragraphs.
   uint16_t  e_minalloc; ///< Minimum extra paragraphs needed.
   uint16_t  e_maxalloc; ///< Maximum extra paragraphs needed.
   uint16_t  e_ss;       ///< Initial (relative) SS value.
   uint16_t  e_sp;       ///< Initial SP value.
   uint16_t  e_csum;     ///< Checksum.
   uint16_t  e_ip;       ///< Initial IP value.
   uint16_t  e_cs;       ///< Initial (relative) CS value.
   uint16_t  e_lfarlc;   ///< File address of relocation table.
   uint16_t  e_ovno;     ///< Overlay number.
   uint16_t  e_res[4];   ///< Reserved words.
   uint16_t  e_oemid;    ///< OEM identifier (for e_oeminfo).
   uint16_t  e_oeminfo;  ///< OEM information; e_oemid specific.
   uint16_t  e_res2[10]; ///< Reserved words.
   uint32_t  PE_start_addr;   ///< File address of new exe header.
 } EFI_IMAGE_DOS_HEADER;

typedef struct {
	uint32_t mMagic; // PE\0\0 or 0x00004550
	uint16_t mMachine;
	uint16_t mNumberOfSections;
	uint32_t mTimeDateStamp;
	uint32_t mPointerToSymbolTable;
	uint32_t mNumberOfSymbols;
	uint16_t mSizeOfOptionalHeader;
	uint16_t mCharacteristics;
} PeHeader;
typedef struct {
	uint16_t mMagic; // 0x010b - PE32, 0x020b - PE32+ (64 bit)
	uint8_t  mMajorLinkerVersion;
	uint8_t  mMinorLinkerVersion;
	uint32_t mSizeOfCode;
	uint32_t mSizeOfInitializedData;
	uint32_t mSizeOfUninitializedData;
	uint32_t mAddressOfEntryPoint;
	uint32_t mBaseOfCode;
	uint64_t mImagebase;
	uint32_t mSectionAlignment;
	uint32_t mFileAlignment;
	uint16_t mMajorOperatingSystemVersion;
	uint16_t mMinorOperatingSystemVersion;
	uint16_t mMajorImageVersion;
	uint16_t mMinorImageVersion;
	uint16_t mMajorSubsystemVersion;
	uint16_t mMinorSubsystemVersion;
	uint32_t mWin32VersionValue;
	uint32_t mSizeOfImage;
	uint32_t mSizeOfHeaders;
	uint32_t mCheckSum;
	uint16_t mSubsystem;
	uint16_t mDllCharacteristics;
	uint32_t mSizeOfStackReserve;
	uint32_t mSizeOfStackCommit;
	uint32_t mSizeOfHeapReserve;
	uint32_t mSizeOfHeapCommit;
	uint32_t mLoaderFlags;
	uint32_t mNumberOfRvaAndSizes;
} Pe32OptionalHeader;
typedef struct  {
	char  mName[8];
	uint32_t mVirtualSize;
	uint32_t mVirtualAddress;
	uint32_t mSizeOfRawData;
	uint32_t mPointerToRawData;
	uint32_t mPointerToRelocations;
	uint32_t mPointerToLinenumbers;
	uint16_t mNumberOfRelocations;
	uint16_t mNumberOfLinenumbers;
	uint32_t mCharacteristics;
}IMAGE_SECTION_HEADER;
typedef IMAGE_SECTION_HEADER IMGSECTION_HEADER;















#define IMAGE_REL_BASED_ABSOLUTE 		0
#define IMAGE_REL_BASED_HIGH 			1
#define IMAGE_REL_BASED_LOW 			2
#define IMAGE_REL_BASED_HIGHLOW 		3
#define IMAGE_REL_BASED_HIGHADJ 		4
#define IMAGE_REL_BASED_MIPS_JMPADDR 		5
#define IMAGE_REL_BASED_ARM_MOV32 		5
#define IMAGE_REL_BASED_RISCV_HIGH20 		5 
#define IMAGE_REL_RESERVED 			6 //must be zero
#define IMAGE_REL_BASED_THUMB_MOV32 		7
#define IMAGE_REL_BASED_RISCV_LOW12I 		7
#define IMAGE_REL_BASED_RISCV_LOW12S 		8
#define IMAGE_REL_BASED_MIPS_JMPADDR16 		9
#define IMAGE_REL_BASED_DIR64 			10
typedef struct
{
	uint32_t page_RVA;
	uint32_t blockSize;
}reloc_block;
typedef struct
{
	uint16_t page_rva_offset: 12;
	uint16_t type:4;
}RELOC_ENTRY;

extern char* section_name[];
extern uint64_t LoadPE(
		EFI_FILE* directory,
		CHAR16* PATH,
		EFI_HANDLE ImageHandle,
		EFI_SYSTEM_TABLE *SystemTable
		);
extern int memcmp(void* L,void*R,uint64_t count);
#endif