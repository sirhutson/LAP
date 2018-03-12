#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "hw_memmap.h"

#include "hw_types.h"
#include "hw_can.h"
#include "hw_ints.h"
#include <stdbool.h>
#include "../inc/hw_memmap.h"
#include "../driverlib/sysctl.h"





#include "../driverlib/can.h"


#include "../driverlib/gpio.h"

#include "../driverlib/interrupt.h"

#include "../driverlib/pin_map.h"

#include "../driverlib/sysctl.h"

#include "../driverlib/uart.h"

#include "tm4c123gh6pm.h"
#include "../src/uart_helper.h"

#define NUM_RX_MESSAGES 7
#define NUM_TX_MESSAGES 7

// place a 1 by each message you would like to receive

#define MESSAGE1 0			
#define MESSAGE2 0
#define MESSAGE3 0 
#define MESSAGE4 0
#define MESSAGE5 0
#define MESSAGE6 0
#define MESSAGE7 0


extern unsigned char MsgData[NUM_RX_MESSAGES][4];

void initReceiver(void);
void CAN_Transmit(uint8_t data[4], uint8_t msgSelect);
void CANIntHandler(void);
void CAN_Init(void);
void Init_Structs(void);
