#pragma once
#include <stdint.h>

typedef struct s_idtr {
	uint16_t	limit;
	uint32_t	base;
}	__attribute__ ((packed)) t_idtr;

typedef struct s_idt_entry {
	uint16_t	isr_low;      // The lower 16 bits of the ISR's address
	uint16_t	kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t		reserved;     // Set to zero
	uint8_t		attributes;   // Type and attributes; see the IDT page
	uint16_t	isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) t_idt_entry;

#define IDT_MEMORY	0x1000
#define IDT_ENTRIES	256
#define IDT_SIZE	(IDT_ENTRIES * sizeof(t_idt_entry))

/* Gate Types */
#define IDT_TASK_GATE		0x5
#define IDT_INTERRUPT_GATE	0xE
#define IDT_TRAP_GATE		0xF

/* Descriptor Privilege Level */
#define IDT_DPL_KERNEL		0x00 /* Ring 0 */
#define IDT_DPL_USER		0x60 /* Ring 3 */

/* Present bit */
#define IDT_PRESENT		0x80

/**
 * Initialize the IDT.
*/
void init_idt();