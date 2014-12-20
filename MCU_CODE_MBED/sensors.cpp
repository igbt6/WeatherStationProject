
#include "sensors.h"

/////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// ///////////////////////////////////////////////


SENSORS::SENSORS():usbDebug(USBTX, USBRX)
{ 
    //usbDebug.baud(9600);


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

}

SENSORS::~SENSORS()
{

    delete bmp180;
    delete max9611;
    delete si7020;
    delete as3935;
    delete ds2782;
    delete adt7410;
}





void SENSORS:: measurement (void const* args)
{


    while(1) {

#ifdef BMP180_ENABLED
        if (!bmp180->readData()) usbDebug.printf("BMP180_DATA_Reading Fuck UP\r\n");

#endif

#ifdef MAX9611_ENABLED
        if(!max9611->readCSAOutputValue())  usbDebug.printf("MAX9611_CSA_Reading Fuck UP\r\n");
#endif

#ifdef SI7020_ENABLED

        if(!si7020->readTemp())  usbDebug.printf("SI7020_TEMP_READ Fuck UP \r\n");

#endif

#ifdef AS3935_ENABLED
        osEvent as3935Event = as3935->checkQueueState();
        if(as3935Event.status==osEventMessage) {

            uint8_t *distance = (uint8_t*)as3935Event.value.p;
            usbDebug.printf("AS3935_DISTANCE: %3d\r\n",distance);
        }

#endif



#ifdef ADT7410_ENABLED

        if(!adt7410->readTemp()) {
            usbDebug.printf("ADT7410_TEMP_READ Fuck UP \r\n");
        }
#endif



#ifdef MAX44009_ENABLED
        if(!max44009->readLuxIntensity())usbDebug.printf("MAX44009_LUX_READ Fuck UP \r\n");

#endif

#ifdef DS2782_ENABLED
        if(!ds2782->readTemperature())  usbDebug.printf("DS2782_TEMP_READ Fuck UP \r\n");
        //else usbDebug.printf("DS2782_TEMP_READ  Fucking OK!\r\n");
        if(!ds2782->readCurrent())  usbDebug.printf("DS2782_CURRENT_READ Fuck UP \r\n");
        if(!ds2782->readVoltage())  usbDebug.printf("DS2782_VOLTAGE_READ Fuck UP \r\n");

#endif


        Thread::wait(777);

    }
}






void SENSORS::getResults (void const* args)
{
    while(1) {

#ifdef USB_DEBUG


#ifdef BMP180_ENABLED
        if(bmp180->getPressure()!=-999&&bmp180->getTemperature()!=-999)
            usbDebug.printf("Pressure(hPa):   %5.2f\r\nTemperatureBMP180(C):   %5.2f\r\n", bmp180->getPressure(), bmp180->getTemperature());
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



#ifdef ADT7410_ENABLED   

        if(adt7410->getTemperature()!=-999)
            usbDebug.printf("TemperatureADT7410_1(C):  %5.2f\r\n", adt7410->getTemperature());
        else
            usbDebug.printf("ADT7410_1ERROR\r\n");

#endif



#ifdef MAX44009_ENABLED

        if(max44009->getLuxIntensity()!=-999)
            usbDebug.printf("MAX44009_LUX_INTESITY: %5.2f\r\n",max44009->getLuxIntensity());
        else
            usbDebug.printf("MAX44009_ERROR\r\n");
#endif

#endif
   // usbDebug.printf("TEST_STRING_1_2_3_4_5_6_7_8_9_10_A_B_C_D_E_F_G_H_I_J_K_L_M_N_O_P_Q_R_S_T_U_V_X_Y_Z\r\n");
        Thread::wait(1500);
    }
}


