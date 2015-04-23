
#include "sensors.h"
#include "MbedJSONValue.h"


/////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// ///////////////////////////////////////////////


SENSORS::SENSORS():usbDebug(USBTX, USBRX)
{
    usbDebug.baud(115200);

#ifdef GPS_ENABLED
    gps = new GTS4E60(GPS_PIN_TX,GPS_PIN_RX,GPS_PIN_SHUTDOWN);
#endif

#ifdef ADT7410_ENABLED
    adt7410 =new ADT7410( ADT7410_PIN_SDA,ADT7410_PIN_SCL,100000,ADT7410_2_I2C_ADDRESS);
#endif

#ifdef MAX44009_ENABLED
    max44009= new MAX44009( MAX44009_PIN_SDA, MAX44009_PIN_SCL ,100000);
#endif

#ifdef BMP180_ENABLED
    bmp180= new BMP180( BMP180_PIN_SDA, BMP180_PIN_SCL);

#endif

#ifdef MAX9611_ENABLED
    max9611= new MAX9611( MAX9611_PIN_SDA, MAX9611_PIN_SCL);
#endif

#ifdef SI7020_ENABLED
    si7020= new SI7020( SI7020_PIN_SDA, SI7020_PIN_SCL);
#endif

#ifdef AS3935_ENABLED
    as3935= new AS3935( AS3935_PIN_SDA, AS3935_PIN_SCL,AS3935_PIN_INTERRUPT);
#endif

#ifdef DS2782_ENABLED
    ds2782= new DS2782( DS2782_PIN_SDA, DS2782_PIN_SCL);
#endif

#ifdef RFM23_ENABLED
    rfm23b =new RF22ReliableDatagram(STATION_ADDRESS,RFM_PIN_nSEL, RFM_PIN_SDI ,RFM_PIN_SDO,RFM_PIN_SCLK,RFM_PIN_nIRQ,RFM_PIN_SDN  );
    if(!rfm23b->init()) {
        DEBUG("rfm23b init failed");
        while(1);
    } else
        DEBUG("rfm23b init succes");
#endif

}

SENSORS::~SENSORS()
{
    delete adt7410;
    delete max44009;
    delete bmp180;
    delete max9611;
    delete si7020;
    delete as3935;
    delete ds2782;
    delete gps;
    delete rfm23b;

}





void SENSORS:: measurement (void const* args)
{

    static uint8_t lastReadGpsParam=GGA;
    while(1) {

#ifdef GPS_ENABLED
        if(gps->isDataAvailable()) {
            if(lastReadGpsParam==RMC) { //i'll only read GGA and RMC nmea sentences
                lastReadGpsParam=GGA;
            } else {
                lastReadGpsParam=RMC;
            }
            uint8_t ret= gps->parseData(lastReadGpsParam);
            if(ret==ERROR) {
                DEBUG("ERROR INCORRECT DATA\r\n");
            } else if(ret==NO_FIX_FOUND) {
                DEBUG("NO GPS FIX FOUND\r\n");
            } else if(ret==NO_SATELLITES) {
                DEBUG("NO SATELLITES FOUND\r\n");
            } else if(ret==INVALID_STATUS) {
                DEBUG("STATUS INVALID\r\n");
            } else {
                struct UTC_Time utcTime= gps->getTime();
                struct Date date= gps->getDate();
                DEBUG("GPS_UTC_TIME: %02d:%02d:%02.3f\r\n",utcTime.hours, utcTime.minutes, utcTime.seconds);
                DEBUG("GPS_DATE: %02d.%02d.%02d\r\n", date.day, date.month, date.year);
                DEBUG("GPS_DATA: fixtype: %d, satelites: %d, altitude: %f, speed: %f, heading: %f\r\n",gps->getFixType(), gps->getSatellites(), gps->getAltitude(), gps->getSpeedKm(), gps->getHeading());
                DEBUG("GPS_DATA: status: %c, latitude: %f, ns :%c, longitude: %f, ew: %c\r\n",gps->getStatus(), gps->getLatitude(), gps->getNS(), gps->getLongitude(), gps->getEW());
            }
        }
#endif


#ifdef BMP180_ENABLED
        if (!bmp180->readData()) DEBUG("BMP180_DATA_Reading Fuck UP\r\n");

#endif

#ifdef MAX9611_ENABLED
        if(!max9611->readCSAOutputValue())  DEBUG("MAX9611_CSA_Reading Fuck UP\r\n");
#endif

#ifdef SI7020_ENABLED

        if(!si7020->readTemp())  DEBUG("SI7020_TEMP_READ Fuck UP \r\n");
        if(!si7020->readHumidity())  DEBUG("SI7020_HUMIDREAD Fuck UP \r\n");

#endif

#ifdef ADT7410_ENABLED

        if(!adt7410->readTemp()) {
            DEBUG("ADT7410_TEMP_READ Fuck UP \r\n");
        }
#endif



#ifdef MAX44009_ENABLED
        if(!max44009->readLuxIntensity())DEBUG("MAX44009_LUX_READ Fuck UP \r\n");

#endif

#ifdef DS2782_ENABLED
        if(!ds2782->readTemperature())  DEBUG("DS2782_TEMP_READ Fuck UP \r\n");
        //else DEBUG("DS2782_TEMP_READ  Fucking OK!\r\n");
        if(!ds2782->readCurrent())  DEBUG("DS2782_CURRENT_READ Fuck UP \r\n");
        if(!ds2782->readVoltage())  DEBUG("DS2782_VOLTAGE_READ Fuck UP \r\n");

#endif



        Thread::wait(2000);

    }
}






