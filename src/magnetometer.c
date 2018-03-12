#include "magnetometer.h"

struct MagnetometerRawData mag_ypr;
struct MagnetometerConvertedData mag_converted;


void MAG_config() // Set Establishes the necessary values for correct operation of gyro 
{	
	I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x02); //register to write
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}

	I2C0_MDR_R = (0x00); //continuous conversion mode
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x00); //register to write
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}

	I2C0_MDR_R = (0x90); //temp on and data output is 15hz
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	
	I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x01); //register to write
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}

	I2C0_MDR_R = (0x80); //gain setting
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}

	//read ira register to ensure mag i2c isn't into funny stuff
	
}

void MAG_X() // x Axis
{
	uint8_t xl;
	uint8_t xh;
  I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x03); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = mag_read; 
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}  
	xh = I2C0_MDR_R;
	I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x04); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = mag_read; 
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	xl = I2C0_MDR_R;
	mag_ypr.x = (xl|xh<<8);
	mag_converted.x = mag_ypr.x/4;
}

void MAG_Y() // Y Axis
{
	uint8_t yl;
	uint8_t yh;
  I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x07); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = mag_read; 
	I2C0_MCS_R = (0x07); // witches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	yh = I2C0_MDR_R;
	
  I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x08); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = mag_read; 
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	yl = I2C0_MDR_R;
	mag_ypr.y = (yl|yh<<8);
	mag_converted.y = mag_ypr.y/4;
}
void MAG_Z() // Z Axis
{
	uint8_t zl;
	uint8_t zh;
  I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x05); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = mag_read; 
	I2C0_MCS_R = (0x07); // witches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	zh = I2C0_MDR_R;
  I2C0_MSA_R = mag_write; // slave address write
	I2C0_MDR_R = (0x06); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	I2C0_MSA_R = mag_read; 
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	zl = I2C0_MDR_R;
	mag_ypr.z = (zl|zh<<8);
	mag_converted.z = mag_ypr.z/4;
}
void MAG_data()
{
	MAG_Z();
	MAG_Y();
	MAG_X();
}
