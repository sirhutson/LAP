#include "i2c_helper.h"

void i2c_setup(void)
{

	SYSCTL_RCGCI2C_R |= (1<<0); // Using I2C0 module
	SYSCTL_RCGCGPIO_R |= (1<<1); // Enable clock to PortB
	GPIO_PORTB_AFSEL_R |= (0x06<<1); //enable alt function on pins 2 and 3
		
	GPIO_PORTB_AFSEL_R |= (0x06<<1); //enable alt function on pins 2 and 3
	
	
	GPIO_PORTB_ODR_R |= (1<<3); // Open drain on pb3
	GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB2_I2C0SCL; //PIN 2 is now serial clock 
	GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_I2C0SDA; //PIN 3 is now serial data
	GPIO_PORTB_CR_R |= (0x06<<1);
	I2CMasterEnable(I2C0_BASE);  //Initialize master to do work and stuff
   
	I2C0_MTPR_R = 0x09; //Correct clock speed for fast mode a 3 would be fast mode plus
}
