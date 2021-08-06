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
	fBuffer->width = gop->Mode->Info->HorizontalResolution;
	fBuffer->height = gop->Mode->Info->VerticalResolution;
	fBuffer->Pixel_per_ScaneLine = gop->Mode->Info->PixelsPerScanLine;
	return 1;
}