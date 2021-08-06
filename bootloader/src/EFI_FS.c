#include "EFI_FS.h"

EFI_FILE* Load_file(EFI_FILE* directory , CHAR16* PATH,EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_FILE* Loaded_file;
	EFI_LOADED_IMAGE_PROTOCOL* Loaded_image;
	SystemTable->BootServices->HandleProtocol(ImageHandle,&gEfiLoadedImageProtocolGuid,(void**)&Loaded_image);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FS;
	SystemTable->BootServices->HandleProtocol(Loaded_image->DeviceHandle,&gEfiSimpleFileSystemProtocolGuid,(void**)&FS);
	if(directory == NULL)
	{
		FS->OpenVolume(FS,&directory);
	}
	EFI_STATUS status = directory->Open(directory,&Loaded_file,PATH,EFI_FILE_MODE_READ,EFI_FILE_READ_ONLY);
	if(status != EFI_SUCCESS)
	{
		return NULL;
	}
	
	return Loaded_file;
}