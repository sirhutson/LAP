#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "sysctl.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "i2c.h"
#include "pin_map.h"
#include "../inc/tm4c123gh6pm.h"


void i2c_setup(void);
void i2c_errorcheck(void);

