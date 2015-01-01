
#include "gts4E60.h"
#include <string.h>



GTS4E60::GTS4E60(PinName tx, PinName rx) : mGpsSerial(tx,rx)
{
    mGpsSerial.baud(GTS4E60_SERIAL_DEFAULT_BAUD );
}

int GTS4E60::write(const char* data)
{

    return mGpsSerial.printf(data);
}


int GTS4E60::isRxDataAvailable()
{

    return mGpsSerial.readable();
}



int GTS4E60::parseData()
{
   // while(1) {
        getData();
        if(sscanf(NEMA, "GPGGA, %2d%2d%f, %*f, %*c, %*f, %*c, %d, %d, %*f, %f", &hours, &minutes, &seconds, &fixtype, &satellites, &altitude) >=1);
        if(sscanf(NEMA, "GPRMC, %2d%2d%f, %c, %f, %c, %f, %c, %f, %f, %2d%2d%2d", &hours, &minutes, &seconds, &validity, &latitude, &ns, &longitude, &ew, &speed, &heading, &day, &month, &year) >=1) {
            if(fixtype == 0) {
                return 0;
            }
            year += 2000;
            if(ns =='S') {
                latitude   *= -1.0;
            }
            if(ew =='W') {
                longitude  *= -1.0;
            }
            float degrees = trunc(latitude / 100.0f);
            float minutes = latitude - (degrees * 100.0f);
            latitude = degrees + minutes / 60.0f;
            degrees = trunc(longitude / 100.0f);
            minutes = longitude - (degrees * 100.0f);
            longitude = degrees + minutes / 60.0f;
            if(fixtype == 1) {
                fix = "Positive";
            }
            if(fixtype == 2) {
                fix = "Differential";
            }
            if(heading > 0.00 && heading < 45.00) {
                cardinal = "NNE";
            }
            if(heading == 45.00) {
                cardinal = "NE";
            }
            if(heading > 45.00 && heading < 90.00) {
                cardinal = "ENE";
            }
            if(heading == 90.00) {
                cardinal = "E";
            }
            if(heading > 90.00 && heading < 135.00) {
                cardinal = "ESE";
            }
            if(heading == 135.00) {
                cardinal = "SE";
            }
            if(heading > 135.00 && heading < 180.00) {
                cardinal = "SSE";
            }
            if(heading == 180.00) {
                cardinal = "S";
            }
            if(heading > 180.00 && heading < 225.00) {
                cardinal = "SSW";
            }
            if(heading == 225.00) {
                cardinal = "SW";
            }
            if(heading > 225.00 && heading < 270.00) {
                cardinal = "WSW";
            }
            if(heading == 270.00) {
                cardinal = "W";
            }
            if(heading > 270.00 && heading < 315.00) {
                cardinal = "WNW";
            }
            if(heading == 315.00) {
                cardinal = "NW";
            }
            if(heading > 315.00 && heading < 360.00) {
                cardinal = "NNW";
            }
            if(heading == 360.00 || heading == 0.00) {
                cardinal = "N";
            }
            kph = speed*1.852;
            return 1;
        }
    //}
}


float GTS4E60::trunc(float v)
{
    if(v < 0.0) {
        v*= -1.0;
        v = floor(v);
        v*=-1.0;
    } else {
        v = floor(v);
    }
    return v;
}

void GTS4E60::getData()
{
    while(mGpsSerial.getc() != '$');
    for(int i=0; i<256; i++) {
        NEMA[i] = mGpsSerial.getc();
        if(NEMA[i] == '\r') {
            NEMA[i] = 0;
            return;
        }
    }
    error("overflowed message limit");
}

void GTS4E60::Init()
{
    wait(1);
    wait(1);
}

