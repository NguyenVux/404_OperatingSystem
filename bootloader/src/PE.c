#include "PE.h"
#include "EFI_IO.h"
#ifndef test
uint64_t LoadPE(
		EFI_FILE* directory,
		CHAR16* PATH,
		EFI_HANDLE ImageHandle,
		EFI_SYSTEM_TABLE *SystemTable) 
{
	
	EFI_SYSTEM_TABLE* ST = SystemTable;
	EFI_FILE* pe_file = Load_file(directory,PATH,ImageHandle,SystemTable);
	
	if(pe_file == NULL)
	{
		ST->ConOut->OutputString(ST->ConOut, L"\r\nFile not found");
		 return 0;
	}
	
	EFI_IMAGE_DOS_HEADER header;
	{
		UINTN size =sizeof(header);
		pe_file->Read(pe_file,&size,&header);
	}
	if(header.e_magic != DOS_MZ_SIG)
	{
		return 0;
	}
	ST->ConOut->OutputString(ST->ConOut, L"\r\nPE header location: 0x");
	ST->ConOut->OutputString(ST->ConOut, to_string(header.PE_start_addr,HEX));
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
	pe_file->SetPosition(pe_file,header.PE_start_addr);
	PeHeader PEheader;
	{
		UINTN size =sizeof(PEheader);
		pe_file->Read(pe_file,&size,&PEheader);
	}
	if(PEheader.mMagic != PE_SIG || PEheader.mMachine != EFI_IMAGE_MACHINE_X64)
	{
		return 0;
	}
	ST->ConOut->OutputString(ST->ConOut, L"\r\nPE header magic: 0x");
	ST->ConOut->OutputString(ST->ConOut, to_string(PEheader.mMagic,HEX));
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
	Pe32OptionalHeader Optional_header;
	{
		UINTN size =sizeof(Optional_header);
		pe_file->Read(pe_file,&size,&Optional_header);
	}
	
	ST->ConOut->OutputString(ST->ConOut, L"\r\nPE 32 header magic: 0x");
	ST->ConOut->OutputString(ST->ConOut, to_string(Optional_header.mMagic,HEX));
        ST->ConOut->OutputString(ST->ConOut, L"\r\n");
	if(Optional_header.mMagic != PE_OPT_SIG)
	{
		return 0;
	}


	uint64_t pages = Optional_header.mSizeOfImage / 0x1000;
	uint64_t addr = 0;
	ST->BootServices->AllocatePages(AllocateAnyPages,EfiLoaderData,pages,&addr);

	uint64_t next_segment = 0;
	pe_file->GetPosition(pe_file,&next_segment);
	next_segment += PEheader.mSizeOfOptionalHeader-sizeof(Optional_header);
	pe_file->SetPosition(pe_file,next_segment);
	IMAGE_SECTION_HEADER imgHeader;
	for(int i = 0; i < PEheader.mNumberOfSections;++i)
	{
		uint64_t size = sizeof(imgHeader);
		pe_file->Read(pe_file,&size,&imgHeader);
		next_segment+= size;
		pe_file->SetPosition(pe_file,imgHeader.mPointerToRawData);
		uint64_t data_size = imgHeader.mSizeOfRawData;
		pe_file->Read(pe_file,&data_size,(void*)(addr+imgHeader.mVirtualAddress));
		pe_file->SetPosition(pe_file,next_segment);
	}
	pe_file->Close(pe_file);
	return addr+Optional_header.mAddressOfEntryPoint;
}
#endif


