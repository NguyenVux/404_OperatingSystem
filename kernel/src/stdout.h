#pragma once
//#include "stream/stream.h"
#include "Graphic\Console.h"


class Stdout
{
private:
	Console* _console;
	uint8_t buffer[256];
	uint8_t head = 0;
	static const uint64_t buffer_size = 256;
public:
	void write(void* byte, uint8_t size);
	void init(Console* console);
	void flush();
	friend Stdout& operator<<(Stdout& out, char* x);
};