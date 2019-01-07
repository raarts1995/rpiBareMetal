#ifndef SPI_H
#define SPI_H

#include "defines.h"
#include "gpio.h"
#include "uart.h"
#include "interrupts.h"

typedef volatile struct spi{
	int* base;
	char data[SPI_BUFSIZE];
	int dataLen, dataSend;
	int dataRdy;
} SPI;

extern SPI spi;

void spi_init();
void spi_set_clk_freq(unsigned int clk);
void spi_set_clk_div(int div);
void spi_set_cspol(int cs, int pol);
void spi_set_cpha(int pol);
void spi_set_cpol(int pol);
void set_cs(int cs);
void spi_transfer(char* buf, int len);
void spi_enable_interrupt();
void spi_handler();
void spi_write_int(char* buf, int len);
int spi_rdy_int();
void spi_read_int(char* buf, int len);
void spi_clear_rxfifo();
void spi_clear_txfifo();

#endif