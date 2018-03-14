#include "project.h"

uint32_t ms_counter; 
uint32_t a;
uint32_t period = 4000;  // this equates to 5ms.


// 1 tick is 62.5 nanoseconds based off 16MHz clock 1/16,000,000....

void loading() // This function cuts the red led on and off, totally unneccessary 
{
int i;

	for(i=0;i<10;i++)
		{
			SysCtlDelay(1000);  // Random delay I chose
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_PIN_1); //Red Light On
			SysCtlDelay(1000);  // Random delay I chose
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0); //Red Light Off
		}

}

void SysTick_Handler(void)
{
	ms_counter++;
}

void TIMER0A_Handler(void)
{
	TIMER0_ICR_R = 0x000001;  // acknowledges the timer timeout 
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,GPIO_PIN_3);
	//TIMER0_ICR_R |= (0x000001);  // acknowledges the timer timeout 
	printf("%d ms at interrupt\n\r",ms_counter);
	a = 1;
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,0);
}

int main()
{




   SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL| SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);  // FOR IMU

		
	
		Gpio_setup();		
		UART_setup();

		pwm_setup();            // for imu
		i2c_setup();
		ADC_setup();
		
		IMU_config_power();
		lux_confirmation(); // only needs to be done once when power is reset
		lux_setup();
	  systick_setup();
	  //timer0A_setup(period);
				
while (1)
		{

// FOR IMU - LAB		
			
//		if (ms_counter >= 5)
//			{
//				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,GPIO_PIN_2);
//				IMU_data();
//				IMU_STATUS();
//				update_roll(roll);
//				update_pitch(pitch);
//				update_yaw(heading);
//				print_IMU();
//				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
//				ms_counter = 0;
//			}
//			
//loading();
			
			
