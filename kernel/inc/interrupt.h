#pragma once
#include <stdint.h>

typedef struct s_interrupt_frame {
	// Pushed by pusha
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	// Interrupt number and error code
	uint32_t int_no, err_code;
	// Pushed by the processor automatically
	uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) t_interrupt_frame;