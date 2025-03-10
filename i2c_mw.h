/***
 *
 *
 *
 *
 ***/

#ifndef _I2C_MW_H_
#define _I2C_MW_H_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>

void i2c_setup(void);

//I2C write to specific device register
int i2c_reg_write(uint32_t hi2c, const uint8_t addr, uint8_t reg, uint8_t *buf,const uint8_t nbytes);

// read from specific device register
int i2c_reg_read(uint32_t hi2c, const uint8_t addr, uint8_t reg, uint8_t *buf,const uint8_t nbytes);


#endif //_I2C_MW_H_
