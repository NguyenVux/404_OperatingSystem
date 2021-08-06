#include "GOP.h"
extern int init_GOP(EFI_HANDLE ImageHandle,EFI_SYSTEM_TABLE *SystemTable,FrameBuffer* fBuffer)
{
	EFI_GUID gop_GUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
	EFI_STATUS status;
	EFI_SYSTEM_TABLE* ST = SystemTable;
	status = ST->BootServices->LocateProtocol(&gop_GUID,NULL,(void**)&gop);
	if(EFI_ERROR(status))
	{
		return 0;
	}
	fBuffer->Base_Adrress = (void*)gop->Mode->FrameBufferBase;
	fBuffer->Buffer_Size = gop->Mode->FrameBufferSize;
	fBuffer->pixel_mode = (int)gop->Mode->Info->PixelFormat;
	fBuffer->width = gop->Mode->Info->HorizontalResolution;
	fBuffer->height = gop->Mode->Info->VerticalResolution;
	fBuffer->Pixel_per_ScaneLine = gop->Mode->Info->PixelsPerScanLine;
	return 1;
}


PSF1_FONT* Load_font(
				EFI_FILE* directory,
				CHAR16* PATH,
				EFI_HANDLE ImageHandle,
				EFI_SYSTEM_TABLE *SystemTable
			) 
{
	EFI_FILE* font = Load_file(directory,PATH,ImageHandle,SystemTable);
	
	if(font == NULL)
		return NULL;
		
	PSF1_FONT *loaded_font;
	SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(PSF1_FONT),(void**)&loaded_font);

	SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(PSF1_HEADER),(void**)&(loaded_font->PSF1_HEADERl));
	UINTN Header_size = sizeof(PSF1_HEADER);
	font->Read(font,&Header_size,loaded_font->PSF1_HEADERl);


	if(loaded_font->PSF1_HEADERl->magic != PSF_MAGIC) 
		return NULL;
	UINTN glyph_buffer_size = loaded_font->PSF1_HEADERl->charsize * 256;
	if(loaded_font->PSF1_HEADERl->mode == 1) // 512 glyph
	{
		glyph_buffer_size = loaded_font->PSF1_HEADERl->charsize*512;
	}
	font->SetPosition(font,sizeof(PSF1_HEADER));	
	SystemTable->BootServices->AllocatePool(EfiLoaderData,glyph_buffer_size,(void**)&(loaded_font->glyph_BUFFER));
	font->Read(font,&glyph_buffer_size,loaded_font->glyph_BUFFER);
	return loaded_font;
}