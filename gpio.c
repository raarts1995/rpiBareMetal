#include "gpio.h"

volatile unsigned int* gpio_reg = (unsigned int*)GPIO_BASE;

//set alternative function of a pin
void gpio_set_alt(int x, int alt) {
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
	
	if (alt < 4)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= ((0x4 | alt) << bit);
	else if (alt == 4)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x3 << bit);
	else if (alt == 5)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x2 << bit);
}

void gpio_pinmode(int x, int io) {
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
	if (io)
		gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x1 << bit);
}

void gpio_set_output(int x){
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
	gpio_reg[GPIO_GPFSEL0 + (x/10)] |= (0x1 << bit);
}

void gpio_set_input(int x) {
	int bit = (x%10)*3;
	gpio_reg[GPIO_GPFSEL0 + (x/10)] &= ~(0x7 << bit);
}

void gpio_write_pin(int x, int s) {
	if (s)
		gpio_set_pin(x);
	else
		gpio_clear_pin(x);
}

void gpio_set_pin(int x){
	gpio_reg[GPIO_GPSET0 + (x/32)] |= (1 << (x%32));
}

void gpio_clear_pin(int x) {
	gpio_reg[GPIO_GPCLR0 + (x/32)] |= (1 << (x%32));
}

int gpio_read_pin(int x) {
	return ((gpio_reg[GPIO_GPLEV0 + (x/32)] >> (x%32)) & 0x1);
}

int gpio_read_event(int x) {
	int set = ((gpio_reg[GPIO_GPEDS0 + (x/32)] >> (x%32)) & 0x1);
	if (set)
		gpio_reg[GPIO_GPEDS0 + (x/32)] |= (1 << (x%32));
	return set;
}

void gpio_set_edge_detect(int x, int ed) {
	gpio_reg[GPIO_GPREN0 + (x/32)] &= ~(1 << (x%32));
	gpio_reg[GPIO_GPFEN0 + (x/32)] &= ~(1 << (x%32));
	
	if (ed & GPIO_RISING_EDGE)
		gpio_reg[GPIO_GPREN0 + (x/32)] |= (1 << (x%32));
	if (ed & GPIO_FALLING_EDGE)
		gpio_reg[GPIO_GPFEN0 + (x/32)] |= (1 << (x%32));
}

//set the pullup/down resistor on the given gpio pin
void gpio_pud(int x, int ud) {
	if (ud > 2)
		return;
	gpio_reg[GPIO_GPPUD] = ud;
	int i = 0;
	for (i = 0; i < 150; i++) ; //150 clock cycles
	gpio_reg[GPIO_GPPUDCLK0 + (x/32)] |= (1 << (x%32));
	for (i = 0; i < 150; i++) ;
	gpio_reg[GPIO_GPPUD] = 0;
	gpio_reg[GPIO_GPPUDCLK0 + (x/32)] = 0;
}
