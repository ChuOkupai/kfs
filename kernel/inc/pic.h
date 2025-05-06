#pragma once
#include <stdint.h>

/* PIC I/O ports */
#define PIC1_COMMAND        0x20
#define PIC1_DATA           0x21
#define PIC2_COMMAND        0xA0
#define PIC2_DATA           0xA1

/* PIC commands */
#define PIC_EOI             0x20    /* End of interrupt */
#define PIC_READ_IRR        0x0A    /* Read Interrupt Request Register */
#define PIC_READ_ISR        0x0B    /* Read In-Service Register */

/* PIC initialization commands */
#define ICW1_ICW4           0x01    /* ICW4 needed */
#define ICW1_SINGLE         0x02    /* Single mode */
#define ICW1_INTERVAL4      0x04    /* Call address interval 4 */
#define ICW1_LEVEL          0x08    /* Level triggered mode */
#define ICW1_INIT           0x10    /* Initialization command */

#define ICW4_8086           0x01    /* 8086/88 mode */
#define ICW4_AUTO           0x02    /* Auto EOI */
#define ICW4_BUF_SLAVE      0x08    /* Buffered mode/slave */
#define ICW4_BUF_MASTER     0x0C    /* Buffered mode/master */
#define ICW4_SFNM           0x10    /* Special fully nested */

/**
 * Initialize and remap the PICs to avoid conflicts with CPU exceptions.
 * @param offset1 The new offset for master PIC (typically 0x20)
 * @param offset2 The new offset for slave PIC (typically 0x28)
 */
void pic_init(uint8_t offset1, uint8_t offset2);

/**
 * Send an End of Interrupt command to the PICs.
 * @param irq The IRQ number (0-15)
 */
void pic_send_eoi(uint8_t irq);

/**
 * Mask (disable) an IRQ line.
 * @param irq The IRQ number to mask (0-15)
 */
void pic_mask(uint8_t irq);

/**
 * Unmask (enable) an IRQ line.
 * @param irq The IRQ number to unmask (0-15)
 */
void pic_unmask(uint8_t irq);

/**
 * Disable all interrupts.
 */
void pic_disable();