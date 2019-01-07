#include "systimer.h"

int* systim_reg = (int*)SYSTIM_BASE;

void systim_waitus(unsigned int us) {
	unsigned int tstart = systim_reg[SYSTIM_CLO];
	while ((systim_reg[SYSTIM_CLO] - tstart) < us) ;
}

void systim_waitms(unsigned int ms) {
	int i;
	for (i = 0; i < ms; i++)
		systim_waitus(1000);
}

void systim_waits(unsigned int s) {
	int i;
	for (i = 0; i < s; i++)
		systim_waitms(1000);
}