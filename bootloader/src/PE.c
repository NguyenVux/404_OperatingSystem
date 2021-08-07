#include "PE.h"
#include "EFI_IO.h"


char reloc_section_name[] = {0x2E, 0x72, 0x65, 0x6C, 0x6F, 0x63, 0x00, 0x00}; // .reloc in ascii


IMGSECTION_HEADER* Read_section_header(
					EFI_FILE* pe,
					int section_count,
					EFI_HANDLE ImageHandle,
					EFI_SYSTEM_TABLE* ST)
{
	IMGSECTION_HEADER* arr;
	uint64_t size = sizeof(IMGSECTION_HEADER);
	ST->BootServices->AllocatePool(EfiLoaderData,size*section_count,(void**)&arr);
	for(int i = 0; i < section_count;++i)		
	{
		pe->Read(pe,&size,&arr[i]);
	}
	return arr;
}
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
	Pe32OptionalHeader Optional_header;
	{
		UINTN size =sizeof(Optional_header);
		pe_file->Read(pe_file,&size,&Optional_header);
	}
	if(Optional_header.mMagic != PE_OPT_SIG)
	{
		return 0;
	}


	uint64_t next_segment = 0;
	pe_file->GetPosition(pe_file,&next_segment);
	next_segment += PEheader.mSizeOfOptionalHeader-sizeof(Optional_header);
	pe_file->SetPosition(pe_file,next_segment);

	IMGSECTION_HEADER *imgHeader = Read_section_header(pe_file,PEheader.mNumberOfSections,ImageHandle,SystemTable);



	uint64_t pages = Optional_header.mSizeOfImage / 0x1000;
	uint64_t addr = 0;
	ST->BootServices->AllocatePages(AllocateAnyPages,EfiLoaderData,pages,&addr);
	void* reloc_table;
	for(int i = 0; i < PEheader.mNumberOfSections;++i)		
	{
		uint64_t size = imgHeader[i].mSizeOfRawData;
		pe_file->SetPosition(pe_file,imgHeader[i].mPointerToRawData);
		void* section_base = (void*)(addr+imgHeader[i].mVirtualAddress);
		pe_file->Read(pe_file,&size,section_base);
		if(*(uint64_t*)imgHeader[i].mName == *(uint64_t*)reloc_section_name)
		{
			reloc_table = section_base;
		}
	}
	uint64_t delta = addr-Optional_header.mImagebase;
	reloc_block* block = (reloc_block*)reloc_table;
	while(block->page_RVA != 0x000)
	{
		RELOC_ENTRY* entry =  (RELOC_ENTRY*)((uint64_t)block + 8);
		// 8 size size of block header the
		// the blockSize element in reloc_block is include block size header (in bytes)
		uint64_t entries_count = (block->blockSize-8)/sizeof(RELOC_ENTRY); 
		for(uint64_t i = 0; i < entries_count; ++i)
		{
			if(entry[i].type == IMAGE_REL_BASED_DIR64)
			{
				uint64_t* location = (uint64_t*)(addr+block->page_RVA+entry[i].page_rva_offset);
				*location+= delta;
			}
		}
		block = (reloc_block*)((uint64_t)block+ block->blockSize);

	}
	pe_file->Close(pe_file);
	return addr+Optional_header.mAddressOfEntryPoint;
}


