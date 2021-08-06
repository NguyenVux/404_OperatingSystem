#include "Console.h"

void Console::init(FrameBuffer* _b, PSF1_FONT* _f) {
    buffer = _b;
    font = _f;
}

void Console::print(char x,uint32_t color) {
	if(buffer == NULL || font == NULL)
		return;

	if(x == '\n')
	{
		cursor.y += font->PSF1_HEADERl->charsize;
		return;
	}

	if(x == '\r')
	{
		cursor.x = 0;
		return;
	}

	
	uint32_t* pixel_pointer =  (uint32_t*)buffer->Base_Adrress;
	char* fontPtr = (char*)font->glyph_BUFFER + (font->PSF1_HEADERl->charsize*x);
	for(uint64_t y =0; y < font->PSF1_HEADERl->charsize;y++)
	{
		for(uint64_t x =0; x < 8;x++)
		{
			if( (*fontPtr &(0b10000000 >> x)) >0)
			{
				*(pixel_pointer+(x+cursor.x)+((y+cursor.y)*buffer->Pixel_per_ScaneLine)) = 0xffffffff;
			}
		}
		++fontPtr;

	}
	cursor.x+=8+spacing;
	if(cursor.x > buffer->Pixel_per_ScaneLine)
	{
		cursor.x = 0;
		cursor.y += font->PSF1_HEADERl->charsize;
	}
}

