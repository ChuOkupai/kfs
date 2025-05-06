#include <string.h>
#include <gdt.h>

t_gdtdescriptor g_kgdt[GDT_ENTRIES];

extern void flush_gdt(uint32_t);

static inline void init_gdt_desc(uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags, t_gdtdescriptor *desc) {
	desc->limit = (limit & 0xffff);
	desc->base_low = (base & 0xffff);
	desc->base_middle = (base & 0xff0000) >> 16;
	desc->access_byte = access_byte;
	desc->limit_high = (limit & 0xf0000) >> 16;
	desc->flags = (flags & 0xf);
	desc->base_high = (base & 0xff000000) >> 24;
}

void init_gdt() {
	// Null descriptor
	init_gdt_desc(0x0, 0x0, 0x0, 0x0, g_kgdt);
	// Kernel code segment (R-X)
	init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, g_kgdt + 1);
	// Kernel data segment (RW-)
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, g_kgdt + 2);
	// Kernel stack segment (RW-) - Should have a non-zero limit!
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, g_kgdt + 3);
	// User code segment (R-X)
	init_gdt_desc(0x0, 0xFFFFF, 0xFB, 0x0D, g_kgdt + 4);
	// User data segment (RW-)
	init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, g_kgdt + 5);
	// User stack segment (RW-) - Should have a non-zero limit!
	init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, g_kgdt + 6);

	memcpy((void*)GDT_MEMORY, (void*)g_kgdt, sizeof(g_kgdt));

	static t_gdtr gdtr;
	gdtr.limite = sizeof(g_kgdt) - 1;
	gdtr.base = GDT_MEMORY;

	flush_gdt((uint32_t)&gdtr);
}
