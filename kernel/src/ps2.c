#include <io.h>
#include <ps2.h>

#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64

void init_ps2() {
	// Disable the devices
	write_ps2_command(0xAD);
	write_ps2_command(0xA7);

	// Flush the output buffer
	while (read_ps2_status() & 1) {
		read_ps2_data();
	}

	// Set the controller configuration byte
	write_ps2_command(0x20);
	uint8_t config = read_ps2_data();
	config &= ~(1 << 0); // Enable IRQ1 (keyboard)
	config &= ~(1 << 1); // Enable IRQ12 (mouse)
	write_ps2_command(0x60);
	write_ps2_data(config);

	// Perform controller self-test
	write_ps2_command(0xAA);
	uint8_t self_test_result = read_ps2_data();
	if (self_test_result != 0x55) {
		// TODO: Add kernel panic when self-test fails
		return;
	}

	// Enable the devices
	write_ps2_command(0xAE);
	write_ps2_command(0xA8);
}

uint8_t read_ps2_data() {
	while (!(read_ps2_status() & 1)) {
		// Wait for output buffer to be full
	}

	return inb(PS2_DATA_PORT);
}

uint8_t read_ps2_status() {
	return inb(PS2_STATUS_PORT);
}

void write_ps2_command(uint8_t command) {
	while (read_ps2_status() & 2) {
		// Wait for input buffer to be empty
	}

	outb(PS2_STATUS_PORT, command);
}

void write_ps2_data(uint8_t data) {
	while (read_ps2_status() & 2) {
		// Wait for input buffer to be empty
	}

	outb(PS2_DATA_PORT, data);
}
