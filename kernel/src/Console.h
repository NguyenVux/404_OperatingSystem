#pragma once
#include "graphic.h"

struct Position
{
	uint32_t x;
	uint32_t y;
};

class Console
{
public:
	uint32_t col = 0;
	uint32_t row = 0;
	uint8_t spacing = 2;
	Position cursor;
	FrameBuffer* buffer = NULL;
	PSF1_FONT* font = NULL;
	void init(FrameBuffer*,PSF1_FONT*);
	void print(char,uint32_t);
	void clear(uint32_t color);
	void setCursor(uint32_t x,uint32_t y);
};
extern Console console;