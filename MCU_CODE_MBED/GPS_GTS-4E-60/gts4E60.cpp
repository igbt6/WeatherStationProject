
#include "gts4E60.h"
#include <string.h>



GTS4E60::GTS4E60(PinName tx, PinName rx) : mGpsSerial(tx,rx)
{
    mGpsSerial.baud(GTS4E60_SERIAL_DEFAULT_BAUD );
    init();
}

int GTS4E60::write(const char* data)
{

    return mGpsSerial.printf(data);
}

//private methods

float GTS4E60::nmeaToDecimal(float deg_coord, char nsew)
{
    int degree = (int)(deg_coord/100.0f);
    float minutes = deg_coord - degree*100;
    float dec_deg = minutes / 60.0f;
    float decimal = degree + dec_deg;
    if (nsew == 'S' || nsew == 'W') {
        decimal *= -1; // return negative value
    }
    return decimal;

    //using trunc
    /*
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
    */

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


void GTS4E60::readData()
{
    while(mGpsSerial.getc() != '$');  //wait for the correct NMEA protocol message
    for(int i=0; i<GTS4E60_NMEA_BUF_SIZE-2; i++) {
        mNmeaData[i] = mGpsSerial.getc();
        if(mNmeaData[i] == '\r') {
            mNmeaData[i] = 0;
            return;
        }
    }
    error("overflowed message limit");
}

//public methods

void GTS4E60::init()
{
    memset(mNmeaData,0,GTS4E60_NMEA_BUF_SIZE);
    //GPGAA
    mFixType= 0;        // 0 = no fix;  1 = fix;  2=differential fix
    mSatellites = 0;     // number of satellites used
    mHdop= 0;
    mAltitude= 0.0;
    mUnits= ' ';

    // RMC - Recommended Minimmum Specific GNS Data
    mLongitude= 0.0;
    mLatitude = 0.0;
    NS=' ';
    EW=' ';
    mDataStatus= 'V';
    wait(1);
}


int GTS4E60::isDataAvailable()
{

    return mGpsSerial.readable();
}



bool GTS4E60::parseData()
{
    // while(1) {
    readData();
    // Check if it is a GPGGA snetence
    if(sscanf(mNmeaData, "GPGGA, %2d%2d%f, %*f, %*c, %*f, %*c, %d, %d, %*f, %f", &mUtcTime.hours, &mUtcTime.minutes, &mUtcTime.seconds, &mFixType, &mSatellites, &mAltitude) >=1);
    //if it is a GPGSA sentence
    //else if(sscanf(mNmeaData, "GPGSA, %2d%2d%f, %*f, %*c, %*f, %*c, %d, %d, %*f, %f", &hours, &minutes, &seconds, &fixtype, &satellites, &altitude) >=1);
    //if it is a GPRMC sentence
    else if(sscanf(mNmeaData, "GPRMC, %2d%2d%f, %c, %f, %c, %f, %c, %f, %f, %2d%2d%2d", &mUtcTime.hours, &mUtcTime.minutes, &mUtcTime.seconds, &mDataStatus, &mLatitude, &NS, &mLongitude, &EW, &mSpeedKn, &mHeading, &mDate.day, &mDate.month, &mDate.year) >=1) {
        if(mFixType == 0) {
            mFix = "Invalid or not available";
            return 0;
        }
        mDate.year += 2000;
        mLatitude= nmeaToDecimal(mLatitude,NS);
        mLongitude= nmeaToDecimal(mLongitude,EW);

        if(mFixType == 1) {
            mFix = "Positive";
        }
        if(mFixType == 2) {
            mFix = "Differential";
        }
        if(mHeading > 0.00 && mHeading < 45.00) {
            mCardinal = "NNE";
        } else if(mHeading == 45.00) {
            mCardinal = "NE";
        } else if(mHeading > 45.00 && mHeading < 90.00) {
            mCardinal = "ENE";
        } else if(mHeading == 90.00) {
            mCardinal = "E";
        } else if(mHeading > 90.00 && mHeading < 135.00) {
            mCardinal = "ESE";
        } else if(mHeading == 135.00) {
            mCardinal = "SE";
        } else if(mHeading > 135.00 && mHeading < 180.00) {
            mCardinal = "SSE";
        } else if(mHeading == 180.00) {
            mCardinal = "S";
        } else if(mHeading > 180.00 && mHeading < 225.00) {
            mCardinal = "SSW";
        } else if(mHeading == 225.00) {
            mCardinal = "SW";
        } else if(mHeading > 225.00 && mHeading < 270.00) {
            mCardinal = "WSW";
        } else if(mHeading == 270.00) {
            mCardinal = "W";
        } else if(mHeading > 270.00 && mHeading < 315.00) {
            mCardinal = "WNW";
        } else if(mHeading == 315.00) {
            mCardinal = "NW";
        } else if(mHeading > 315.00 && mHeading < 360.00) {
            mCardinal = "NNW";
        } else if(mHeading == 360.00 || mHeading == 0.00) {
            mCardinal = "N";
        }
        mSpeedKm = mSpeedKn*1.852;

    }
    //if there is a GPGSV sentence
    //else if(sscanf(mNmeaData, "GPGSV, %2d%2d%f, %c, %f, %c, %f, %c, %f, %f, %2d%2d%2d", &hours, &minutes, &seconds, &validity, &latitude, &ns, &longitude, &ew, &speed, &heading, &day, &month, &year) >=1) {}
    return 1;
}





//getter methods
UTC_Time GTS4E60:: getTime()
{
    return mUtcTime;
}

Date GTS4E60:: getDate()
{
    return mDate;
}

float GTS4E60:: getLongitude()
{
    return mLongitude;
}

float GTS4E60::getLatitude()
{
    return mLatitude;
}

float GTS4E60::getAltitude()
{
    return mAltitude;
}

float GTS4E60::getSpeedKn()
{
    return mSpeedKn;
}

float GTS4E60::getSpeedKm()
{
    return mSpeedKm;
}

int   GTS4E60::getSatelites()
{
    return mSatellites;
}

//float GTS4E60::getCourseT() {}
//float GTS4E60::getCourseM() {}

int GTS4E60::getFixType()
{
    return mFixType;
}

int GTS4E60::getSatellites()
{
    return mSatellites;
}

int GTS4E60:: getStatus()
{
    return mDataStatus;
}

char GTS4E60:: getNS()
{
    return NS;
}
char GTS4E60:: getEW()
{
    return EW;
}

float GTS4E60:: getHeading()
{
    return mHeading;
}


