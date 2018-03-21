#include "imu_helper.h"


void IMU_config_power(void)
{
I2C0_MSA_R = bno_write; // slave address write
I2C0_MDR_R = (POWER_MODE); //register to write, power register
I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (0x00); //value to write, puts bno055 in normal power mode
	I2C0_MCS_R = (0x05); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
I2C0_MSA_R = bno_write; // slave address write
I2C0_MDR_R = (OPR_MODE); //register to write, power register
I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
// imu mode is 0x08
// compass mode is 0x09
// ndof is 0x0C probably the preferred mode we will use despite higher current consumption
	
	I2C0_MDR_R = (0x0C); //value to write, puts bno055 into NDOF mode 
	I2C0_MCS_R = (0x05); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
}	

// determine units
// output format based upon pitch for clock or counter clock
// i2c read access to make sure msb is not updated when lsb is read for accurate data
// st_result holds info that start up was successful for each sensor