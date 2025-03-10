#include "i2c_mw.h"


void i2c_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOB);
   	//rcc_periph_clock_enable(RCC_GPIOH);
   	//rcc_set_i2c_clock_hsi(I2C1);

   	//i2c_reset(I2C1);
   	/* Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit. */
   	//gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
   	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO6 | GPIO7);
   	//gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, GPIO6 | GPIO7);
   	// it's important to set the pins to open drain
   	gpio_set_output_options(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, GPIO6 | GPIO7);
   	gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);
   	rcc_periph_clock_enable(RCC_I2C1);
   	i2c_peripheral_disable(I2C1);
   	//configure ANFOFF DNF[3:0] in CR1
   	//i2c_enable_analog_filter(I2C1);
   	//i2c_set_digital_filter(I2C1, 0);
   	/* HSI is at 8Mhz */
   	i2c_set_speed(I2C1, i2c_speed_sm_100k, 8);
   	//configure No-Stretch CR1 (only relevant in slave mode)
   	//i2c_enable_stretching(I2C1);
   	//addressing mode
   	//i2c_set_7bit_addr_mode(I2C1);
   	i2c_set_standard_mode(I2C1); // mcarter added 2021-11-23
   	i2c_peripheral_enable(I2C1);

}


int i2c_reg_write(uint32_t hi2c,const uint8_t addr, uint8_t reg, uint8_t *buf,const uint8_t nbytes)
{
	//int num_bytes_read = 0;
	uint8_t msg[nbytes + 1];

	// Check to make sure caller is sending 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	// Append register address to front of data packet
	msg[0] = reg;
	for (int i = 0; i < nbytes; i++) {
		msg[i + 1] = buf[i];
	}

	// Write data to register(s) over I2C
	i2c_transfer7(hi2c, addr, msg, (nbytes + 1), 0, 0);

	return nbytes;
}


int i2c_reg_read(uint32_t hi2c,const uint8_t addr, uint8_t reg,uint8_t *buf,const uint8_t nbytes)
{
	//int num_bytes_read = 0;

	// Check to make sure caller is asking for 1 or more bytes
	if (nbytes < 1) {
		return 0;
	}

	// Read data from register(s) over I2C
	i2c_transfer7(hi2c, addr, &reg, 1, buf, nbytes);
	return nbytes;
}

