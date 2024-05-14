#pragma once
#include <stdint.h>

/**
 * Reads the current value of the PIT.
 * @return The current value of the PIT.
*/
uint16_t pit_read();

/**
 * Initialize the Programmable Interval Timer (PIT).
 */
void timer_init();

/**
 * Wait for at least the specified amount of milliseconds.
 * @note This function is blocking.
 * @param ms The amount of milliseconds to wait.
 */
void timer_wait(uint16_t ms);
