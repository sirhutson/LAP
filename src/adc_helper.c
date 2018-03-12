#include "adc_helper.h"

struct ADC_DATACONVERTED ADCconvertedinfo;
struct ADC_DATA ADCinfo;
//uint32_t ADC_Values[13];

void ADC_setup()
{	
//SYSCTL_RCGCADC_R |= 0x01;
//SYSCTL_RCGCGPIO_R |= 0x8;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
			{
			}		
	
//  GPIO_PORTD_AFSEL_R |= 0x07; //enable alt function on pins 0-3
//	GPIO_PORTD_DEN_R &= ~0x07; // Clear bits so that it will function as analog
//	GPIO_PORTD_AMSEL_R |= 0x07; // Analog function enabled and isolation turned off
//	
//  GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD0_AIN7; //PIN 0 is now analog in 
//	GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD1_AIN6; //PIN 1 is now analog in 
//	GPIO_PORTD_PCTL_R |= GPIO_PCTL_PD2_AIN5; //PIN 2 is now analog in 

	ADCReferenceSet(ADC0_BASE, ADC_REF_INT); 
	
	ADCSequenceDisable(ADC0_BASE, 0);
	
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0,ADC_CTL_CH7);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 1,ADC_CTL_CH6);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 2,ADC_CTL_CH5|ADC_CTL_END);
	
	

	ADCSequenceEnable(ADC0_BASE, 0);

}
    


void process_ADC()
{
	
	ADCProcessorTrigger(ADC0_BASE, 0);  // Trigger the sample sequence.

	while(ADCBusy(ADC0_BASE))
	{
	};

	ADCSequenceDataGet(ADC0_BASE, 0, (uint32_t *)&ADCinfo);  // Read the value from the ADC.


}
void print_ADC_DATA()
{
	ADCconvertedinfo.GAS = ADCinfo.GAS;  // .00080556 is found from a reference voltage of 3.3/4096 the resolution. multiply this by the result for the correct value
	ADCconvertedinfo.LEFTRIGHT = (ADCinfo.LEFTRIGHT/16)-1; //  then divided by 1000 moves the decimal place over 3 places correctly
	ADCconvertedinfo.UPDOWN = (ADCinfo.UPDOWN/16)-1;
	
	//Above is a really sloppy way to convert the values from the adc before they are printed
	printf("The information gathered from gas is %d\n\r", ADCinfo.GAS);
	printf("The information gathered from lr is %04x\n\r", ADCinfo.LEFTRIGHT);
	printf(" ud is %04x\n\r",ADCinfo.UPDOWN);
	
	printf("The information gathered from gas is %04x\n\r", ADCconvertedinfo.GAS);
	printf("The information gathered from lr is %04x\n\r", ADCconvertedinfo.LEFTRIGHT);
	printf(" ud is %04x\n\r",ADCconvertedinfo.UPDOWN);

}