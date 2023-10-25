#pragma once
#include <stdint.h>

/**
 * Initialize the Programmable Interval Timer (PIT).
 */
void timer_init();

/**
 * Wait for at least the specified amount of milliseconds.
 * This function is blocking.
 * @param ms The amount of milliseconds to wait.
 */
void timer_wait(uint16_t ms);
