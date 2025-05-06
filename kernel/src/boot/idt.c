#include <idt.h>
#include <string.h>

__attribute__((aligned(0x10))) 
static t_idt_entry g_idt[IDT_ENTRIES];

static t_idtr g_idtr;

// Keep track of which vectors are registered
static int g_vectors[IDT_ENTRIES] = {0};

// External reference to our ISR stub table
extern void* isr_stub_table[];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	t_idt_entry* descriptor = &g_idt[vector];

	descriptor->isr_low     = (uint32_t)isr & 0xFFFF;
	descriptor->kernel_cs   = 0x08; // Kernel code segment
	descriptor->reserved    = 0;    // Must be 0
	descriptor->attributes  = flags;
	descriptor->isr_high    = (uint32_t)isr >> 16;
}

void init_idt()
{
	// Zero out the entire IDT first
	memset(g_idt, 0, sizeof(g_idt));
	
	// Set up exception handlers (0-31)
	for (uint8_t vector = 0; vector < 32; vector++) {
		idt_set_descriptor(vector, isr_stub_table[vector], IDT_PRESENT | IDT_INTERRUPT_GATE);
		g_vectors[vector] = 1;
	}

	// Copy IDT to the designated memory location
	memcpy((void*)IDT_MEMORY, (void*)g_idt, sizeof(g_idt));

	// Set up IDTR
	g_idtr.base = IDT_MEMORY;
	g_idtr.limit = sizeof(g_idt) - 1;

	// Load IDT
	__asm__ volatile ("lidt %0" : : "m"(g_idtr) : "memory");
}