void SENSORS::getResults (void const* args)
{
    while(1) {

#ifdef USB_DEBUG


#ifdef BMP180_ENABLED
        if(bmp180->getPressure()!=-999&&bmp180->getTemperature()!=-999)
            DEBUG("BMP180_PRESSURE: %5.2f [hPa]\r\nBMP180_TEMPERATURE: %5.2f [C]\r\n", bmp180->getPressure(), bmp180->getTemperature());
        else
            DEBUG("BMP180_ERROR\r\n");
#endif

#ifdef MAX9611_ENABLED
        //DEBUG("MAX9611_Temperature[C]:   %5.2f\r\n", max9611->getTemp());
        DEBUG("MAX9611_CSA  %5.2f [mA]\r\n", max9611->getCSAOutput());
        //DEBUG("MAX9611_CSA_RAW:   0x%04x\r\n", max9611->mRawInt);
#endif

#ifdef SI7020_ENABLED
        DEBUG("SI7020_TEMPERATURE: %3.2f [C]\r\n", si7020->getTemp());
        DEBUG("SI7020_HUMIDITY: %3.2f ['/.]\r\n", si7020->getHumidity());
#endif


#ifdef DS2782_ENABLED
        DEBUG("DS2782_TEMP: %3.2f [C]\r\n", ds2782->getTemperature());
        DEBUG("DS2782_CURRENT: %3.2f [mA]\r\n", ds2782->getCurrent());
        DEBUG("DS2782_VOLTAGE=: %3.2f [mV]\r\n", ds2782->getVoltage());
        DEBUG("DS2782_ACR: %3.2f [uV]\r\n", ds2782->readAcrReg());
         DEBUG("DS2782_RARC: %3d [./']\r\n", ds2782->readRarcReg());
        //DEBUG("DS2782_STATUS= 0x%02d \r\n", ds2782->readStatusReg());
        uint8_t statusReg = ds2782->readStatusReg();
        DEBUG("DS2782_STATUS: 0x%02x \r\n", statusReg);
        if(statusReg & DS2782::LEARNF)
             DEBUG("LEARNF flag is SET\r\n");
        else
             DEBUG("LEARNF flag is NOT SET\r\n");
        if(statusReg & DS2782::SEF)
             DEBUG("SEF flag is SET\r\n");
        else
            DEBUG("SEF flag is NOT SET\r\n");
        if(statusReg & DS2782::AEF)
             DEBUG("AEF flag is SET\r\n");
        else
            DEBUG("AEF flag is NOT SET\r\n");
        if(statusReg & DS2782::CHGTF)
             DEBUG("CHGTF flag is SET\r\n");
        else
             DEBUG("CHGTF flag is NOT SET\r\n");

#endif



#ifdef ADT7410_ENABLED

        if(adt7410->getTemperature()!=-999)
            DEBUG("ADT7410_TEMPERATURE: %5.2f [C]\r\n", adt7410->getTemperature());
        else
            DEBUG("ADT7410_ERROR\r\n");

#endif



#ifdef MAX44009_ENABLED

        if(max44009->getLuxIntensity()!=-999)
            DEBUG("MAX44009_LUX_INTESITY: %5.2f [lx]\r\n\n",max44009->getLuxIntensity());
        else
            DEBUG("MAX44009_ERROR\r\n\n");
#endif

#endif
        // DEBUG("TEST_STRING_1_2_3_4_5_6_7_8_9_10_A_B_C_D_E_F_G_H_I_J_K_L_M_N_O_P_Q_R_S_T_U_V_X_Y_Z\r\n");
        Thread::wait(1500);
    }
}





void SENSORS::waitForEvents(void const*args)
{
    while(1) {
#ifdef AS3935_ENABLED
        osEvent as3935Event = as3935->checkQueueState();
        if(as3935Event.status==osEventMessage) {

            uint8_t *distance = (uint8_t*)as3935Event.value.p;
            DEBUG("AS3935_DISTANCE: %3d\r\n",distance);
        } else {
            DEBUG("AS3935 NO phenomenon occured");
        }
        // DEBUG("AS3935_DISTANCE: %d \r\n", as3935->getLightningDistanceKm());
#endif


#ifdef RFM23_ENABLED
        uint8_t data[] = "METEO_DATA";
        uint8_t buf[20];
        uint8_t len = sizeof(buf);
        uint8_t from;
        std::string serializedData;

        if (rfm23b->recvfromAck(buf, &len, &from)) {
            DEBUG("got request from : 0x%x",from);
            DEBUG(": ");
            DEBUG("%s",(char*)buf);
            // Send a reply to wifi module
            DEBUG(serializeDataPacket().c_str());

            serializedData = serializeDataPacket();
            if (!rfm23b->sendtoWait((uint8_t*)serializedData.c_str(), serializedData.length(), from))
                DEBUG("sendtoWait failed");
        }


#endif
        Thread::wait(200);
        
    }
}





std::string SENSORS:: serializeDataPacket(void)
{

    MbedJSONValue meteoData;

#ifdef SI7020_ENABLED
        meteoData["HUM"]=si7020->getHumidity();
#endif

#ifdef AS3935_ENABLED

#endif
#ifdef DS2782_ENABLED
        meteoData["BAT_C"][0]=ds2782->getCurrent();
        meteoData["BAT_V"][1]= ds2782->getVoltage();
#endif
#ifdef MAX9611_ENABLED
        meteoData["CUR"] =max9611->getCSAOutput();
#endif
#ifdef BMP180_ENABLED
        meteoData["PRE"]= bmp180->getPressure(); 
#endif
#ifdef ADT7410_ENABLED
        meteoData["TEM"]=adt7410->getTemperature();

#endif
#ifdef MAX44009_ENABLED
        meteoData["LHT"]=max44009->getLuxIntensity();
#endif
#ifdef GPS_ENABLED

#endif


   

 return meteoData.serialize();

}
