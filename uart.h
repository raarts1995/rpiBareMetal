#ifndef UART_H
#define UART_H

#include "defines.h"
#include "gpio.h"
#include "interrupts.h"

static char *uart_tab = "0123456789ABCDEF";

/** @brief The UART variable set*/
typedef volatile struct uart{
	char *base;                               			// base address; as char *
	int n;                                    			// uart number 0-3
	char inbuf[UART_SBUFSIZE];
	int indata, inroom, inhead, intail;
	char outbuf[UART_SBUFSIZE];
	int outdata, outroom, outhead, outtail;
	volatile int txon;                        			// 1=TX interrupt is on
}UART;

extern UART uart;                               				// UART structure

void uart_init();
void uart_enable_interrupt();
void uart_handler();
void uart_gets(char *s); 					// get a line from UART
void uart_printf(char *fmt, ...);

void uart_do_rx();                             // RX interrupt handler
void uart_do_tx();                             // TX interrupt handler
char uart_getc(); 							// return a char from UART
void uart_putc(char c); 					// output a char to UART
void uart_prints(char *s); 					// output a string of chars
void uart_prb(int x);
void uart_printb(int x);
void uart_prx(int x);
void uart_printx(int x);
void uart_pru(int x);
void uart_printu(int x);
void uart_printi(int x);

#endif