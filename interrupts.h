#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#include "defines.h"
#include "uart.h"
#include "gpio.h"

/** @brief See Section 7.5 of the BCM2836 ARM Peripherals documentation, the base
    address of the controller is actually xxxxB000, but there is a 0x200 offset
    to the first addressable register for the interrupt controller, so offset the
    base to the first register */
#define INTERRUPT_CONTROLLER_BASE   ( 0x2000B200 )

/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define BASIC_ARM_TIMER_IRQ         (1 << 0)
#define BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)

#define IRQ_2_ARM_I2C_IRQ		(1 << 21)
#define IRQ_2_ARM_SPI_IRQ		(1 << 22)
#define IRQ_2_ARM_PCM_IRQ		(1 << 23)
#define IRQ_2_ARM_UART_IRQ		(1 << 25)


/** @brief The interrupt controller memory mapped register set */
typedef struct {
    volatile uint32_t IRQ_basic_pending;
    volatile uint32_t IRQ_pending_1;
    volatile uint32_t IRQ_pending_2;
    volatile uint32_t FIQ_control;
    volatile uint32_t Enable_IRQs_1;
    volatile uint32_t Enable_IRQs_2;
    volatile uint32_t Enable_Basic_IRQs;
    volatile uint32_t Disable_IRQs_1;
    volatile uint32_t Disable_IRQs_2;
    volatile uint32_t Disable_Basic_IRQs;
} rpi_irq_controller_t;


extern rpi_irq_controller_t* RPI_GetIrqController( void );

#endif
