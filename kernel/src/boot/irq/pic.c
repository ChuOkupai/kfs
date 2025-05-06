#include <io.h>
#include <pic.h>

void pic_init(uint8_t offset1, uint8_t offset2) {
	// Save masks
	uint8_t mask1 = inb(PIC1_DATA);
	uint8_t mask2 = inb(PIC2_DATA);

	// Start initialization sequence (cascade mode)
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	// ICW2: Set vector offsets
	outb(PIC1_DATA, offset1);     // Master PIC starts at offset1
	io_wait();
	outb(PIC2_DATA, offset2);     // Slave PIC starts at offset2
	io_wait();

	// ICW3: Tell Master PIC that there is a slave at IRQ2 (0000 0100)
	outb(PIC1_DATA, 0x04);
	io_wait();
	// ICW3: Tell Slave PIC its cascade identity (0000 0010)
	outb(PIC2_DATA, 0x02);
	io_wait();

	// ICW4: Set 8086 mode
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Restore saved masks
	outb(PIC1_DATA, mask1);
	outb(PIC2_DATA, mask2);
}

void pic_send_eoi(uint8_t irq) {
	if (irq >= 8) {
		// Send to slave PIC if IRQ is from the slave (IRQ8-15)
		outb(PIC2_COMMAND, PIC_EOI);
	}
	// Always send to master PIC
	outb(PIC1_COMMAND, PIC_EOI);
}

void pic_mask(uint8_t irq) {
	uint16_t port;
	uint8_t value;

	if (irq < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		irq -= 8;
	}

	value = inb(port) | (1 << irq);
	outb(port, value);
}

void pic_unmask(uint8_t irq) {
	uint16_t port;
	uint8_t value;

	if (irq < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		irq -= 8;
	}

	value = inb(port) & ~(1 << irq);
	outb(port, value);
}

void pic_disable() {
	// Mask all interrupts
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}