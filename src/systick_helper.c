#include "systick_helper.h"

void systick_setup()
{
	NVIC_ST_CTRL_R = 0; // Disable systick while initializing
	NVIC_ST_RELOAD_R = 80000; // 1ms is 1,000,000ns and  1,000,000/62.5= 16,000 this should be 1ms
	NVIC_ST_CURRENT_R = 0; // Clears current value
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF)|0x40000000; // priority 2
	NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts	
}


void timer0A_setup(uint32_t period)
{
	SYSCTL_RCGCTIMER_R |= 0x01;  // timer 0 active
	TIMER0_CTL_R &= ~0x00000000;   // disable timer during setup
	TIMER0_CFG_R = 0x00000000;   // configure for 32 bit mode
	TIMER0_TAMR_R =0x00000002;   // configure for periodic mode
	//TIMER0_CTL_R &= ~(0x000C);  // rising edge triggered
	TIMER0_TAILR_R = period-1;  // reload value
	TIMER0_TAPR_R = 0;           // bus clock resolution
	TIMER0_ICR_R  = 0x00001;     // clear timer0 timeout flag
  TIMER0_IMR_R  = 0x00001;     // arm timeout interrupt
	
	
	NVIC_PRI4_R   = (NVIC_PRI4_R&0x00FFFFFF)| 0x80000000; // priority 3
	NVIC_EN0_R = 1<<19;          // enable IRQ 23 in NVIC
	TIMER0_CTL_R  = 0x0000001;   // enable timer0 
}
