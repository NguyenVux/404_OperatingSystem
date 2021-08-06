#include "EFI_IO.h"
CHAR16 buffer[1024];
CHAR16* num_table = L"0123456789ABCDEF";
CHAR16* to_string(uint64_t in,int format)
{
    if (in == 0)
    {
        buffer[0] = num_table[0];
        buffer[1] = '\0';
        return buffer;
    }
    if(format == HEX)
    {
        uint64_t tmp = in;
        uint32_t digit= 0;
        while(tmp != 0){
            digit++;
            tmp >>= 4;
        }
        buffer[digit] = '\0';
        while(digit > 0){
            digit--;
            uint8_t d = in & 0xf;
            buffer[digit] = num_table[d];
            in >>=4;
        }
        return buffer;
    }
    if(format == BIN)
    {
        uint64_t tmp = in;
        uint32_t digit= 0;
        while(tmp != 0){
            digit++;
            tmp >>= 1;
        }
        buffer[digit+1] = '\0';
        while(digit > 0){
            digit--;
            uint8_t d = in & 0x1;
            buffer[digit] = num_table[d];
            in >>=1;
        }
        return buffer;
    }
    if(format == DEC)
    {
        uint64_t tmp = in;
        uint32_t digit= 0;
        while(tmp != 0){
            digit++;
            tmp/=10;
        }
        buffer[digit+1] = '\0';
        while(digit > 0){
            digit--;
            uint8_t d = in % 10;
            buffer[digit] = num_table[d];
            in /=10;
        }
        return buffer;
    }
    buffer[0] = 'W';
    buffer[1] = 'R';
    buffer[2] = 'O';
    buffer[3] = 'N';
    buffer[4] = 'G';
    buffer[5] = '\0';
    return buffer;
}