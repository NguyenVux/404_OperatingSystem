#include "efi.h"
#include <efilib.h>
#include "GOP.h"
#include "EFI_IO.h"
#include "PE.h"
void  *memset(void *b, int c, int len)
{
  int i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}
void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
    char* a = s1;
    char* b = s2;
    for(size_t i=0; i < n; ++i)
    {
        *a = *b;
        a++;
        b++;
    }
    return s1;
}
int memcmp(void* L,void*R,uint64_t count)
{
    unsigned char* l = (unsigned char*)L;
    unsigned char* r = (unsigned char*)r;
    for(uint64_t i=0; i < count;++i)
    {
        if(*l<*r)
        {
            return -1;
        }
        if(*l>*r)
        {
            return 1;
        }
        l++;
        r++;
    }
    return 0;
}

typedef struct 
{
	FrameBuffer* buffer;
    EFI_MEMORY_DESCRIPTOR* map;
    uint64_t mMap_size;
	uint64_t Descriptor_size;
} BootInfo;

FrameBuffer fBuffer;
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_SYSTEM_TABLE* ST = SystemTable;
    if(init_GOP(ImageHandle,SystemTable,&fBuffer))
    {
	    ST->ConOut->OutputString(ST->ConOut, L"GOP Located \r\n");
	    ST->ConOut->OutputString(ST->ConOut, L"GOP Base: 0x");
	    ST->ConOut->OutputString(ST->ConOut, to_string(fBuffer.Base_Adrress,HEX));
	    ST->ConOut->OutputString(ST->ConOut, L"\r\nScreen height: ");
	    ST->ConOut->OutputString(ST->ConOut, to_string(fBuffer.height,DEC));
	    ST->ConOut->OutputString(ST->ConOut, L"\r\nScreen Width: ");
	    ST->ConOut->OutputString(ST->ConOut, to_string(fBuffer.width,DEC));
	    ST->ConOut->OutputString(ST->ConOut, L"\r\nPixel per line: ");
	    ST->ConOut->OutputString(ST->ConOut, to_string(fBuffer.Pixel_per_ScaneLine,DEC));
        Status = ST->ConOut->OutputString(ST->ConOut, L"\r\n");
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"GOP Located Failed\r\n");
    }
    uint64_t start_ddr = LoadPE(NULL,L"404OS\\kernel.sys",ImageHandle,ST);
    BootInfo Bootinfo;
    Bootinfo.buffer = &fBuffer;
    int(*kernel_start)(BootInfo) = ((__attribute__((sytemv_abi)) int(*)(BootInfo))start_ddr);
    ST->ConOut->OutputString(ST->ConOut, L"\r\n Test kernel: ");
    EFI_MEMORY_DESCRIPTOR* map= NULL;
	UINTN mMap_size,Mapkey;
	UINTN Descriptor_size;
	UINT32 Descriptor_version;
	{
			SystemTable->BootServices->GetMemoryMap(&mMap_size,map,&Mapkey,&Descriptor_size,&Descriptor_version);
			SystemTable->BootServices->AllocatePool(EfiLoaderData,mMap_size,(void**)&map);
			SystemTable->BootServices->GetMemoryMap(&mMap_size,map,&Mapkey,&Descriptor_size,&Descriptor_version);
	}
    Bootinfo.map = map;
    Bootinfo.Descriptor_size = Descriptor_size;
    Bootinfo.mMap_size = mMap_size;
    ST->BootServices->ExitBootServices(ImageHandle,Mapkey);
    kernel_start(Bootinfo);
	//ST->ConOut->OutputString(ST->ConOut, to_string(kernel_start(Bootinfo),DEC));
    //Status = ST->ConOut->OutputString(ST->ConOut, L"\r\n");
    if (EFI_ERROR(Status))
        return Status; 
    return Status;
}