#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "gpio.h"
#include "sysctl.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "adc.h"
#include "../inc/tm4c123gh6pm.h"

//*************************************************************************
// This function the values attached to the ADC pins into human readable 
// format in the form of volts. 
//*************************************************************************

struct ADC_DATA // RAW data if it is ever needed
{
	uint16_t LEFTRIGHT;
	uint16_t GAS;
	uint16_t UPDOWN;

};

struct ADC_DATACONVERTED
{
	uint8_t GAS;
	uint8_t LEFTRIGHT;
	uint8_t UPDOWN;
};

void ADC_setup(void); 
void process_ADC(void);
void print_ADC_DATA(void);


extern struct ADC_DATA ADCinfo;
extern struct ADC_DATACONVERTED ADCconvertedinfo;