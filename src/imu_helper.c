#include "imu_helper.h"
struct IMU_euler msb_lsb;

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
	
	
	I2C0_MSA_R = bno_write; // slave address write
I2C0_MDR_R = (UNIT_SELECT); //register to write, unit selection
I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (0x10); //value to write, puts bno055 in degrees and fahrenheit
	I2C0_MCS_R = (0x05); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}

}	


void IMU_data(void)
{
	uint8_t eph;
	uint8_t epl;
	
	uint8_t ehdh;
	uint8_t ehdl;
	
	uint8_t erh;
	uint8_t erl;
	
  I2C0_MSA_R = bno_write; // slave address write
	I2C0_MDR_R = (0x9E); //register to write, this is euler pitch low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = bno_read; 
	I2C0_MCS_R = (0x09); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	epl = I2C0_MDR_R;
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	eph = I2C0_MDR_R;
	
	
	I2C0_MSA_R = bno_write; // slave address write
	I2C0_MDR_R = (0x9C); //register to write, this is euler pitch low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = bno_read; 
	I2C0_MCS_R = (0x09); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	erl = I2C0_MDR_R;
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	erh = I2C0_MDR_R;
	
	I2C0_MSA_R = bno_write; // slave address write
	I2C0_MDR_R = (0x9A); //register to write, this is euler pitch low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = bno_read; 
	I2C0_MCS_R = (0x09); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	ehdl = I2C0_MDR_R;
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	ehdh = I2C0_MDR_R;
	
	msb_lsb.y = (epl|eph<<8);
	msb_lsb.z = (erl|erh<<8);
	msb_lsb.z = (ehdl|ehdh<<8);
	
}
// determine units ... done 
// output format based upon pitch for clock or counter clock... left as default. 
// i2c read access to make sure msb is not updated when lsb is read for accurate data... attempting incremental reading
// st_result holds info that start up was successful for each sensor ... not used yet
