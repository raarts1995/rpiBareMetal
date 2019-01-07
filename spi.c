#include "spi.h"

SPI spi;

void spi_init() {
	spi.base = (int*)(SPI_BASE);
	spi.dataLen = 0;
	spi.dataRdy = 0;
	spi.base[SPI_CS] = 0;
	
	gpio_set_alt(9,  0);  //MISO
	gpio_set_alt(10, 0);  //MOSI
	gpio_set_alt(11, 0);  //CLK
	
	/*gpio_pud(9, GPIO_PUD_CLEAR);
	gpio_pud(10, GPIO_PUD_CLEAR);
	gpio_pud(11, GPIO_PUD_CLEAR);*/
}

void spi_set_clk_freq(unsigned int clk) {
	spi_set_clk_div(F_CPU/clk);
}

void spi_set_clk_div(int div) {
	spi.base[SPI_CLK] = (div & ~1); //div moet deelbaar zijn door 2 volgens datasheet
}

void spi_set_cspol(int cs, int pol) {
	if (cs > 1)
		return;
	if (pol) {
		spi.base[SPI_CS] |= (SPI_CSPOL0 << cs);
		spi.base[SPI_CS] |= (SPI_CSPOL);
	}
	else {
		spi.base[SPI_CS] &= ~(SPI_CSPOL0 << cs);
		spi.base[SPI_CS] &= ~(SPI_CSPOL);
	}
}

void spi_set_cpha(int pol) {
	if (pol)
		spi.base[SPI_CS] |= (SPI_CPHA);
	else
		spi.base[SPI_CS] &= ~(SPI_CPHA);
}

void spi_set_cpol(int pol) {
	if (pol)
		spi.base[SPI_CS] |= (SPI_CPOL);
	else
		spi.base[SPI_CS] &= ~(SPI_CPOL);
}

void spi_set_cs(int cs) {
	if (cs > 1)
		return;
	spi.base[SPI_CS] &= ~0x3;
	spi.base[SPI_CS] |= cs;
	
	gpio_set_alt(8 - cs, 0); //CS0 = 8, CS1 = 7
	//gpio_pud(8 - cs, GPIO_PUD_CLEAR);
}

//zonder interrupt
void spi_transfer(char* buf, int len) {
	spi.base[SPI_CS] |= SPI_TA | SPI_CLR_RXFIFO | SPI_CLR_TXFIFO;
	int i = 0;
	for (i = 0; i < len; i++) {
		while (!(spi.base[SPI_CS] & SPI_TXD)) ; //wacht tot er ruimte is in txfifo
		spi.base[SPI_FIFO] = buf[i];
		//uart_printf("spi xfer (%x): %x\r\n", *(spi.base), buf[i]);
		while (!(spi.base[SPI_CS] & SPI_DONE)) ; //wacht tot de byte verstuurd is
		buf[i] = 0;
		if (spi.base[SPI_CS] & SPI_RXD) //wacht tot er data in rx fifo staat
			buf[i] = spi.base[SPI_FIFO];
	}
	while (!(spi.base[SPI_CS] & SPI_DONE)) ;
	spi.base[SPI_CS] &= ~SPI_TA;
}

//interrupt functies
void spi_enable_interrupt() {
	RPI_GetIrqController()->Enable_IRQs_2 |= IRQ_2_ARM_SPI_IRQ;
}

void spi_handler() {
	if (spi.base[SPI_CS] & SPI_DONE) {
		if (spi.dataSend != spi.dataLen) {
			if (spi.dataSend > 0)
				spi.data[spi.dataSend-1] = spi.base[SPI_FIFO];
			spi.base[SPI_FIFO] = spi.data[spi.dataSend++];
		}
		else {
			spi.data[spi.dataLen-1] = spi.base[SPI_FIFO];
			spi.dataSend = 0;
			spi.base[SPI_CS] &= ~(SPI_TA);
			spi.dataRdy = 1;
			//deactiveer interrupts
			spi.base[SPI_CS] &= ~SPI_INTR;
			spi.base[SPI_CS] &= ~SPI_INTD;
		}
	}
}

void spi_write_int(char* buf, int len) {
	spi.dataLen = ((len > SPI_BUFSIZE) ? SPI_BUFSIZE : len);
	int i = 0;
	for (i = 0; i < spi.dataLen; i++)
		spi.data[i] = buf[i];
	
	//spi.base[SPI_CS] |= SPI_INTR;
	spi.base[SPI_CS] |= SPI_INTD;
	spi.base[SPI_CS] |= SPI_TA;
}

int spi_rdy_int() {
	if (spi.dataRdy) {
		spi.dataRdy = 0;
		return 1;
	}
	return 0;
}

void spi_read_int(char* buf, int len) {
	int dataLen = ((len > SPI_BUFSIZE) ? SPI_BUFSIZE : len);
	int i = 0;
	for (i = 0; i < spi.dataLen; i++)
		buf[i] = spi.data[i];
}

void spi_clear_rxfifo() {
	spi.base[SPI_CS] |= SPI_CLR_RXFIFO;
}

void spi_clear_txfifo() {
	spi.base[SPI_CS] |= SPI_CLR_TXFIFO;
}