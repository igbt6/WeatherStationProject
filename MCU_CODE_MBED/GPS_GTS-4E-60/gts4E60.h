/*
  @file gts4E60.h

  @brief GTS-4E-60 GPS Module (FIBOCOM) module Library

  @Author lukasz uszko(luszko@op.pl)

  Tested on FRDM-KL46Z and FRDM-KL25Z

  Copyright (c) 2014 lukasz uszko
  Released under the MIT License (see http://mbed.org/license/mit)

  Documentation regarding GTS-4E-60 GPS Module might be found here:

*/




#ifndef __GTS4E60_H__
#define __GTS4E60_H__

#include "mbed.h"
#include "BufferedSerial.h"
#include <string>

#define GTS4E60_SERIAL_DEFAULT_BAUD       9600
#define GTS4E60_SERIAL_TIMEOUT            10000
#define GTS4E60_SERIAL_EOL                "\r\n"

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

class GTS4E60
{
public:
    GTS4E60 (PinName tx, PinName rx);
    int write(const char* data);
    int isRxDataAvailable();
    inline int getDataFromRx() {
        return mGpsSerial.getc();
    }
    
    void Init();
    int parseData();
    float time;         // UTC time
    int hours;
    int minutes;
    float seconds;
    char validity,ns,ew;// RMC data status A = Data Valid; V = Data Not valid;
    float latitude;     //
    float longitude;    //
    float speed;        // speed in knots
    float heading;      // heading in degrees derived from previous & current location
    string date;           //
    int day;
    int month;
    int year;
    int fixtype;        // 0 = no fix;  1 = fix;  2=differential fix
    int satellites;     // number of satellites used
    float altitude;     //
    string fix; 
    string cardinal;
    float kph;

private:

    float trunc ( float v);
    void getData();
    Serial mGpsSerial;
    char NEMA[256];

    //BufferedSerial mGpsSerial;

};

#endif // __GTS4E60_H__
