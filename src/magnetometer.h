
//This is the header document for the magnetometer on my adafruit IMU

//*****************************************************************************
//
// Mostly neccessary libraries
//
//*****************************************************************************
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include "../inc/tm4c123gh6pm.h"


//*****************************************************************************
//
// MAGNETOMETER Slave Address
//
//*****************************************************************************

#define mag_write 0x3C      // proper data sheet proves this
#define mag_read  0x3D      // proper data sheet proves this
#define time 10

// Gain values from the mechanical characteristics in the datasheet. weirdly listed will revisit
#define MAG_GAIN_1100  1100 //1.3    gauss  LSB/gauss for units for xy
#define MAG_GAIN_980    980 //1.3   gauss for z 
#define MAG_GAIN_855    855 //1.9   for xy
#define MAG_GAIN_760    760 //1.9   for z
#define MAG_GAIN_670    670 //2.5   for xy
#define MAG_GAIN_600    600 //2.5   for z             gain
#define MAG_GAIN_450    450 //4.0   for xy
#define MAG_GAIN_400		400 //4.0		for z
#define MAG_GAIN_400		400 //4.7		for xy
#define MAG_GAIN_355		355 //4.7		for z
#define MAG_GAIN_330		330 //5.6		for xy
#define MAG_GAIN_295		295 //5.6		for z
#define MAG_GAIN_230    230 //8.1		for xy
#define MAG_GAIN_205    205 //8.1		for z

//******************************************************************************
//    MAGNETOMETER DATA TYPE
//******************************************************************************
struct MagnetometerRawData
{
       int16_t x;   // int gives me -1 and uint gives me 65535
       int16_t y;
       int16_t z;
};

struct MagnetometerConvertedData
{
        double x;
        double y;
        double z;
};
//*****************************************************************************
//
// MAGNETOMETER REGISTERS
//
//*****************************************************************************

#define CTRL_REG1_M       0x00  // Register has the data rate select, power mode and x,y,z axis enable
#define CTRL_REG2_M       0x01  // High Pass filter select, MSB's must be 0
#define MODE_REG_M        0x02  // Interrupt enable pin 1, boot status, i2 fifo,push-pull_open drain
#define OUT_X_L_M         0x03  // X-axis data two's complement
#define OUT_X_H_M         0x04  // X-axis data two's complement
#define OUT_Y_L_M         0x05  // Y-axis data two's complement
#define OUT_Y_H_M         0x06  // Y-axis data two's complement
#define OUT_Z_L_M         0x07  // Z-axis data two's complement
#define OUT_Z_H_M         0x08  // Z-axis data two's complement
#define SR_REG_M          0x09  // Choose mode of fifo
#define IRA_REG_M         0x0A  // Info about fifo
#define IRB_REG_M         0x0B  // Interrupt configuration for x,y,z lines
#define IRC_REG_M         0x0C  // Dictates reason for interrupt
#define TEMP_OUT_H_M      0x31  // interrupt threshold, point its triggered
#define TEMP_OUT_L_M      0x32  // how long interrupt will last

//*****************************************************************************
//
// Magnetometer Struct for status
//
//*****************************************************************************

struct Magnetometer
{
	uint8_t CTL_REG1M;
	uint8_t CTL_REG2M;
	uint8_t MODE_REGM;
	uint8_t OUT_XLM;
	uint8_t OUT_XHM;
	uint8_t OUT_YLM;
	uint8_t OUT_YHM;
	uint8_t OUT_ZLM;
	uint8_t OUT_ZHM;
	uint8_t SR_REGM;
	uint8_t IRA_REGM;
	uint8_t IRB_REGM;
	uint8_t IRC_REGM;
	uint8_t TEMP_HM;
	uint8_t TEMP_LM;

};
	
//*****************************************************************************
//
// MAGNETOMETER Prototypes for API Functions
//
//*****************************************************************************


void MAG_config(void);

void MAG_Z(void);  //z 
void MAG_Y(void); //y
void MAG_X(void);  //x
void MAG_data(void); //x,y,z





extern struct MagnetometerRawData mag_ypr; 
extern struct MagnetometerConvertedData mag_converted; 
