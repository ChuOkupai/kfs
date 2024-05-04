#include <stdio.h>
#include <stack.h>

extern uint32_t stack_bottom;
extern uint32_t stack_top;

void print_stack_info() {
	puts(" Stack bottom | Stack top  | Stack size");
	puts("--------------|------------|------------");
	printf(" 0x%08x   | 0x%08x | %d\n", (uint32_t) &stack_bottom, (uint32_t) &stack_top, stack_size());
}

void print_stack_trace() {
	t_stackframe *stk;
	asm ("movl %%ebp,%0" : "=r"(stk) ::);
	puts("Stack trace:");
	for(unsigned int frame = 0; stk && frame < 7; ++frame) {
		// Unwind to previous stack frame
		printf("  #%d 0x%x\n", frame, stk->eip);
		stk = stk->ebp;
	}
}

size_t stack_size() {
	return (uint32_t)&stack_top - (uint32_t)&stack_bottom;
}
