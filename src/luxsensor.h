#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "../inc/tm4c123gh6pm.h"
#include <math.h>

#define luxwrite 0x72  // slave address with the address select line floating
#define luxread 0x73  // slave read with floating address select line 

struct LUXinfo
{
	double data0;
	double data1;
	double lux;
};

void lux_setup(void);
void lux_confirmation(void); // want to make sure I can use regular i2c communication
void lux_data(void);

extern struct LUXinfo luxdata;
