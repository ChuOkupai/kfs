#pragma once
#include <stdint.h>

/* IRQ numbers */
#define IRQ_TIMER           0
#define IRQ_KEYBOARD        1
#define IRQ_CASCADE         2
#define IRQ_COM2            3
#define IRQ_COM1            4
#define IRQ_LPT2            5
#define IRQ_FLOPPY          6
#define IRQ_LPT1            7
#define IRQ_RTC             8
#define IRQ_ACPI            9
#define IRQ_AVAILABLE1      10
#define IRQ_AVAILABLE2      11
#define IRQ_PS2_MOUSE       12
#define IRQ_FPU             13
#define IRQ_PRIMARY_ATA     14
#define IRQ_SECONDARY_ATA   15

/* IRQ base vector in the IDT */
#define IRQ_BASE            0x20

/* Maximum number of IRQs */
#define IRQ_COUNT           16

/* IRQ handler type */
typedef void (*t_irq_handler)(void);

/**
 * Initialize the IRQ system.
 */
void init_irq();

/**
 * Install a handler for the specified IRQ.
 * @param irq The IRQ number (0-15)
 * @param handler Function pointer to the handler
 */
void irq_install_handler(uint8_t irq, t_irq_handler handler);

/**
 * Uninstall the handler for the specified IRQ.
 * @param irq The IRQ number (0-15)
 */
void irq_uninstall_handler(uint8_t irq);

/**
 * Enable a specific IRQ.
 * @param irq The IRQ number (0-15)
 */
void irq_enable(uint8_t irq);

/**
 * Disable a specific IRQ.
 * @param irq The IRQ number (0-15)
 */
void irq_disable(uint8_t irq);