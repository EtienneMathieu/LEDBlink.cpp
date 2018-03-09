#include "gps_stg_venus.h"
GPSVenus::GPSVenus(Serial & GPSPort_) :GPSPort(GPSPort_){
    GPSPort_.baud(9600);
}

void GPSVenus::setBaud_115200()
 {
         // VENUS Binary MsgID=0x05
         
         char msg[11] = { 0xA0, 0xA1, 0x00, 0x04, 
                          0x05, 0x00, 0x05, 0, 
                          0, 0x0D, 0x0A };
         for (int i=4; i < 8; i++) {
             msg[8] ^= msg[i];
         }
	 for (int i = 0; i < 11; i++)
		 GPSPort.putc(msg[i]);
 }

void GPSVenus::setNmeaMessages(bool gga, bool gsa, bool gsv, bool gll, bool rmc, bool vtg)
 {
         // VENUS Binary MsgID=0x08
         // GGA interval
         // GSA interval
         // GSV interval
         // GLL interval
         // RMC interval
         // VTG interval
         // ZDA interval -- hardcode off
         char msg[16] = { 0xA0, 0xA1, 0x00, 0x09, 
                          0x08, gga, gsa, gsv, gll, rmc, vtg, 0, 0,
                          0, 0x0D, 0x0A };
         for (int i=4; i < 13; i++) {
             msg[13] ^= msg[i];
         }
         for (int i=0; i < 16; i++)
              GPSPort.putc(msg[i]);
}
 
 
void GPSVenus::setUpdateRate(int rate)
 {
     char msg[10] = { 0xA0, 0xA1, 0x00, 0x03,
                     0x0E, rate&0xFF, 01,
                     0, 0x0D, 0x0A };
     for (int i=4; i < 7; i++) {
         msg[7] ^= msg[i];
     }
     switch (rate) {
     case 1 :
     case 2 :
     case 4 :
     case 5 :
     case 8 :
     case 10 :
     case 20 :
         for (int i=0; i < 10; i++)            
              GPSPort.putc(msg[i]);
         break;
     default :
         break;
     }
}