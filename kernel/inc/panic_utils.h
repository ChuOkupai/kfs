#pragma once

/**
 * Clean CPU registers to prevent undefined behavior after a panic
 */
void clean_registers(void);

/**
 * Save the current stack pointer
 * 
 * @return The current stack pointer
 */
void* save_stack_pointer(void);

/**
 * Halt the CPU indefinitely
 * This function never returns
 */
__attribute__((noreturn)) void halt_cpu(void);
