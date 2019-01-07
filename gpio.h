#ifndef GPIO_H
#define GPIO_H

#include "defines.h"

#define ACT_LED 47 //https://raspberrypi.stackexchange.com/questions/67431/cant-turn-on-act-led-on-baremetal-pi3

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define GPIO_PUD_CLEAR 0
#define GPIO_PULLDOWN 1
#define GPIO_PULLUP 2

#define GPIO_ED_CLEAR 0
#define GPIO_RISING_EDGE 1
#define GPIO_FALLING_EDGE 2

void gpio_set_alt(int x, int alt);
void gpio_pinmode(int x, int io);
void gpio_set_output(int x);
void gpio_set_input(int x);
void gpio_write_pin(int x, int s);
void gpio_set_pin(int x);
void gpio_clear_pin(int x);
int gpio_read_pin(int x);
int gpio_read_event(int x);
void gpio_set_edge_detect(int x, int ed);
void gpio_pud(int x, int ud);
#endif
