#ifndef DEFINES_H
#define DEFINES_H

#define F_CPU          250000000 //250MHz

#define SYSTIM_BASE    0x20003000
#define SYSTIM_CS      0
#define SYSTIM_CLO     1
#define SYSTIM_CHI     2

#define GPIO_BASE      0x20200000
#define GPIO_GPFSEL0   0
#define GPIO_GPFSEL1   1
#define GPIO_GPFSEL2   2
#define GPIO_GPSET0    7
#define GPIO_GPCLR0    10
#define GPIO_GPLEV0    13
#define GPIO_GPEDS0    16    
#define GPIO_GPREN0    19
#define GPIO_GPFEN0    22
#define GPIO_GPPUD     37
#define GPIO_GPPUDCLK0 38

#define UART_BASE      0x20201000
#define UART_UDR       0x00
#define UART_UDS       0x04
#define UART_RXFE      0x10
#define UART_UFR       0x18
#define UART_TXFF      0x20
#define UART_CNTL      0x2C
#define UART_IMSC      0x38
#define UART_MIS       0x40
#define UART_SBUFSIZE  128

#define SPI_BASE       0x20204000
#define SPI_CS         0
#define SPI_FIFO       1
#define SPI_CLK        2
#define SPI_DLEN       3
#define SPI_CPHA       (1 << 2)
#define SPI_CPOL       (1 << 3)
#define SPI_CLR_TXFIFO (1 << 4)
#define SPI_CLR_RXFIFO (1 << 5)
#define SPI_CSPOL      (1 << 6)
#define SPI_TA         (1 << 7)
#define SPI_INTD       (1 << 9)
#define SPI_INTR       (1 << 10)
#define SPI_ADCS       (1 << 11)
#define SPI_DONE       (1 << 16)
#define SPI_RXD        (1 << 17)
#define SPI_TXD        (1 << 18)
#define SPI_RXR        (1 << 19)
#define SPI_RXF        (1 << 20)
#define SPI_CSPOL0     (1 << 21)
#define SPI_CSPOL1     (1 << 22)
#define SPI_CSPOL2     (1 << 23)
#define SPI_BUFSIZE    16

#define I2C_BASE       0x20804000 //=BSC1. BSC0=0x20205000
#define I2C_C          0
#define I2C_S          1
#define I2C_DLEN       2
#define I2C_A          3
#define I2C_FIFO       4
#define I2C_DIV        5
#define I2C_READ       (1 << 0)
#define SPI_CLR_TXFIFO (1 << 4)
#define SPI_CLR_RXFIFO (1 << 5)
#define I2C_ST         (1 << 7)
#define I2C_INTD       (1 << 8)
#define I2C_INTT       (1 << 9)
#define I2C_INTR       (1 << 10)
#define I2C_I2CEN      (1 << 15)
#define I2C_TA         (1 << 0)
#define I2C_DONE       (1 << 1)
#define I2C_TXD        (1 << 4)
#define I2C_RXD        (1 << 5)
#endif