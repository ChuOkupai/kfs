#include <interrupt.h>
#include <irq.h>
#include <stdint.h>
#include <stdio.h>

// Exception description table
typedef struct s_exception_info {
	const char* name;
	const char* description;
	uint8_t has_error_code;
	uint8_t can_continue;
} t_exception_info;

// Exception descriptions table
static const t_exception_info exception_table[] = {
	{ "Divide Error", "Division by zero or division overflow", 0, 0 },
	{ "Debug", "Debug exception", 0, 1 },
	{ "NMI", "Non-maskable interrupt", 0, 0 },
	{ "Breakpoint", "INT 3 instruction executed", 0, 1 },
	{ "Overflow", "INTO instruction executed with OF flag set", 0, 1 },
	{ "Bound Range", "BOUND instruction operand exceeds bounds", 0, 0 },
	{ "Invalid Opcode", "Undefined/invalid instruction executed", 0, 0 },
	{ "Device Not Available", "FPU/SIMD instruction with no math coprocessor", 0, 0 },
	{ "Double Fault", "Exception during exception handler", 1, 0 },
	{ "Coprocessor Segment Overrun", "FPU exception (legacy)", 0, 0 },
	{ "Invalid TSS", "Task switch to invalid TSS", 1, 0 },
	{ "Segment Not Present", "Loading segment register with invalid segment", 1, 0 },
	{ "Stack-Segment Fault", "Stack operation beyond stack segment limit", 1, 0 },
	{ "General Protection", "Memory access violation or privilege error", 1, 0 },
	{ "Page Fault", "Memory access to non-present page", 1, 0 },
	{ "Reserved", "Reserved exception (15)", 0, 0 },
	{ "x87 FP Exception", "Floating-point exception", 0, 0 },
	{ "Alignment Check", "Unaligned memory access", 1, 0 },
	{ "Machine Check", "Hardware error detected", 0, 0 },
	{ "SIMD FP Exception", "SSE/AVX floating-point exception", 0, 0 },
	{ "Virtualization Exception", "Virtualization feature exception", 0, 0 },
	{ "Control Protection", "Protection check violation", 1, 0 },
	{ "Reserved", "Reserved exception (22)", 0, 0 },
	{ "Reserved", "Reserved exception (23)", 0, 0 },
	{ "Reserved", "Reserved exception (24)", 0, 0 },
	{ "Reserved", "Reserved exception (25)", 0, 0 },
	{ "Reserved", "Reserved exception (26)", 0, 0 },
	{ "Reserved", "Reserved exception (27)", 0, 0 },
	{ "Reserved", "Reserved exception (28)", 0, 0 },
	{ "Reserved", "Reserved exception (29)", 0, 0 },
	{ "Security Exception", "Security-sensitive event", 1, 0 },
	{ "Reserved", "Reserved exception (31)", 0, 0 }
};

/**
 * Prints error code info for specific exceptions
 */
static void print_error_code_info(uint8_t exception, uint32_t error_code) {
	switch(exception) {
		case 8: // Double Fault
			printf("Error code: 0x%x (should be zero)\n", error_code);
			break;

		case 10: // Invalid TSS
		case 11: // Segment Not Present
		case 12: // Stack Fault
		case 13: // General Protection Fault
			printf("Selector: 0x%04x, Table: %s, External: %s\n",
				  error_code & ~0x7,
				  (error_code & 0x4) ? "External" : "Internal",
				  (error_code & 0x3) == 0 ? "GDT" : 
				  (error_code & 0x3) == 1 ? "IDT" : 
				  (error_code & 0x3) == 2 ? "LDT" : "IDT");
			break;

		case 14: // Page Fault
			{
				uint32_t cr2;
				asm volatile("movl %%cr2, %0" : "=r"(cr2));
				printf("Faulting address: 0x%08x\n", cr2);
				printf("Caused by: %s %s %s %s\n",
					  (error_code & 0x1) ? "present page" : "non-present page",
					  (error_code & 0x2) ? "write" : "read",
					  (error_code & 0x4) ? "user-mode" : "kernel-mode",
					  (error_code & 0x8) ? "reserved bit violation" : "normal access");
			}
			break;
	}
}

/**
 * Print a stack trace
 */
static void print_stack_trace(uint32_t ebp) {
	printf("\nStack trace (approximate):\n");
	uint32_t* stack_ptr = (uint32_t*)ebp;
	for (int i = 0; i < 5 && stack_ptr != NULL && (uint32_t)stack_ptr > 0x1000; i++) {
		uint32_t return_addr = *(stack_ptr + 1);
		printf("[%d] EBP=0x%08x Return=0x%08x\n", i, (uint32_t)stack_ptr, return_addr);
		stack_ptr = (uint32_t*)*stack_ptr;
	}
}

/**
 * Print detailed register state
 */
static void print_register_dump(t_interrupt_frame* frame) {
	printf("\nRegister Dump:\n");
	printf("EAX=0x%08x  EBX=0x%08x  ECX=0x%08x  EDX=0x%08x\n", 
		   frame->eax, frame->ebx, frame->ecx, frame->edx);
	printf("ESI=0x%08x  EDI=0x%08x  EBP=0x%08x  ESP=0x%08x\n", 
		   frame->esi, frame->edi, frame->ebp, frame->esp);
	printf("EIP=0x%08x  CS=0x%04x    EFLAGS=0x%08x\n",
		   frame->eip, frame->cs, frame->eflags);
}

/**
 * General exception handler for all CPU exceptions
 */
void exception_handler(t_interrupt_frame* frame) {
	uint8_t exception = frame->int_no;
	
	if (exception < 32) {
		const t_exception_info* info = &exception_table[exception];
		
		printf("\n====== EXCEPTION: %s ======\n", info->name);
		printf("%s\n", info->description);
		printf("Error code: 0x%x\n", frame->err_code);
		
		// Print CPU state
		printf("At CS:EIP = 0x%04x:0x%08x\n", frame->cs, frame->eip);
		
		// Print detailed error information
		print_error_code_info(exception, frame->err_code);
		
		// Print registers and stack trace
		print_register_dump(frame);
		print_stack_trace(frame->ebp);
		
		// Check if we can continue
		if (info->can_continue) {
			printf("\nContinuing execution...\n");
			return;
		}
	} else {
		printf("\nKERNEL PANIC: Unknown exception %d (Error code: 0x%x)\n", 
			   exception, frame->err_code);
		print_register_dump(frame);
	}
	
	printf("\nSystem halted.\n");
	while(1); // Halt
}