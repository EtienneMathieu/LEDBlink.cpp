#include "mbed.h"
#include "BMP180.h"
#include "BNO055.h"
#include "gps_stg_venus.h"
#include "HMC5883L.h"
#include "L3GD20H.h"
#include "LSM303DLHC.h"

//#define DEF_LSM303DLHC
//#define DEF_L3GD20H
#define DEF_GPS
int main() 
{
	
#ifdef DEF_LSM303DLHC
	LSM303DLHC mag(I2C_SCL, I2C_SDA);
	float *ax, *ay, *az;
	float *mx, *my, *mz;   
	for (;;)
	{
		mag.read(ax,ay,az,mx,my,mz);
		printf("ax:%f  ay:%f   az:%f  mx:%f   my:%f   mz:%f\n", *ax, *ay, *az, *mx, *my, *mz);
	}
	
#endif //LSM303DLHC

	
#ifdef DEF_L3GD20H
	L3GD20H gyro(I2C_SDA, I2C_SCL);
	short g[3];
	
	for (;;)
	{
		gyro.read(g);
		printf("gx:%s gy:%s gz:%s\n", g[0], g[1], g[2]);
	
	}
	
#endif // L3GD20H
	
	
#ifdef DEF_GPS
	Serial gps(SERIAL_RX,SERIAL_TX);
	GPSVenus venus(gps);
	Serial pc(USBRX,USBTX);
 
	pc.baud(115200);
	printf("start\r\n");
	venus.setBaud_115200();
	wait(0.5);
	gps.baud(115200);
	venus.setUpdateRate(10);
	wait(0.5);
	venus.setNmeaMessages(false, false, false, false, true, false);
	while(1)
	{
		pc.putc(gps.getc());
	}
	
#endif // GPS
	
}