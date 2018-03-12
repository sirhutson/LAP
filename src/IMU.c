#include "IMU.h"

// For all trig functions must input radians 

#define time 10 // For 10 ms

int backtrack[4] = {0,0,0,1}; 
int ax,ay,az,gx,gy,gz;
int homeframe[4];

double pitch;
double roll;
double yaw;
double xangle; // in radians
double yangle; // in radians
double zangle; // in radians
double axangle;
double ayangle;
double azangle;
double heading;
	
double acc_vector;

double orientmaster[3][3];

//create struct for converted angles from degrees to radians

void IMU_config_power()
{
	GYRO_config();
	
	MAG_config();
	ACCEL_config();
	
	GYRO_normalpower();
	ACCEL_normalpower();
}

void IMU_data()
{
	GYRO_data();
	MAG_data();
	ACCEL_data();
}

void get_referenceframe()
{ 
	IMU_data();
	ax = accel_converted.x;
	ay = accel_converted.y;
	az = accel_converted.z;
	gx = gyro_converted.x;
	gy = gyro_converted.y;
	gz = gyro_converted.z;
	int homeframe[4] = {ax,ay,az,1};	
}


void IMU_STATUS()
{
	static int firstboot = 1;
	acc_vector = sqrt((accel_converted.x *accel_converted.x)+(accel_converted.y*accel_converted.y)+(accel_converted.z*accel_converted.z));
	
	if (firstboot == 1)
	{
		//yaw   = atan((sin(zangle)*cos(yangle))/(cos(zangle)*cos(yangle))); //using the accelerometer and this is inaccurate
		roll = (asin(accel_converted.x/acc_vector))*-57.296;
		pitch = (asin(accel_converted.y/acc_vector))*57.296;
		firstboot = 0;
		return;
	}
		xangle = gyro_converted.x;
		yangle = gyro_converted.y;
		zangle = gyro_converted.z;
//For yaw translation, other code
		//xangle -= yangle * sin(zangle * .00000087);
		//yangle += xangle * sin(zangle * .00000087);
	
//Needed for outside first run
		axangle = asin(accel_converted.x/acc_vector)*-57.296;
		ayangle = asin(accel_converted.y/acc_vector)*57.296;

	// Master matrix that holds orientation info
	
	orientmaster[0][0] = (cos(zangle)*cos(yangle));
	orientmaster[1][0] = (cos(yangle)*sin(zangle));
	orientmaster[2][0] = (-sin(yangle));
	orientmaster[2][1] = (cos(yangle)*sin(xangle));
	orientmaster[2][2] = (cos(yangle)*cos(xangle));
	
	
// Actual point of sensor fusion because accelerometer readings now affect gyro
	
	roll  = ((atan((cos(yangle)*sin(xangle))/(cos(yangle)*cos(yangle))) * 0.9996) + (axangle * 0.0004))*42;
	pitch = ((atan((-orientmaster[2][0])/(sqrt(.5*(orientmaster[0][0]*orientmaster[0][0])+ (orientmaster[1][0]*orientmaster[1][0])+(orientmaster[2][1]*orientmaster[2][1])+(orientmaster[2][2]*orientmaster[2][2]))))* 0.9996) + (ayangle * 0.0004))*42;
	//heading = atan2((mag_converted.z * sin(roll))-(mag_converted.y*cos(roll)),(mag_converted.x*cos(pitch)) + (mag_converted.y *sin(pitch)*sin(roll)) +( mag_converted.z * sin(pitch) * cos(roll)));
	yaw   = (atan((sin(zangle)*cos(yangle))/(cos(zangle)*cos(yangle))) * 0.0004) + (heading * .9996)*42;
	
	//heading = (atan2(mag_converted.y,mag_converted.x)); //compass reading in degrees
// 0.0 = North
// 90.0 = East
// 180.0 = South
// 270 = West
	
//	 if (heading < 0)
//  {
//   heading = 360 + heading;
//	}
	


//	orientmaster[3][0] = 0;
//	orientmaster[3][1] = 0;
//	orientmaster[3][2] = 0;
//	orientmaster[3][3] = 1;

}



void print_IMU() // will print the data in dps
{
	
	//printf(" %f %f %f mag converted data\n\r",mag_converted.x,mag_converted.y,mag_converted.z);
	//printf(" %f %f %f gyro converted data\n\r",gyro_converted.x,gyro_converted.y,gyro_converted.z);
	//printf(" %d %d %d gyro data\n\r",gyro_ypr.x,gyro_ypr.y,gyro_ypr.z);
	//printf(" %f %f %f accel data\n\r",accel_converted.x,accel_converted.y,accel_converted.z);
	//printf(" %f roll %f pitch %f yaw\n\r",roll, pitch,heading);
	printf(" %f roll %f pitch %f yaw\n\r", (roll/0.017453293), (pitch/0.017453293), yaw*57.324); //42 is a very random conversion factor 
	//printf(" %d %d %d mag raw data\n\r",mag_ypr.x,mag_ypr.y,mag_ypr.z);

}