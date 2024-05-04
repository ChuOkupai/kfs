.global flush_gdt

flush_gdt:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	ljmp $0x08, $next

next:
