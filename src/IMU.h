//This is the combined library for the IMU. It will at least make my main code look clean
//Not sure if it will be beneficial in terms of speed and clock cycles. 
#pragma once
#include "magnetometer.h"
#include "accelerometer.h"
#include "L3GD20.h"
#include <stdint.h>
#include <math.h>



void IMU_config_power(void);
void IMU_STATUS(void);
void IMU_data(void);
void print_IMU(void);
void get_referenceframe(void);


extern double roll;
extern double pitch;
extern double yaw;
extern double heading;