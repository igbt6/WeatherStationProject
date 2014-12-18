
#include "sensors.h"

/////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// ///////////////////////////////////////////////


SENSORS::SENSORS():usbDebug(USBTX, USBRX)// rs,rw,e,d4-d7
{
    
    
#ifdef ADT7410_ENABLED
    adt7410_1= new  ADT7410( ADT7410_PIN_SDA,ADT7410_PIN_SCL,100000);
    adt7410_2 =new ADT7410( ADT7410_PIN_SDA,ADT7410_PIN_SCL,100000,ADT7410_2_I2C_ADDRESS);
#endif
    

#ifdef BMP180_ENABLED
    bmp180= new BMP180( BMP180_PIN_SDA, BMP180_PIN_SCL);
    bmp180->Initialize(64, BMP180_OSS_ULTRA_LOW_POWER); // 64m altitude compensation and low power oversampling
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

}

SENSORS::~SENSORS()
{


    delete bmp180;
    delete max9611;
    delete si7020;
    delete as3935;
    delete ds2782;

}





void SENSORS:: measurement (void const* args)
{


    while(1) {
//      measPrintMutex.lock();
#ifdef BMP180_ENABLED
        if (bmp180->ReadData( &results.BMP180temperature,&results.BMP180pressure)) {
        } else
            results.BMP180temperature=-999;
#endif

#ifdef MAX9611_ENABLED
        if(!max9611->readCSAOutputValue())  usbDebug.printf("MAX9611_CSA_Reading Fuck UP\r\n");
#endif

#ifdef SI7020_ENABLED

        if(!si7020->readTemp())  usbDebug.printf("SI7020_TEMP_READ Fuck UP \r\n");
        else usbDebug.printf("SI7020_TEMP_READ  Fucking OK!\r\n");

#endif

#ifdef AS3935_ENABLED


#endif

#ifdef DS2782_ENABLED
        if(!ds2782->readTemperature())  usbDebug.printf("DS2782_TEMP_READ Fuck UP \r\n");
        //else usbDebug.printf("DS2782_TEMP_READ  Fucking OK!\r\n");
        if(!ds2782->readCurrent())  usbDebug.printf("DS2782_CURRENT_READ Fuck UP \r\n");
        if(!ds2782->readVoltage())  usbDebug.printf("DS2782_VOLTAGE_READ Fuck UP \r\n");

#endif


        Thread::wait(1000);

    }
}






void SENSORS::getResults (void const* args)
{
    while(1) {

#ifdef USB_DEBUG
#ifdef MAX4070_ENABLED
        //usbDebug.printf("MAX4070_CurrentValue: %5.2f\r\n",results.MAX4070chargerCurrent);
        usbDebug.printf("MAX4070_VoltageValue: %5.2f\r\n",max4070Voltage->getResult());
#endif
#ifdef BMP180_ENABLED
        if(results.BMP180pressure!=-999&&results.BMP180temperature!=-999)
            usbDebug.printf("Pressure(hPa):   %5.2f\r\nTemperatureBMP180(C):   %5.2f\r\n", results.BMP180pressure, results.BMP180temperature);
        else
            usbDebug.printf("BMP180_ERROR\r\n");
#endif

#ifdef MAX9611_ENABLED
        //usbDebug.printf("MAX9611_Temperature[C]:   %5.2f\r\n", max9611->getTemp());
        usbDebug.printf("MAX9611_CSA  %5.2f [mA]\r\n", max9611->getCSAOutput());
        //usbDebug.printf("MAX9611_CSA_RAW:   0x%04x\r\n", max9611->mRawInt);
#endif

#ifdef SI7020_ENABLED
        usbDebug.printf("SI7020_TEMP= %3.2f [C]\r\n", si7020->getTemp());
        usbDebug.printf("SI7020_HUMIDITY= %3.2f [%]\r\n", si7020->getHumidity());
#endif

#ifdef AS3935_ENABLED
        usbDebug.printf("AS3935_TEMP= %d \r\n", as3935->lightningDistanceKm());
#endif

#ifdef DS2782_ENABLED
        usbDebug.printf("DS2782_TEMP= %3.2f [C]\r\n", ds2782->getTemperature());
        usbDebug.printf("DS2782_CURRENT= %3.2f [mA]\r\n", ds2782->getCurrent());
        usbDebug.printf("DS2782_VOLTAGE= %3.2f [mV]\r\n", ds2782->getVoltage());
        usbDebug.printf("DS2782_ACR= %3.2f [uV]\r\n", ds2782->readAcrReg());
        usbDebug.printf("DS2782_RARC= %3d [./']\r\n", ds2782->readRarcReg());
        //usbDebug.printf("DS2782_STATUS= 0x%02d \r\n", ds2782->readStatusReg());
        uint8_t statusReg = ds2782->readStatusReg();
        usbDebug.printf("DS2782_STATUS= 0x%02x \r\n", statusReg);
        if(statusReg & DS2782::LEARNF)
            usbDebug.printf("LEARNF flag is SET\r\n");
        else
            usbDebug.printf("LEARNF flag is NOT SET\r\n");
        if(statusReg & DS2782::SEF)
            usbDebug.printf("SEF flag is SET\r\n");
        else
            usbDebug.printf("SEF flag is NOT SET\r\n");
        if(statusReg & DS2782::AEF)
            usbDebug.printf("AEF flag is SET\r\n");
        else
            usbDebug.printf("AEF flag is NOT SET\r\n");
        if(statusReg & DS2782::CHGTF)
            usbDebug.printf("CHGTF flag is SET\r\n");
        else
            usbDebug.printf("CHGTF flag is NOT SET\r\n");

#endif

#endif
        Thread::wait(2000);
   } 
}


