//This is the header document for the gyroscope on my adafruit IMU

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
// L3GD20  Slave Address
//
//*****************************************************************************
#define L3GD20_POLL_TIMEOUT      100         // Maximum number of read attempts
#define L3GD20H_ID      0xD7
#define time 10
// Sesitivity values from the mechanical characteristics in the datasheet.
#define GYRO_SENSITIVITY_250DPS  .00875005
#define GYRO_SENSITIVITY_500DPS  .01749999
#define GYRO_SENSITIVITY_2000DPS .0700035

//******************************************************************************
//    OPTIONAL SPEED SETTINGS
//******************************************************************************
    typedef enum
    {
      GYRO_RANGE_250DPS  = 250,
      GYRO_RANGE_500DPS  = 500,
      GYRO_RANGE_2000DPS = 2000
    } gyroRange_t;

//******************************************************************************
//    GYROSCOPE DATA TYPE
//******************************************************************************
struct gyroRawData
{
        int16_t x;
        int16_t y;
        int16_t z;
};

struct gyroConvertedData
{
        double x;
        double y;
        double z;
};
//*****************************************************************************
//
// L3GD20 REGISTERS
//
//*****************************************************************************
#define gyro_write 0xD6      // proper data sheet proves this
#define gyro_read  0xD7       /// proper data sheet proves this

#define WHO_AM_I      0x0F  // Device identification register
																										// Default value 11010100
#define CTRL_REG1     0x20  // Register has the data rate select, power mode and x,y,z axis enable
#define CTRL_REG2     0x21  // High Pass filter select, MSB's must be 0
#define CTRL_REG3     0x22  // Interrupt enable pin 1, boot status, i2 fifo,push-pull_open drain
#define CTRL_REG4     0x23  // Scale selection 250 dps etc. Endian selection, update mode
#define CTRL_REG5     0x24 // Reboot memory, Hi pass enable, fifo enable
#define REFERENCE     0x25  // For interrupt generation, default 0
#define OUT_TEMP      0x26  // Temperature information,internal thermometer
#define STATUS_REG    0x27  // tells if new information overwritten previous data
#define OUT_X_L       0x28  // X-axis data two's complement
#define OUT_X_H       0x29  // X-axis data two's complement
#define OUT_Y_L       0x2A  // Y-axis data two's complement
#define OUT_Y_H       0x2B  // Y-axis data two's complement
#define OUT_Z_L       0x2C  // Z-axis data two's complement
#define OUT_Z_H       0x2D  // Z-axis data two's complement
#define FIFO_CTRL_REG 0x2E  // Choose mode of fifo
#define FIFO_SRC_REG  0x2F  // Info about fifo
#define INT1_CFG      0x30  // Interrupt configuration for 1
#define INT1_SRC      0x31  // interrupt source register. read only
#define INT1_THS_XH   0x32  // interrupt threshold for x_h
#define INT1_THS_XL   0x33  // interrupt threshold for x_l
#define INT1_THS_YH   0x34  // interrupt threshold for y_h
#define INT1_THS_YL   0x35  // interrupt threshold for y_l
#define INT1_THS_ZH   0x36  // interrupt threshold for z_h
#define INT1_THS_ZL   0x37  // interrupt threshold for z_l
#define INT1_DURATION 0x38  // setup count down for interrupt
#define LOW_ODR       0x39  // 


//*****************************************************************************
//
// L3GD20 Struct for status
//
//*****************************************************************************

struct L3GD20
{
//	uint8_t WHO_AMI;
//	uint8_t RFU[16];
	uint8_t CTL_REG1;
	uint8_t CTL_REG2;
	uint8_t CTL_REG3;
	uint8_t CTL_REG4;
	uint8_t CTL_REG5;
	uint8_t REF;
	uint8_t OUTTEMP;
	uint8_t STATUS;
	uint8_t OUT_XL;
	uint8_t OUT_XH;
	uint8_t OUT_YL;
	uint8_t OUT_YH;
	uint8_t OUT_ZL;
	uint8_t OUT_ZH;
	uint8_t FIFO_CTRL;
	uint8_t FIFO_SRC;
	uint8_t IG_CFG;
	uint8_t IG_SRC;
	uint8_t IG_THS_XH;
	uint8_t IG_THS_XL;
	uint8_t IG_THS_YH;
	uint8_t IG_THS_YL;
	uint8_t IG_THS_ZH;
	uint8_t IG_THS_ZL;
	uint8_t IG_DURATION;
	uint8_t LOWODR;
};
	
//*****************************************************************************
//
// L3GD20 Prototypes for API Functions
//
//*****************************************************************************

void GYRO_normalpower(void);// must be done every power cycle because the chips default sleep mode after every boot
void GYRO_config(void);
void GYRO_status(void);
void GYRO_yaw(void);  //z 
void GYRO_pitch(void); //y
void GYRO_roll(void);  //x
void GYRO_data(void); //x,y,z


void print_gyro_status(struct L3GD20 * gyro);


extern struct L3GD20 GYROSTATUS;
extern struct gyroRawData gyro_ypr; 
extern struct gyroConvertedData gyro_converted;


