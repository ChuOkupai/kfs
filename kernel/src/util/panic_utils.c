#include <stdio.h>
#include <panic_utils.h>

void clean_registers(void)
{
    // Clean general purpose registers
    asm volatile(
        "xor %%eax, %%eax;"
        "xor %%ebx, %%ebx;"
        "xor %%ecx, %%ecx;"
        "xor %%edx, %%edx;"
        "xor %%esi, %%esi;"
        "xor %%edi, %%edi;"
        : : : "eax", "ebx", "ecx", "edx", "esi", "edi"
    );
}

void* save_stack_pointer(void)
{
    void* stack_ptr;
    asm("mov %%esp, %0" : "=r"(stack_ptr));
    return stack_ptr;
}

__attribute__((noreturn)) void halt_cpu(void)
{
    // Disable interrupts first
    asm volatile("cli");

    printf("System halted. Press the reset button to restart.\n");

    clean_registers();
    
    // Infinite halt loop
    while(1) {
        asm volatile("hlt");
    }
}
