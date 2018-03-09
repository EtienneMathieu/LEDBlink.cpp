#include "mbed.h"

class GPSVenus {
public:
	GPSVenus(Serial & GPSPort_);
	void setBaud_115200();
	void setNmeaMessages(bool gga, bool gsa, bool gsv, bool gll, bool rmc, bool vtg);
	void setUpdateRate(int rate);
private:
	Serial & GPSPort;
};


