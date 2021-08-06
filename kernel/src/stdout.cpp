#include "stdout.h"


void Stdout::init(Console* console)
{
	this->_console = console;
}

void Stdout::write(void* byte, uint8_t size)
{
	uint8_t* _ptr = (uint8_t*)byte;
	uint8_t* _buffer = (uint8_t*)buffer+head;
	for(uint8_t i =0 ;i < size; ++i)
	{
		if((uint64_t)_buffer - (uint64_t)buffer > buffer_size)
		{
			flush();
			_buffer = (uint8_t*)buffer+head;
		}
		*_buffer = *_ptr;
		head++;
		_buffer++;
		_ptr++;
	}
}

void Stdout::flush()
{
		for (int i = 0; i < head; i++)
		{
			_console->print(buffer[i],0);
		}
		head= 0;
}

Stdout& operator<<(Stdout& out, char* x)
{
		while (*x != 0)
		{
			out.write(x,1);
			x++;
		}
		return out;
}