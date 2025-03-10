#include <stdint.h>
#include "delay.h"

void delay_cycles(uint32_t cyc)
{
	for (uint32_t i = 0; i < cyc; i++) {	/* Wait a bit. */
		__asm__("nop");
	}
}
