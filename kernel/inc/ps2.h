#pragma once
#include <stdint.h>

/**
 * Initializes the PS/2 controller.
*/
void init_ps2();

/**
 * Reads a byte from the PS/2 controller.
 * @return The byte read.
*/
uint8_t read_ps2_data();

/**
 * Reads the PS/2 controller's status.
 * @return The status.
*/
uint8_t read_ps2_status();

/**
 * Writes a command to the PS/2 controller.
 * @param command The command to write.
*/
void write_ps2_command(uint8_t command);

/**
 * Writes data to the PS/2 controller.
 * @param data The data to write.
*/
void write_ps2_data(uint8_t data);
