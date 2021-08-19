#include "Console.h"


Console console;
void Console::init(FrameBuffer* _b, PSF1_FONT* _f) {
    buffer = _b;
    font = _f;
    cursor.x=0;
    cursor.y = 0;
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
	if(cursor.x+8+spacing > buffer->Pixel_per_ScaneLine)
	{
		cursor.x = 0;
		cursor.y += font->PSF1_HEADERl->charsize;
	}
	
	uint32_t* pixel_pointer =  (uint32_t*)buffer->Base_Adrress;
	char* fontPtr = (char*)font->glyph_BUFFER + (font->PSF1_HEADERl->charsize*x);
	for(uint64_t y =0; y < font->PSF1_HEADERl->charsize;y++)
	{
		for(uint64_t x =0; x < 8;x++)
		{
			if( (*fontPtr &(0b10000000 >> x)) >0)
			{
				uint64_t mem_addr = (x+cursor.x)+((y+cursor.y)*buffer->Pixel_per_ScaneLine);
				if(mem_addr < buffer->height*buffer->Pixel_per_ScaneLine)
				{
					*(pixel_pointer+mem_addr) = color;
				}
			}
		}
		++fontPtr;

	}
	cursor.x+=8+spacing;
	
}

void Console::clear(uint32_t color) 
{
	uint32_t* pixel_pointer =  (uint32_t*)buffer->Base_Adrress;
	uint32_t* end = (uint32_t*)((uint8_t*)pixel_pointer+buffer->Buffer_Size);

	for(; pixel_pointer <= end; pixel_pointer++)
	{
		*pixel_pointer = color;
	}
}

void Console::setCursor(uint32_t x,uint32_t y)
{
	this->cursor = {x,y};
}

