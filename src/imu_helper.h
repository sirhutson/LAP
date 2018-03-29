// This library configures the BNO055 and processes its data

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "../driverlib/pin_map.h"
#include "../inc/tm4c123gh6pm.h"

//*****************************************************************************
// BNO055 Slave Address
//*****************************************************************************

#define bno_write 0x28      // proper data sheet proves this
#define bno_read  0x29      // proper data sheet proves this

//*****************************************************************************
// BNO055 REGISTERS
//*****************************************************************************

#define MAG_RAD_MSB   0x6A   // 
#define MAG_RAD_LSB   0x69   //
#define ACC_RAD_MSB   0x68   //
#define ACC_RAD_LSB   0x67   //
#define GYR_OFSTZ_MSB  0x66   // Z
#define GYR_OFSTZ_LSB  0x65   // Z
#define GYR_OFSTY_MSB  0x64   // Y
#define GYR_OFSTY_LSB  0x63   // Y 
#define GYR_OFSTX_MSB  0x62   // X
#define GYR_OFSTX_LSB  0x61   // X
#define MAG_OFSTZ_MSB  0x60   // Z
#define MAG_OFSTZ_LSB  0x5F   // Z
#define MAG_OFSTY_MSB  0x5E   // Y
#define MAG_OFSTY_LSB  0x5D   // Y 
#define MAG_OFSTX_MSB  0x5C   // X
#define MAG_OFSTX_LSB  0x5B   // X
#define ACC_OFSTZ_MSB  0x5A   // Z
#define ACC_OFSTZ_LSB  0x59   // Z
#define ACC_OFSTY_MSB  0x58   // Y
#define ACC_OFSTY_LSB  0x57   // Y 
#define ACC_OFSTX_MSB  0x56   // X
#define ACC_OFSTX_LSB  0x55   // X
#define TEMP_SOURCE    0x40   //
#define SYS_TRIGGER    0x3F   //
#define POWER_MODE     0x3E   //
#define OPR_MODE       0x3D   //
#define UNIT_SELECT    0x3B   //
#define SYS_ERROR      0x3A   // READ ONLY
#define SYS_STATUS     0x39   // READ ONLY
#define SYS_CLK_STAT   0x38   // READ ONLY
#define INT_STATUS     0x37   // READ ONLY
#define ST_RESULT      0x36   // READ ONLY
#define CALIB_STATUS   0x35   // READ ONLY
#define TEMPERATURE    0x34   // READ ONLY
#define GRV_Z_MSB      0x33   // READ ONLY
#define GRV_Z_LSB      0x32   // READ ONLY
#define GRV_Y_MSB      0x31   // READ ONLY
#define GRV_Y_LSB      0x30   // READ ONLY
#define GRV_X_MSB      0x2F   // READ ONLY
#define GRV_X_LSB      0x2E   // READ ONLY
#define LIA_Z_MSB      0x2D   // READ ONLY
#define LIA_Z_LSB      0x2C   // READ ONLY
#define LIA_Y_MSB      0x2B   // READ ONLY
#define LIA_Y_LSB      0x2A   // READ ONLY
#define LIA_X_MSB      0x29   // READ ONLY
#define LIA_X_LSB      0x28   // READ ONLY
#define QUAT_Z_MSB     0x27   // READ ONLY
#define QUAT_Z_LSB     0x26   // READ ONLY
#define QUAT_Y_MSB     0x25   // READ ONLY
#define QUAT_Y_LSB     0x24   // READ ONLY
#define QUAT_X_MSB     0x23   // READ ONLY
#define QUAT_X_LSB     0x22   // READ ONLY
#define QUAT_W_MSB     0x21   // READ ONLY
#define QUAT_W_LSB     0x20   // READ ONLY
#define EUL_PCH_MSB    0x1F   // READ ONLY
#define EUL_PCH_LSB    0x1E   // READ ONLY
#define EUL_RLL_MSB    0x1D   // READ ONLY
#define EUL_RLL_LSB    0x1C   // READ ONLY
#define EUL_HD_MSB     0x1B   // READ ONLY
#define EUL_HD_LSB     0x1A   // READ ONLY
#define GYR_Z_MSB      0x19   // READ ONLY
#define GYR_Z_LSB      0x18   // READ ONLY
#define GYR_Y_MSB      0x17   // READ ONLY
#define GYR_Y_LSB      0x16   // READ ONLY
#define GYR_X_MSB      0x15   // READ ONLY
#define GYR_X_LSB      0x14   // READ ONLY
#define MAG_Z_MSB      0x13   // READ ONLY
#define MAG_Z_LSB      0x12   // READ ONLY
#define MAG_Y_MSB      0x11   // READ ONLY
#define MAG_Y_LSB      0x10   // READ ONLY
#define MAG_X_MSB      0xF    // READ ONLY
#define MAG_X_LSB      0xE    // READ ONLY
#define ACC_Z_MSB      0xD    // READ ONLY
#define ACC_Z_LSB      0xC    // READ ONLY
#define ACC_Y_MSB      0xB    // READ ONLY
#define ACC_Y_LSB      0xA    // READ ONLY
#define ACC_X_MSB      0x9    // READ ONLY
#define ACC_X_LSB      0x8    // READ ONLY
#define PAGE_ID        0x7    // READ ONLY
#define BL_REV_ID      0x6    // READ ONLY
#define SW_REV_IDH     0x5    // READ ONLY
#define SW_REV_IDL     0x4    // READ ONLY
#define GYR_ID         0x3    // READ ONLY
#define MAG_ID         0x2    // READ ONLY
#define ACC_ID         0x1    // READ ONLY
#define CHIP_ID        0x0    // READ ONLY

struct IMU_euler
{
        int16_t x;  //roll
        int16_t y;  //pitch
        int16_t z;  //heading
};

void IMU_config_power(void);
void IMU_STATUS(void);
void IMU_data(void);


extern struct IMU_euler msb_lsb;