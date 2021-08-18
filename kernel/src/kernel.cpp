#include "kernelUtil.h"
#include "gdt/gdt.h"



typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

extern "C" void _start(BootInfo bootInfo)
{
	char a[] = "TEST";
	int segment_count = bootInfo.mMap_size / bootInfo.Descriptor_size;
	init_kernel(&bootInfo);
	uint64_t memory_size;
	GDTDescriptor gdtp;
	gdtp.Size = sizeof(GDT) -1;
	gdtp.Offset = (uint64_t)&DefaultGDT;
	stdout <<"Kernel: " << (uint64_t)&gdtp << endl;
	stdout << "packed size: " << sizeof(GDTEntry) << endl;
	stdout << "packed size: " << sizeof(GDTDescriptor) << endl;
	stdout << "pixel mode: " << bootInfo.buffer->pixel_mode << endl;
	stdout << "buffer size: " << bootInfo.buffer->Buffer_Size << endl;
	stdout << "pixel perline: " << bootInfo.buffer->Pixel_per_ScaneLine << endl;
	stdout << "height: " << bootInfo.buffer->height << endl;
	for (uint8_t c = 0; c < 255; c++)
	{
		HsvColor hsv = {c,255,255};
		RgbColor color = HsvToRgb(hsv);
		uint32_t _color;
		_color |= (uint32_t)color.b;
		_color |= (uint32_t)color.g << 8;
		_color |= (uint32_t)color.r << 16;
		console.clear(_color);
	}
	//console.clear(0);
	while(1){};
}
