#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "sysctl.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "adc.h"
#include "pin_map.h"
#include "../inc/tm4c123gh6pm.h"



void usb_setup();
void endpoint_config();
void pin_config();
