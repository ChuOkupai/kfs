#include <idt.h>
#include <interrupt.h>
#include <irq.h>
#include <pic.h>
#include <stdio.h>

/* Array of IRQ handlers */
static t_irq_handler g_irq_handlers[IRQ_COUNT] = {0};

/* External reference to IRQ stubs table */
extern void* irq_stub_table[];

void irq_handler(t_interrupt_frame* frame) {
	uint8_t irq = frame->int_no;
	if (g_irq_handlers[irq])
		g_irq_handlers[irq]();
	else
		printf("Unhandled IRQ %d\n", irq);
	pic_send_eoi(irq);
}

void init_irq() {
	extern void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
	
	/* Remap the PICs so IRQs don't conflict with CPU exceptions */
	pic_init(IRQ_BASE, IRQ_BASE + 8);

	/* Install IRQ handlers (0-15) in IDT vectors 0x20-0x2F */
	for (uint8_t i = 0; i < IRQ_COUNT; i++)
		idt_set_descriptor(IRQ_BASE + i, irq_stub_table[i], IDT_PRESENT | IDT_INTERRUPT_GATE);

	/* Mask all interrupts initially */
	pic_disable();
}

void irq_install_handler(uint8_t irq, t_irq_handler handler) {
	if (irq >= IRQ_COUNT) return;

	/* Set the handler function pointer */
	g_irq_handlers[irq] = handler;

	irq_enable(irq);
}

void irq_uninstall_handler(uint8_t irq) {
	if (irq >= IRQ_COUNT) return;

	irq_disable(irq);

	/* Clear the handler function pointer */
	g_irq_handlers[irq] = 0;
}

/**
 * Enable a specific IRQ.
 */
void irq_enable(uint8_t irq) {
	if (irq >= IRQ_COUNT) return;
	pic_unmask(irq);
}

/**
 * Disable a specific IRQ.
 */
void irq_disable(uint8_t irq) {
	if (irq >= IRQ_COUNT) return;
	pic_mask(irq);
}