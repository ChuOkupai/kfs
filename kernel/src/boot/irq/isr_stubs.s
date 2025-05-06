.section .text
.global isr_stub_table
.extern exception_handler

/* Macro for ISR stubs without error codes */
.macro ISR_NO_ERR_STUB num
.global isr_stub_\num
isr_stub_\num:
	pushl $0
	pushl $\num
	pusha

	movl %esp, %eax
	pushl %eax
	call exception_handler
	addl $4, %esp

	popa
	addl $8, %esp
	iret
.endm

/* Macro for ISR stubs with error codes */
.macro ISR_ERR_STUB num
.global isr_stub_\num
isr_stub_\num:
	pushl $\num
	pusha

	movl %esp, %eax
	pushl %eax
	call exception_handler
	addl $4, %esp

	popa
	addl $8, %esp
	iret
.endm

/* Create stubs for all 32 CPU exceptions */
ISR_NO_ERR_STUB 0
ISR_NO_ERR_STUB 1
ISR_NO_ERR_STUB 2
ISR_NO_ERR_STUB 3
ISR_NO_ERR_STUB 4
ISR_NO_ERR_STUB 5
ISR_NO_ERR_STUB 6
ISR_NO_ERR_STUB 7
ISR_ERR_STUB    8
ISR_NO_ERR_STUB 9
ISR_ERR_STUB    10
ISR_ERR_STUB    11
ISR_ERR_STUB    12
ISR_ERR_STUB    13
ISR_ERR_STUB    14
ISR_NO_ERR_STUB 15
ISR_NO_ERR_STUB 16
ISR_ERR_STUB    17
ISR_NO_ERR_STUB 18
ISR_NO_ERR_STUB 19
ISR_NO_ERR_STUB 20
ISR_NO_ERR_STUB 21
ISR_NO_ERR_STUB 22
ISR_NO_ERR_STUB 23
ISR_NO_ERR_STUB 24
ISR_NO_ERR_STUB 25
ISR_NO_ERR_STUB 26
ISR_NO_ERR_STUB 27
ISR_NO_ERR_STUB 28
ISR_NO_ERR_STUB 29
ISR_ERR_STUB    30
ISR_NO_ERR_STUB 31

/* Define the ISR stub table */
isr_stub_table:
	.long isr_stub_0
	.long isr_stub_1
	.long isr_stub_2
	.long isr_stub_3
	.long isr_stub_4
	.long isr_stub_5
	.long isr_stub_6
	.long isr_stub_7
	.long isr_stub_8
	.long isr_stub_9
	.long isr_stub_10
	.long isr_stub_11
	.long isr_stub_12
	.long isr_stub_13
	.long isr_stub_14
	.long isr_stub_15
	.long isr_stub_16
	.long isr_stub_17
	.long isr_stub_18
	.long isr_stub_19
	.long isr_stub_20
	.long isr_stub_21
	.long isr_stub_22
	.long isr_stub_23
	.long isr_stub_24
	.long isr_stub_25
	.long isr_stub_26
	.long isr_stub_27
	.long isr_stub_28
	.long isr_stub_29
	.long isr_stub_30
	.long isr_stub_31