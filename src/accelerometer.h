
//This is the header document for the accelerometer on my adafruit IMU

//*****************************************************************************
//
// Mostly neccessary libraries
//
//*****************************************************************************
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "../driverlib/pin_map.h"
#include "../inc/tm4c123gh6pm.h"


//*****************************************************************************
//
// ACCELEROMETER Slave Address
//
//*****************************************************************************

#define accel_write 0x32      // proper data sheet proves this
#define accel_read  0x33      // proper data sheet proves this
#define time 10

// Sesitivity values from the mechanical characteristics in the datasheet.
#define LA_SENSITIVITY_1  1    //g's  should multiply by 9.8m/s^2 I believe
#define LA_SENSITIVITY_2  .5    //datasheet says mg/lsb for units
#define LA_SENSITIVITY_4  .25
#define LA_SENSITIVITY_12  .0834

//******************************************************************************
//    ACCELEROMTER DATA TYPE
//******************************************************************************
struct AccelerometerRawData
{
        int16_t x;
        int16_t y;
        int16_t z;
};

struct AccelerometerConvertedData
{
        double x;
        double y;
        double z;
};
//*****************************************************************************
//
// ACCELEROMETER REGISTERS
//
//*****************************************************************************

#define CTRL_REG1_A       0x20  // Register has the data rate select, power mode and x,y,z axis enable
#define CTRL_REG2_A       0x21  // High Pass filter select, MSB's must be 0
#define CTRL_REG3_A       0x22  // Interrupt enable pin 1, boot status, i2 fifo,push-pull_open drain
#define CTRL_REG4_A       0x23  // Scale selection 2 G's etc. Endian selection, update mode
#define CTRL_REG5_A       0x24  // Reboot memory, Hi pass enable, fifo enable
#define CTRL_REG6_A       0x25  // Click interrupt and reboot memory PAD2
#define REFERENCE_A       0x26  // For interrupt generation, default 0
#define STATUS_REG_A      0x27  // Tells if new data is available on axis (x,y,z) or previous overwritten
#define OUT_X_L_A         0x28  // X-axis data two's complement
#define OUT_X_H_A         0x29  // X-axis data two's complement
#define OUT_Y_L_A         0x2A  // Y-axis data two's complement
#define OUT_Y_H_A         0x2B  // Y-axis data two's complement
#define OUT_Z_L_A         0x2C  // Z-axis data two's complement
#define OUT_Z_H_A         0x2D  // Z-axis data two's complement
#define FIFO_CTRL_REG_A   0x2E  // Choose mode of fifo
#define FIFO_SRC_REG_A    0x2F  // Info about fifo
#define INT1_CFG_A        0x30  // Interrupt configuration for x,y,z lines
#define INT1_SRC_A        0x31  // Dictates reason for interrupt
#define INT1_THS_A        0x32  // interrupt threshold, point its triggered
#define INT1_DUR_A 			  0x33  // how long interrupt will last
#define INT2_CFG_A        0x34  // interrupt configuration
#define INT2_SRC_A        0x35  // Dictates reason for interrupt
#define INT2_THS_A        0x36  // interrupt threshold
#define INT2_DUR_A 			  0x37  // how long it will last
#define CLICK_CFG_A       0x38  // interrupt for clicking action
#define CLICK_SRC_A       0x39  // dictates reason for click interrupt occuring
#define CLICK_THS_A       0x3A  // for click detection process
#define TIME_LIMIT_A      0x3B  // time period between clicks for double click to be valid
#define TIME_LATENT_A     0x3C  // time interval that starts after first click
#define TIME_WINDOW_A     0x3D  // max time that can pass before click detection starts

//*****************************************************************************
//
// Accelerometer Struct for status
//
//*****************************************************************************

struct Accelerometer
{
	uint8_t CTL_REG1A;
	uint8_t CTL_REG2A;
	uint8_t CTL_REG3A;
	uint8_t CTL_REG4A;
	uint8_t CTL_REG5A;
	uint8_t CTL_REG6A;
	uint8_t REFERANCEA;
	uint8_t STATUSREGA;
	uint8_t OUT_XLA;
	uint8_t OUT_XHA;
	uint8_t OUT_YLA;
	uint8_t OUT_YHA;
	uint8_t OUT_ZLA;
	uint8_t OUT_ZHA;
	uint8_t FIFO_CTRLA;
	uint8_t FIFO_SRCA;
	uint8_t IG_CFGA;
  uint8_t IG_SRCA;
  uint8_t IG_THSa;
	uint8_t IG_DURA;
	uint8_t IG2_CFGA;
	uint8_t IG2_SRCA;
	uint8_t IG2_THSA;
	uint8_t IG2_DURA;
	uint8_t CLICKCFGA;
	uint8_t CLICKSRCA;
	uint8_t CLICKTHSA;
	uint8_t TIME_LIM_A;
	uint8_t TIME_LAT_A; 
	uint8_t TIME_WIND_A;
};
	
//*****************************************************************************
//
// ACCELEROMETER Prototypes for API Functions
//
//*****************************************************************************

void ACCEL_normalpower(void);// must be done every power cycle because the chips default sleep mode after every boot
void ACCEL_config(void);
void ACCEL_status(void);
void ACCEL_Z(void);  //z 
void ACCEL_Y(void); //y
void ACCEL_X(void);  //x
void ACCEL_data(void); //x,y,z

void print_accel_status(struct Accelerometer * accel);


extern struct Accelerometer ACCELSTATUS;
extern struct AccelerometerRawData accel_ypr; 
extern struct AccelerometerConvertedData accel_converted;
