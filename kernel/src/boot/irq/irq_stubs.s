.section .text
.global irq_stub_table

/* External reference to our C IRQ handler */
.extern irq_handler

/* Macro for IRQ stubs */
.macro IRQ_STUB num
.global irq_stub_\num
irq_stub_\num:
	pushl $0              /* Push dummy error code */
	pushl $\num           /* Push IRQ number */
	pusha                 /* Push all general purpose registers */
	
	movl %esp, %eax       /* Pass pointer to stack frame */
	pushl %eax
	call irq_handler      /* Call C handler */
	addl $4, %esp         /* Clean up stack */
	
	popa                  /* Restore all registers */
	addl $8, %esp         /* Clean up error code and IRQ number */
	iret                  /* Return from interrupt */
.endm

/* Create stubs for all 16 hardware IRQs */
IRQ_STUB 0
IRQ_STUB 1
IRQ_STUB 2
IRQ_STUB 3
IRQ_STUB 4
IRQ_STUB 5
IRQ_STUB 6
IRQ_STUB 7
IRQ_STUB 8
IRQ_STUB 9
IRQ_STUB 10
IRQ_STUB 11
IRQ_STUB 12
IRQ_STUB 13
IRQ_STUB 14
IRQ_STUB 15

/* Define IRQ stub table for easy reference */
irq_stub_table:
	.long irq_stub_0
	.long irq_stub_1
	.long irq_stub_2
	.long irq_stub_3
	.long irq_stub_4
	.long irq_stub_5
	.long irq_stub_6
	.long irq_stub_7
	.long irq_stub_8
	.long irq_stub_9
	.long irq_stub_10
	.long irq_stub_11
	.long irq_stub_12
	.long irq_stub_13
	.long irq_stub_14
	.long irq_stub_15