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
void *memcpy(void *restrict s1, const void *s2, size_t n)
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
    PSF1_FONT* font;
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
        ST->ConOut->OutputString(ST->ConOut, L"Loading kernel \r\n");
        uint64_t start_ddr = LoadPE(NULL,L"404OS\\kernel.sys",ImageHandle,ST);
        BootInfo Bootinfo;
        ST->ConOut->OutputString(ST->ConOut, L"Loading font \r\n");
        Bootinfo.font = Load_font(NULL,L"404OS\\zap-light18.psf",ImageHandle,ST);
        if(Bootinfo.font == NULL)
            ST->ConOut->OutputString(ST->ConOut, L"Can't font \r\n");
        else
            ST->ConOut->OutputString(ST->ConOut, L"font loaded \r\n");
        Bootinfo.buffer = &fBuffer;
        void(*kernel_start)(BootInfo) = ((__attribute__((sytemv_abi)) void(*)(BootInfo))start_ddr);
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
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"Failed to init system\r\n");
    }
    if (EFI_ERROR(Status))
        return Status; 
    return Status;
}