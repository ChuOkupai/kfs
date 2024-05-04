#include <string.h>
#include <gdt.h>

t_gdtr g_kgdtr;
t_gdtdescriptor g_kgdt[7];

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
	init_gdt_desc(0x0, 0x0, 0x0, 0x0, g_kgdt); // null descriptor
	init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, g_kgdt + 1); // kernel code
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, g_kgdt + 2); // kernel data
	init_gdt_desc(0x0, 0x0, 0x97, 0x0D, g_kgdt + 3); // kernel stack
	init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, g_kgdt + 4); // user code
	init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, g_kgdt + 5); // user data
	init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, g_kgdt + 6); // user stack

	g_kgdtr.limite = sizeof(g_kgdt);
	g_kgdtr.base = GDT_MEMORY;

	memcpy((char *)g_kgdtr.base, (char *)g_kgdt, g_kgdtr.limite);

	asm("lgdtl (g_kgdtr)");

	flush_gdt((uint32_t) &g_kgdtr);
}
