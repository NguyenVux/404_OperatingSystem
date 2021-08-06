#include "stdout.h"


void Stdout::init(Console* console)
{
	this->_console = console;
	head=0;
}

void Stdout::write(const void* byte, uint8_t size)
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

Stdout& operator<<(Stdout& out,uint32_t x) 
{
	return out.print_num_uint(out,x);
}
Stdout& operator<<(Stdout& out,int32_t x) 
{
	return out.print_num_int(out,x);
}
Stdout& operator<<(Stdout& out,uint16_t x) 
{
	return out.print_num_uint(out,x);
}
Stdout& operator<<(Stdout& out,int16_t x) 
{
	return out.print_num_int(out,x);
}


Stdout& operator<<(Stdout& out,int64_t x) 
{
	return out.print_num_int(out,x);
}

Stdout& operator<<(Stdout& out,uint64_t x) 
{
	return out.print_num_uint(out,x);
}

Stdout& operator<<(Stdout& out,const char* x)
{
		while (*x != 0)
		{
			out.write(x,1);
			x++;
		}
		return out;
}
Stdout& Stdout::print_num_uint(Stdout& out,uint64_t num) 
{
	char num_buffer[22];
        uint64_t tmp = num;
        uint32_t digit= 0;
        {
            digit++;
            tmp/=10;
        }while(tmp != 0);
        num_buffer[digit] = '\0';
        while(digit > 0){
            digit--;
            char d = num % 10;
            num_buffer[digit] = d+'0';
            num /=10;
        }
	out << num_buffer;
	return out;
}

Stdout& Stdout::print_num_int(Stdout& out,int64_t num) 
{
	char num_buffer[22];
        uint64_t tmp = num;
        uint32_t digit= 0;
	if(num < 0)
	{
		tmp *=-1;
		while(tmp != 0){
			digit++;
			tmp/=10;
		}
		num_buffer[digit+2] = '\0';
		num*=-1;
		while(digit > 0){
		digit--;
		char d = num % 10;
		num_buffer[digit+1] = d+'0';
		num /=10;
       		}
		num_buffer[0]='-';
	}
	else
	{
		while(tmp != 0){
			digit++;
			tmp/=10;
		}
		num_buffer[digit+1] = '\0';
		while(digit > 0){
			digit--;
			char d = num % 10;
			num_buffer[digit] = d+'0';
			num /=10;
		}
	}
        
	out << num_buffer;
	return out;
}
