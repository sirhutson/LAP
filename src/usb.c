#include "usb.h"


void usb_setup()
{
	SYSCTL_SRCR2_R &= (0<<16); // Must clear this reset bit before transferring to device mode
	SYSCTL_RCGCUSB_R |= 0x01; // Enables run clock for the usb
	//needs to be delay of 3 system clock cycles before accessing registers
	SYSCTL_RCGCGPIO_R |= 0x04; // Enables clock to port d because this has the D- and D+ pins
	GPIO_PORTD_PCTL_R |= 0x30; // Pins 4 and 5 are made to be usb data lines
}


void pin_config()
{
}



void endpoint_config()
{
}
