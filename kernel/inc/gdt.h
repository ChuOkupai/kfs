#pragma once
#include <stdint.h>

#define GDT_MEMORY	0x800
#define GDT_ENTRIES	7
#define GDT_SIZE	(GDT_ENTRIES * sizeof(t_gdtdescriptor))

typedef struct s_gdtr {
	uint16_t	limite;
	uint32_t	base;
}	__attribute__ ((packed)) t_gdtr;

typedef struct s_gdtdescriptor {
	uint16_t	limit;
	uint16_t	base_low;
	uint8_t		base_middle;
	uint8_t		access_byte;
	uint8_t		limit_high : 4;
	uint8_t		flags : 4;
	uint8_t		base_high;
}	__attribute__ ((packed)) t_gdtdescriptor;

/**
 * Initialize the GDT.
*/
void init_gdt();
