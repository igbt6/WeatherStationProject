/*
  @file gts4E60.h

  @brief GTS-4E-60 GPS Module (FIBOCOM) module Library
         Easy to change for other module

  @Author lukasz uszko(luszko@op.pl)

  Tested on FRDM-KL46Z and FRDM-KL25Z
  
  Copyright (c) 2014 lukasz uszko
  Released under the MIT License (see http://mbed.org/license/mit)

  Nice tutorial about degree formats and ways of computing them:
  http://home.online.no/~sigurdhu/Deg_formats.htm

  Documentation regarding GTS-4E-60 GPS Module might be found here:
  http://www.fibocom.com/product/2-1-3-2.html

*/




#ifndef __GTS4E60_H__
#define __GTS4E60_H__

#include "mbed.h"
#include "BufferedSerial.h"
#include <string>

#define GTS4E60_SERIAL_DEFAULT_BAUD       9600
#define GTS4E60_SERIAL_TIMEOUT            10000
#define GTS4E60_SERIAL_EOL                "\r\n"
#define GTS4E60_NMEA_BUF_SIZE             1024

//SENTENCES handled by the module: $GPGGA, $GPGSA, $GPRMC, $GPGSV
#define GGA         1
#define GSA         2
#define RMC         3
#define GSV         4

//deafault serial port on FRDM KL46Z:
// UART2:
// RX-PTE17
// TX-PTE16


// EXAMPLE OUTPUTS
//
// $GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C
// $GPRMC, time, status, latitude, N/S, longitude, E/W, speed(knots), heading, date, N/A, N/A, MODE*CHECKSUM
//
// $GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65
// $GPGGA, time, latitude, N/S, longitude, E/W, fix, satellites, hdop, altitude, M, geoidal sep , M,,*CHECKSUM
// $GPGGA, %f, %*f, %*c, %*f, %*c, %d, %d, %*f, %*f, %*c, %*f , %*c,,%*c%*c%*c0

//useful data structs
struct UTC_Time {
    UTC_Time() {
        hours =0;
        minutes =0;
        seconds=0;
    }
    int hours;
    int minutes;
    float seconds;
};


struct Date {
    Date() {
        day =0;
        month =0;
        year =0;
    }
    int day;
    int month;
    int year;
};



class GTS4E60
{
public:
    GTS4E60 (PinName tx, PinName rx);
    int write(const char* data); //?
    void init();
    bool parseData();
    int isDataAvailable();
    inline int getDataFromRx() {
        return mGpsSerial.getc();
    }

//getters
    UTC_Time getTime();
    Date getDate();
    float getLongitude();
    float getLatitude();
    float getAltitude();
    float getSpeedKn();
    float getSpeedKm();
    int   getSatelites();
    float getCourseT();
    float getCourseM();
    int   getFixType();
    int   getSatellites();
    int   getStatus();
    char  getNS();
    char  getEW();
    float getHeading();

// navigational functions
    float calcCourseTo(float, float);
    double calcDistToMi(float, float);
    double calcDistToFt(float, float);
    double calcDistToKm(float, float);
    double calcDistToM(float, float);


private:

    float trunc ( float v);
    float nmeaToDecimal(float deg_coord, char nsew);
    void readData();
    Serial mGpsSerial;
    char mNmeaData[GTS4E60_NMEA_BUF_SIZE];

    // GGA - Global Positioning System Fixed Data
    struct UTC_Time mUtcTime;         // UTC time
    int mFixType;        // 0 = no fix;  1 = fix;  2=differential fix
    int mSatellites;     // number of satellites used
    float mHdop;
    float mAltitude;
    char mUnits;

    // RMC - Recommended Minimmum Specific GNS Data
    char mDataStatus;// RMC data status A = Data Valid; V = Data Not valid;
    float mLatitude;
    float mLongitude;
    char NS, EW;
    float mSpeedKn;      // speed in knots/hour
    float mSpeedKm;      // speed in kilometres/hour
    float mHeading;      // heading in degrees derived from previous & current location
    struct Date mDate;

    //useful variables
    string mFix;
    string mCardinal;

    // VTG - Course over ground, ground speed
    float course_t; // ground speed true
    char course_t_unit;
    float course_m; // magnetic
    char course_m_unit;
    char speed_k_unit;
    float speed_km; // speek km/hr
    char speed_km_unit;

};



#endif // __GTS4E60_H__
