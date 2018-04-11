#include "pwm_helper.h"
void pwm_setup()
{
		SYSCTL_RCGC0_R |= 0x00100000; // SYSCTL_RCGC0_PWM0;  // 1) Enable the PWM clock	
		SysCtlPWMClockSet(SYSCTL_PWMDIV_32);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
		
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
			{
			}
			
	
		
		GPIO_PORTB_AMSEL_R &= ~0xE0; // Disable analog
		GPIO_PORTB_DEN_R |= 0xE0; // PB2 Digital enabled
		GPIO_PORTB_DIR_R |= 0xE0; 
    GPIO_PORTB_AFSEL_R |= 0xE0; // PB4 - Alt. Funct.
		GPIO_PORTB_PCTL_R  |= GPIO_PCTL_PB5_M0PWM3;
		GPIO_PORTB_PCTL_R  |= GPIO_PCTL_PB6_M0PWM0;
		GPIO_PORTB_PCTL_R  |= GPIO_PCTL_PB7_M0PWM1;
//    // Module 0 PWM Generator 0,1
    PWM0_0_CTL_R = 0; // disable for config
		PWM0_1_CTL_R = 0; // disable for config
    PWM0_0_GENA_R = 0x0000008C;
		PWM0_1_GENA_R = 0x0000008C;
		PWM0_0_GENB_R = 0x080C;
		PWM0_1_GENB_R = 0x080C;
    PWM0_0_LOAD_R = 0xFC580; // This affects the frequency of the pulse. needed to do trial and error for correct value of 50hz 
		PWM0_1_LOAD_R = 0xFC580; 
    PWM0_0_CMPA_R = 0x0000063; // 50% duty. (12,500)
		PWM0_1_CMPA_R = 0x0000063;
    PWM0_0_CTL_R =  0x00000001; // enable
		PWM0_1_CTL_R =  0x00000001; 
   PWM0_ENABLE_R = PWM_ENABLE_PWM0EN|PWM_ENABLE_PWM1EN|PWM_ENABLE_PWM3EN; // Enables the output of 5,6,7
//		printf("pwm setup complete");		
	PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,1500); // This widths set will correspond to a specific postion
	PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,1500); //home location
	PWMPulseWidthSet(PWM0_BASE,PWM_OUT_3,1500);
}


void update_roll(double x)
{
		PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,(1500 + (x/.18))); // This widths set will correspond to a specific postion, PB6 
		//PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,(1500 + (x/.180))); // 90 degree change over .5m
	
}
	
void update_pitch(double y)
{
		PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,(1500 + (y/.18))); // This widths set will correspond to a specific postion, PB7
}
void update_yaw(double z)
{
	// Every increment for left is .1294 degrees and for right it is .103
	// may need to flip signs based on left/right rotation
	

		PWMPulseWidthSet(PWM0_BASE,PWM_OUT_3,(1500 + (z/.18))); // This widths set will correspond to a specific postion, PB5

}