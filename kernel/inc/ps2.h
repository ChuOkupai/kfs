#pragma once
#include <stdint.h>

void init_ps2();
uint8_t read_ps2_data();
uint8_t read_ps2_status();
void write_ps2_command(uint8_t command);
void write_ps2_data(uint8_t data);
