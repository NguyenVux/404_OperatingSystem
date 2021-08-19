#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__
#include "stdout.h"
#include "pic/pic.h"
struct interrupt_frame;
__attribute__((interrupt)) void PageFault_handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void KeyboardInt_handler(struct interrupt_frame* frame);
#endif 