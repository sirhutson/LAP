#include "gpio_helper.h"

	//This function sets up GPIO pins
void Gpio_setup()
	{
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);  // Enables the use of PORTF
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);  // Enables the use of PORTE
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);  // Enables the use of PORTA
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);  // Enables the use of PORTD
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  // Enables the use of PORTB
		
			GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // Defines the RGB Leds as outputs
			GPIOPinTypeGPIOInput (GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);  // Defines the two on board switches as inputs
	//		GPIOPinTypeGPIOInput (GPIO_PORTD_BASE, GPIO_PIN_6);  // Adds port d to be used for the two MOM switches
			
			GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);
GPIOPinTypeADC(GPIO_PORTD_BASE,GPIO_PIN_1);
		GPIOPinTypeADC(GPIO_PORTD_BASE,GPIO_PIN_0);
		GPIOPinTypeADC(GPIO_PORTD_BASE,GPIO_PIN_2); 
		
			// The code below unlocks the buttons and sets the drive strength, this was taken from a TIVA example file
			HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
			HWREG(GPIO_PORTF_BASE + GPIO_O_CR)  = 0x01;
			HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
		
			// Port B will be used for PWM control 
			// PB5 = x axis, PB6 = y axis, PB7 = z axis
		
		
//		  // Port D unlocked below
			HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
			HWREG(GPIO_PORTD_BASE + GPIO_O_CR)  = 0x01;
			HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
//			
//			GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
//			GPIOPinConfigure(GPIO_PB5_M0PWM3);
//			GPIOPinConfigure(GPIO_PB6_M0PWM0);
//			GPIOPinConfigure(GPIO_PB7_M0PWM1);
//		
		
		
			GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
			GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);


			GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_2,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);    
			GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_3,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
		
		
//			GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); // This enables the pull up resistors on pin 6 and 7 
//			GPIODirModeSet(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_DIR_MODE_IN);												 // of portD and prevents needing to power and add 
//																																																		   // resistors to the external mom switches.
	

	} 

	//This function retrieves the GPIO data
void process_GPIO()
	{
		//code here.
	} 

	//This function prints the GPIO_DATA  
	//in a human readable format to the terminal
void print_GPIO_data()
	{
		// maybe create an array and have the value printed/sent to the uart port?
		//Uart must be initialized first.
		//code here.
	} 
		