/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include "ssd1306.h"
#include "fonts.h"

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
}

int main(void)
{
	int i;

	gpio_setup();

	ssd1306_Init(I2C1);
	ssd1306_Fill(Black);
	ssd1306_SetCursor(10,30);
	ssd1306_WriteString("Test",Font_11x18,White);
	ssd1306_DrawCircle(64,32,10,White);
	ssd1306_UpdateScreen(I2C1);

	/* Blink the LED (PC8) on the board. */
	while (1) {
		/* Using API function gpio_toggle(): */
		gpio_toggle(GPIOD, GPIO12);	/* LED on/off */
		for (i = 0; i < 500000; i++) {	/* Wait a bit. */
			__asm__("nop");
		}
	}

	return 0;
}
