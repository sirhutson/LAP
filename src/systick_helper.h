#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "sysctl.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "pin_map.h"
#include "../inc/tm4c123gh6pm.h"
#include "../driverlib/systick.h"



void systick_setup(void);
void timer0A_setup(uint32_t period);