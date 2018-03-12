#include "luxsensor.h"

struct LUXinfo luxdata;


void lux_confirmation()
{
	int f;
	
  I2C0_MSA_R = luxwrite; // slave address write
	I2C0_MDR_R = (0x80); //register to write, command register with control 0 in the command field
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x03); //register to write, ctrl1 register
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
  I2C0_MSA_R = luxwrite; // slave address read
	I2C0_MDR_R = (0x80);
	I2C0_MCS_R = (0x03); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	I2C0_MSA_R = luxread; 
	I2C0_MCS_R = (0x07);
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	f = I2C0_MDR_R;
	switch (f)
	{
		case 0x03 :
		printf("Lux configuration into normal power mode was successful\n\r");
		break; 
		
		case 0x00 :
		printf("Lux has been put into sleep mode\n\r");
		break; 
		
		default:
		printf("Need to use a different communication format\n\r");
		break;
	}
	
}

void lux_setup()
{
	
	I2C0_MSA_R = luxwrite; // slave address write
	I2C0_MDR_R = (0x81); //register to write, command register with control 0 in the command field
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x02); // 101 ms conversion rate
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	printf(" Lux has been properly configured for 101ms conversions scale is .0252\n\r");
}


void lux_data() // reads values from lux joint and now it needs to be converted to stuff
{
	uint8_t data0lo;
	uint8_t data0hi;
	uint8_t data1lo;
	uint8_t data1hi;
	double d0  = luxdata.data0;
	double d1 = luxdata.data1;
	double f = d1/d0;
	
	
  I2C0_MSA_R = luxwrite; // slave address write
	I2C0_MDR_R = (0x8C); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x03); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	I2C0_MSA_R = luxread; 
	I2C0_MCS_R = (0x07); // switches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	data0lo = I2C0_MDR_R;
	
	I2C0_MSA_R = luxwrite; // slave address write
	I2C0_MDR_R = (0x8D); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x03); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	I2C0_MSA_R = luxread; 
	I2C0_MCS_R = (0x07); // another byte received and sequence ends
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	data0hi = I2C0_MDR_R;
	
	I2C0_MSA_R = luxwrite; // slave address write
	I2C0_MDR_R = (0x8E); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x03); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	I2C0_MSA_R = luxread; 
	I2C0_MCS_R = (0x07); // witches from transmit to receive and receives 1 byte
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	data1lo = I2C0_MDR_R;
	
	I2C0_MSA_R = luxwrite; // slave address write
	I2C0_MDR_R = (0x8F); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x03); // writing 3 will be a start and run, puts in transmit mode
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	I2C0_MSA_R = luxread; 
	I2C0_MCS_R = (0x07); // another byte received and sequence ends
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	data1hi = I2C0_MDR_R;
	
	luxdata.data0 = (data0lo|data0hi<<8)* 0.252;
	luxdata.data1 = (data1lo|data1hi<<8)* 0.252;
	
		if ((f>0) && (f <= .50))
		{
				luxdata.lux = 0.0304 * (luxdata.data0 - 0.062) * luxdata.data0 * (pow(f,1.4));
		}
		if ((f>.50) && (f <= .61))
		{
				luxdata.lux = 0.0224 * (luxdata.data0 - 0.031) * luxdata.data1;
		}
		if ((f>.61) && (f <= .80))
		{
				luxdata.lux = 0.0128 * (luxdata.data0 - 0.0153) * luxdata.data1;
		}
		if ((f>.80) && (f <= 1.30))
		{
				luxdata.lux = 0.00146 * (luxdata.data0 - 0.00112) * luxdata.data1;
		}
		if (f>1.30)
		{
				luxdata.lux = 0;
		}

		
		printf("%f is the lux value\n\r", luxdata.lux);
}