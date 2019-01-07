#include "uart.h"

UART uart;

void uart_init() // UART initialization function
{
	uart.base = (char *)(UART_BASE);
	*(uart.base+UART_CNTL) &= ~0x10;                  // disable UART FIFO
	*(uart.base+UART_IMSC) |= 0x30;
	uart.indata = uart.inhead = uart.intail = 0;
	uart.inroom = UART_SBUFSIZE;
	uart.outdata = uart.outhead = uart.outtail = 0;
	uart.outroom = UART_SBUFSIZE;
	uart.txon = 0;
	
	gpio_set_alt(14, 0); //txd
	gpio_set_alt(15, 0); //rxd
}

void uart_enable_interrupt() {
	RPI_GetIrqController()->Enable_IRQs_2 |= IRQ_2_ARM_UART_IRQ;
}

/** @brief UART handler called upon interrupt */
void uart_handler()
{
	/************************************************************* 
	LAB ASSIGNEMENT: IMPLEMENT UART HANDLER HERE 
	*************************************************************/ 
	_lock();
	unsigned int mis = *(uart.base + UART_MIS); // read UART_MIS register
	if (mis & (1<<4)) // UART_MIS.bit4=RX interrupt
		uart_do_rx();
	if (mis & (1<<5)) // UART_MIS.bit5=TX interrupt
		uart_do_tx();
	_unlock();
}

/** @brief UART RX interrupt handler */
void uart_do_rx()                             
{
	/************************************************************* 
    LAB ASSIGNEMENT: IMPLEMENT RX INTERRUPT HANDLER HERE 
	*************************************************************/ 
	char c;
	c = *(uart.base+UART_UDR);
	uart.inbuf[uart.inhead++] = c;
	uart.inhead %= UART_SBUFSIZE;
	uart.indata++; uart.inroom--;
}

/** @brief UART TX interrupt handler */
void uart_do_tx()
{
	/************************************************************* 
	LAB ASSIGNEMENT: IMPLEMENT TX INTERRUPT UART HANDLER HERE 
	*************************************************************/ 
	char c;
	if (uart.outdata <= 0){ // if outbuf[ ] is empty
		*(uart.base+UART_IMSC) = 0x10; // disable TX interrupt
		uart.txon = 0; // turn off txon flag
		return;
	}
	c = uart.outbuf[uart.outtail++];
	uart.outtail %= UART_SBUFSIZE;
	*(uart.base+UART_UDR) = (int)c; // write c to DR
	uart.outdata--; uart.outroom++;
} 

/** @brief Return a char from UART */
char uart_getc()
{
	char c;
	while(uart.indata <= 0);                       // loop until uart.data > 0 READONLY
	c = uart.inbuf[uart.intail++];
	uart.intail %= UART_SBUFSIZE;
	// updating variables: must disable interrupts
	_lock();
	uart.indata--; uart.inroom++;
	_unlock();
	return c;
}

/** @brief Output a char to UART */
void uart_putc(char c)
{
	_lock();
	if (uart.txon){                                //if TX is on, enter c into outbuf[]
		uart.outbuf[uart.outhead++] = c;
		uart.outhead %= UART_SBUFSIZE;
		uart.outdata++; uart.outroom--;
		_unlock();
		return;
	}

	// txon==0 means TX is off => output c & enable TX interrupt
	// PL011 TX is riggered only if write char, else no TX interrupt
	int i = *(uart.base+UART_UFR); // read FR
	while( *(uart.base+UART_UFR) & 0x20 );            // loop while FR=TXF
	*(uart.base+UART_UDR) = (int)c;                   // write c to DR
	*(uart.base+UART_IMSC) |= 0x30;                   // 0000 0000: bit5=TX mask bit4=RX mask
	uart.txon = 1;
	_unlock();
}

/** @brief Get a line from UART */
void uart_gets(char *s) 
{
	while ((*s = (char)uart_getc()) != '\r'){
		uart_putc(*s++);
	}
	*s = 0;
}

/** @brief Output a string of chars */
void uart_prints(char *s) 					      // output a string of chars
{
	while (*s)
		uart_putc(*s++);
}


/******************************************************************************/
void uart_prb(int x)
{
	char c;
	if (x) {
		c = uart_tab[x & 1];
		uart_prb(x >> 1);
		uart_putc(c);
	}
}

void uart_printb(int x)
{
	if (x==0)
		uart_putc('0');
	else
		uart_prb(x);
}

void uart_prx(int x)
{
	char c;
	if (x){
		c = uart_tab[x % 16];
		uart_prx(x / 16);
		uart_putc(c);
	}
}

void uart_printx(int x)
{
	uart_prints("0x");
	if (x==0)
		uart_putc('0');
	else
		uart_prx(x);
}

void uart_pru(int x)
{
	char c;
	if (x){
		c = uart_tab[x % 10];
		uart_pru(x / 10);
		uart_putc(c);
	}
}

void uart_printu(int x)
{
	if (x==0)
		uart_putc('0');
	else
		uart_pru(x);
}

void uart_printi(int x)
{
	if (x<0){
		uart_putc('-');
		x = -x;
	}
	uart_printu(x);
}

void uart_printf(char *fmt,...)
{
	int *ip;
	char *cp;
	cp = fmt;
	ip = (int *)&fmt + 1;

	while(*cp){
		if (*cp != '%'){
			uart_putc( *cp);
			if (*cp=='\n')
				uart_putc('\r');
			cp++;
			continue;
		}
		cp++;
		switch(*cp){
			case 'c': uart_putc((char)*ip);     break;
			case 's': uart_prints((char *)*ip); break;
			case 'd': uart_printi(*ip);         break;
			case 'u': uart_printu(*ip);         break;
			case 'x': uart_printx(*ip);         break;
			case 'b': uart_printb(*ip);         break; //print binary
		}
		cp++; ip++;
	}
}

/******************************************************************************/
