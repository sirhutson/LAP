#include "accelerometer.h"

struct Accelerometer ACCELSTATUS;
struct AccelerometerRawData accel_ypr;
struct AccelerometerConvertedData accel_converted;

void ACCEL_normalpower()
{
	int f;
	
  I2C0_MSA_R = accel_write; // slave address write
	I2C0_MDR_R = (CTRL_REG1_A); //register to write, ctrl1 register
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (0x57); //value to write, puts ACCEL in normal power mode at 100hz
	I2C0_MCS_R = (0x05); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	

  I2C0_MSA_R = accel_write; // slave address write
	I2C0_MDR_R = (CTRL_REG1_A); //register to write, ctrl1 register
	I2C0_MCS_R = (0x0B); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
  I2C0_MSA_R = accel_read; // slave address read
	I2C0_MCS_R = (0x07); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	f = I2C0_MDR_R;
	switch (f)
	{
		case 0x57:
		printf("ACCEL configuration into normal power mode was successful\n\r");
		break; 
		
		default:
		printf("ACCEL is NOT configured properly\n\r");
		break;
	}
}

void ACCEL_config() // Set Establishes the necessary values for correct operation of gyro 
{
  I2C0_MSA_R = accel_write; // slave address write
	I2C0_MDR_R = (CTRL_REG2_A); //register to write
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (0x00); //value to write, sets bandwidth and output data rate, 100hz = odr
	I2C0_MCS_R = (0x05); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (CTRL_REG3_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CTRL_REG4_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x08); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CTRL_REG5_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CTRL_REG6_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (REFERENCE_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (STATUS_REG_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (FIFO_CTRL_REG_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_CFG_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_SRC_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_DUR_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT2_CFG_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT2_SRC_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT2_THS_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT2_DUR_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CLICK_CFG_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CLICK_SRC_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CLICK_THS_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (TIME_LIMIT_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (TIME_LATENT_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (TIME_WINDOW_A); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
}

void ACCEL_X() // x Axis
{
	uint8_t xl;
	uint8_t xh;
	
	
  I2C0_MSA_R = accel_write; // slave address write
	
	I2C0_MDR_R = (0xA8); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	
	I2C0_MSA_R = accel_read; 
	I2C0_MCS_R = (0x09); // switches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	xl = I2C0_MDR_R;
	
	I2C0_MCS_R = (0x07); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	xh = I2C0_MDR_R;
	

	accel_ypr.x = (xl|xh<<8);
	accel_converted.x = (.0098066 * (accel_ypr.x))/20; 
}

void ACCEL_Y() // Y Axis
{
	uint8_t yl;
	uint8_t yh;
	
  I2C0_MSA_R = accel_write; // slave address write
	
	I2C0_MDR_R = (0xAA); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	
	I2C0_MSA_R = accel_read; 
	I2C0_MCS_R = (0x09); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	yl = I2C0_MDR_R;
	

	I2C0_MCS_R = (0x07); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	yh = I2C0_MDR_R;
	

	accel_ypr.y = (yl|yh<<8);
	accel_converted.y = (.0098066 * (accel_ypr.y))/20;
}

void ACCEL_Z() // Z Axis
{
	uint8_t zl;
	uint8_t zh;
	
  I2C0_MSA_R = accel_write; // slave address write
	
	I2C0_MDR_R = (0xAC); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	
	I2C0_MSA_R = accel_read; 
	I2C0_MCS_R = (0x09); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	zl = I2C0_MDR_R;
	
	
	I2C0_MSA_R = accel_read; 
	I2C0_MCS_R = (0x07); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	zh = I2C0_MDR_R;
	

	accel_ypr.z = (zl|zh<<8);
	accel_converted.z = (.0098066 *(accel_ypr.z))/20;
}
void print_accel_status(struct Accelerometer * accel)
{
	uint8_t i;
	uint8_t * ptr;
	ptr = (uint8_t *)accel;
	for(i=0;i<30;i++)
	{
		printf(" The status of the accelerometer is register %d value is %02x \n", i , ptr[i]);
	}
	printf("\n\r");
}

void ACCEL_status()
{
	uint8_t *ptr;
	ptr = (uint8_t*) &ACCELSTATUS;
	int i;
	
  I2C0_MSA_R = accel_write; // slave address write
	I2C0_MDR_R = (0x80); //register to read, who am i with increment
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
		{
		}
		
	I2C0_MSA_R = accel_read; // slave address read
	I2C0_MCS_R = (0x0B); // writing 3 means it will expect another send
		
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
		{
		}
		
ptr[0] = I2C0_MDR_R;
		
	for(i=1;i<29;i++)
	{
	
		I2C0_MCS_R = (0x09); // writing 3 means it will expect another send
		
		while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
		{
		}
		
		ptr[i] = I2C0_MDR_R;
		
	}
	I2C0_MCS_R = (0x05);
}

void ACCEL_data()
{
	ACCEL_Z();
	ACCEL_Y();
	ACCEL_X();
	
}

