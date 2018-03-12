#include "L3GD20.h"

struct L3GD20 GYROSTATUS;
struct gyroRawData gyro_ypr;
struct gyroConvertedData gyro_converted;
	uint8_t zl;
	uint8_t yl;
  uint8_t yh;
	uint8_t zh; // moved outside the function so that
	uint8_t xl; // when the function is called. it does
	uint8_t xh; // not reinitialize the variable to 0. so it can add the previous values.
	
#define xoff 511
#define yoff 65279
#define zoff 255

//#define time 10 // For 10 ms
#define timetest 5// for 5 ms
void GYRO_normalpower()
{
	int f;
	
  I2C0_MSA_R = gyro_write; // slave address write
	I2C0_MDR_R = (CTRL_REG1); //register to write, ctrl1 register
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	//I2C0_MDR_R = (0x0f); //value to write, puts gyro in normal power mode
	I2C0_MDR_R = (0x4F);  // value for normal power mode and 100 hz output rate
	I2C0_MCS_R = (0x05); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	

  I2C0_MSA_R = gyro_write; // slave address write
	I2C0_MDR_R = (CTRL_REG1); //register to write, ctrl1 register
	I2C0_MCS_R = (0x0B); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
  I2C0_MSA_R = gyro_read; // slave address read
	I2C0_MCS_R = (0x07); //this is the run and stop to tell bus last of data was sent
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	f = I2C0_MDR_R;
	switch (f)
	{
		case 0x4F :
		printf("Gyro configuration into normal power mode was successful\n\r");
		break; 
		
		case 0x08 :
		printf("Gyro has been put into sleep mode\n\r");
		break; 
		
		default:
		printf("Gyro is still in power down mode\n\r");
		break;
	}
}

void GYRO_config() // Set Establishes the necessary values for correct operation of gyro 
{
  I2C0_MSA_R = gyro_write; // slave address write
	I2C0_MDR_R = (CTRL_REG2); //register to write
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (0x00); //value to write, sets bandwidth and output data rate, 100hz = odr
	I2C0_MCS_R = (0x05); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (CTRL_REG3); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CTRL_REG4); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (CTRL_REG5); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (REFERENCE); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (FIFO_CTRL_REG); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_CFG); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_XL); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_XH); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_YL); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_YH); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_ZL); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_THS_ZH); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (INT1_DURATION); //address to write to 
	I2C0_MCS_R = (0x03); // repeated start with run,  remains in current state
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}	
	
	I2C0_MDR_R = (0x00); //value to write, puts device in 500dps
	I2C0_MCS_R = (0x05); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
	{
	}
	
	I2C0_MDR_R = (LOW_ODR); //address to write to 
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

void GYRO_roll() // x Axis
{	
  I2C0_MSA_R = gyro_write; // slave address write
	
	I2C0_MDR_R = (0xA8); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	I2C0_MSA_R = gyro_read; 
	I2C0_MCS_R = (0x09); // switches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	xl = I2C0_MDR_R;
	
	I2C0_MCS_R = (0x07); // another byte received and sequence ends
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	xh = I2C0_MDR_R;
	gyro_ypr.x = (xl|xh<<8) - xoff; //raw
	gyro_converted.x += (gyro_ypr.x * 0.02 * GYRO_SENSITIVITY_250DPS);//corrected *odr/scale
	gyro_converted.x = (gyro_converted.x *0.017453293); // radians
	//printf("%f x degrees\n\r",gyro_converted.x);
	
}

void GYRO_pitch() // Y Axis
{	
  I2C0_MSA_R = gyro_write; // slave address write
	
	I2C0_MDR_R = (0xAA); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	
	I2C0_MSA_R = gyro_read; 
	I2C0_MCS_R = (0x09); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	yl = I2C0_MDR_R;
	
	I2C0_MCS_R = (0x07); // another byte received and sequence ends
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	yh = I2C0_MDR_R;
	
	gyro_ypr.y = (yl|yh<<8)-yoff; //raw 
	gyro_converted.y += (gyro_ypr.y *0.02 * GYRO_SENSITIVITY_250DPS);// corrected * odr/scale
	gyro_converted.y =  (gyro_converted.y * 0.017453293);
	//printf("%f y degrees\n\r",gyro_converted.y);
	
}

void GYRO_yaw() // Z Axis
{
	
  I2C0_MSA_R = gyro_write; // slave address write
	
	I2C0_MDR_R = (0xAC); //register to write, this is z low with msb set to 1 to read multi bytes
	I2C0_MCS_R = (0x0B); // writing 3 will be a start and run, puts in transmit mode

	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	
	I2C0_MSA_R = gyro_read; 
	I2C0_MCS_R = (0x09); // witches from transmit to receive and receives 1 byte
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
  
	zl = I2C0_MDR_R;
	
	I2C0_MCS_R = (0x07); // another byte received and sequence ends
	
	while ((I2C0_MCS_R & (1<<0)) == !0)
	{
	}
	
	zh = I2C0_MDR_R;
	
	gyro_ypr.z = (zl|zh<<8) - zoff; //raw
	gyro_converted.z += (gyro_ypr.z * 0.02 *GYRO_SENSITIVITY_250DPS); // corrected * odr/ scale
	gyro_converted.z =(gyro_converted.z * 0.017453293);  //radians
	//printf("%f z degrees\n\r",gyro_converted.z);
	
}

void print_gyro_status(struct L3GD20 * thisptr)
{
	uint8_t i;
	uint8_t * ptr;
	ptr = (uint8_t *)thisptr;
	for(i=0;i<26;i++)
	{
		printf(" The status of the gyroscope is register %d value is %02x \n", i , ptr[i]);
	}
	printf("\n\r");
}

void GYRO_status()
{
	uint8_t *ptr;
	ptr = (uint8_t*) &GYROSTATUS;
	int i;
	
  I2C0_MSA_R = gyro_write; // slave address write
	I2C0_MDR_R = (0x80); //register to read, who am i with increment
	I2C0_MCS_R = (0x03); // writing 3 means it will expect another send
	
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
		{
		}
		
	I2C0_MSA_R = gyro_read; // slave address read
	I2C0_MCS_R = (0x0B); // writing 3 means it will expect another send
		
	while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
		{
		}
		
ptr[0] = I2C0_MDR_R;
		
	for(i=1;i<25;i++)
	{
	
		I2C0_MCS_R = (0x09); // writing 3 means it will expect another send
		
		while((I2C0_MCS_R & (1<<0)) == !0) // waits until bus is no longer busy
		{
		}
		
		ptr[i] = I2C0_MDR_R;
		
	}
	I2C0_MCS_R = (0x05);
}

void GYRO_data()
{
	GYRO_yaw();
	GYRO_pitch();
	GYRO_roll();
}
