#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "sysctl.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "pwm.h"
#include "pin_map.h"
#include "../inc/tm4c123gh6pm.h"


void pwm_setup(void);
void update_roll(double x);
void update_pitch (double y);
void update_yaw (double z); // updates servo position