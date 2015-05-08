
#include "sensors.h"

/////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// ///////////////////////////////////////////////
#define PANELx

#ifdef PANEL
///KWIECINSKIEGO PANEL NADAZNY:
AnalogIn sensorInputLeft(PTB3);
AnalogIn sensorInputRight(PTB2);
//PTC7, PTC3   digital out
DigitalOut leftMotor(PTC7);
DigitalOut rightMotor(PTC11);

typedef enum {

    LEFT_MOTOR,
    RIGHT_MOTOR,
    OFF
} Motor;

static void setMotorDirection(Motor motor)
{
    switch(motor) {
        case LEFT_MOTOR:
            rightMotor =0;
            //wait_ms(1000);
            leftMotor= 1;
            break;

        case RIGHT_MOTOR:
            leftMotor= 0;
            //wait_ms(1000);
            rightMotor =1;
            break;

        case OFF:
            leftMotor=0;
            rightMotor =0;
            break;

        default:
            break;
    }
}

static int panelState=0;
static void checkLightSensorStatus(void)
{

    uint16_t resLeft = sensorInputLeft.read_u16();
    uint16_t resRight = sensorInputRight.read_u16();
    float realLeftSensorVal=( (float)((resLeft *(3.3/0xFFFF))));
    float realRightSensorVal=( (float)((resRight *(3.3/0xFFFF))));

    if(realLeftSensorVal>2.20||realRightSensorVal>2.20) {
        setMotorDirection(RIGHT_MOTOR);
    } else if((realLeftSensorVal+0.06
              )<realRightSensorVal) {

        setMotorDirection(LEFT_MOTOR);
    } else {
        setMotorDirection(OFF);
    }



}

#endif

SENSORS::SENSORS():usbDebug(USBTX, USBRX),lcd(PTD7,PTE31,PTD6, PTC17,PTC16,PTC13,PTC12)// rs,rw,e,d4-d7
{

    lcd.printf("HELLO\n");
#ifdef  MAX4070_ENABLED
    //max4070= new MAX4070(MAX4070_PIN_ANALOG_IN ,1 /*4mv ->1mA*/);
    max4070Voltage= new MAX4070Voltage(MAX4070_PIN_ANALOG_IN_VOLTAGE ,1 );
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

#ifdef LTC2460_ENABLED
    ltc2460= new LTC2460(LTC2460_PIN_CS,LTC2460_PIN_MOSI,LTC2460_PIN_MISO,LTC2460_PIN_SCK ,6180/2180); //our resistors in the divider are: GND---- 2180R ----- ADC-----6180R
#endif


    msd = new  USBHostMSD("usb");
#ifdef USB_DEBUG
    usbDebug.printf(" HERERERRE\r\n");
#endif
    if (!msd->connect()) {
#ifdef USB_DEBUG
        usbDebug.printf(" USB Flash drive not found.\r\n");
#endif
    } else {

        fileCurrent= fopen("/usb/Current.txt", "w"); //rewrite, or create
        if (fileCurrent) {
#ifdef USB_DEBUG
            usbDebug.printf("(/usb/Current.txt)... sucess file-open!\r\n\r\n");
#endif
            fprintf(fileCurrent, " LOG Current[A]:\r\n INFO: Dane zapisywane sa co 0.5 sek.\r\n\r\n");
            fclose(fileCurrent);
            fileCurrent=NULL;
        }
#ifdef USB_DEBUG
        else usbDebug.printf(" ... failed file-open (/usb/Voltage.txt)!\r\n\r\n");
#endif
        fileVoltage=fopen("/usb/VOLTAGE.txt", "w");
        if (fileVoltage) {
#ifdef USB_DEBUG
            usbDebug.printf("(/usb/Voltage.txt)... sucess file-open!\r\n\r\n");
#endif
            fprintf(fileVoltage, " LOG VOLTAGE [V]:\r\n INFO: Dane zapisywane sa co 0.5 sek.\r\n\r\n");
            fclose(fileVoltage);
            fileVoltage=NULL;
        }
#ifdef USB_DEBUG
        else usbDebug.printf(" ... failed file-open (/usb/pVoltage.txt)!\r\n\r\n");
#endif
    }

}

SENSORS::~SENSORS()
{
    if(fileCurrent!=NULL) {
        fclose(fileCurrent);
        fileCurrent=NULL;
    }
    if(fileVoltage!=NULL) {
        fclose(fileVoltage);
        fileVoltage=NULL;
    }

    delete max4070;
    delete max4070Voltage;
    delete bmp180;
    delete max9611;
    delete si7020;
    delete as3935;
    delete ds2782;
    delete ltc2460;

}





void SENSORS:: measurement (void const* args)
{
    static int counter=0;

    while(1) {
//      measPrintMutex.lock();
#ifdef MAX4070_ENABLED
        //max4070->readValueFromInput();
        //results.MAX4070chargerCurrent=max4070->getResult();

        max4070Voltage->readValueFromInput();
       
#endif
#ifdef BMP180_ENABLED
        if (bmp180->ReadData( &results.BMP180temperature,&results.BMP180pressure)) {
        } else
            results.BMP180temperature=-999;
#endif

#ifdef MAX9611_ENABLED
        /*
          if(!max9611->readTemp())  usbDebug.printf("MAX9611_TempReading Fuck UP \n");
          else usbDebug.printf("MAX9611_TempReading Fucking OK!\r\n");
        */
        if(!max9611->readCSAOutputValue())  usbDebug.printf("MAX9611_CSA_Reading Fuck UP\r\n");
        //else usbDebug.printf("MAX9611_CSA_Reading Fucking OK!\r\n");
#endif

#ifdef SI7020_ENABLED

        if(!si7020->readTemp())  usbDebug.printf("SI7020_TEMP_READ Fuck UP \r\n");
        else usbDebug.printf("SI7020_TEMP_READ  Fucking OK!\r\n");

        //if(!si7020->readHumidity())  usbDebug.printf("SI7020_HUMIDITY_READ Fuck UP\r\n");
        //for(int i= 0;i<0xFFFFFF;i++);
        // if(!si7020->resetSensor()) usbDebug.printf("SI7020_RESET Fuck UP\r\n");
#endif

#ifdef AS3935_ENABLED


#endif

#ifdef DS2782_ENABLED
        if(!ds2782->readTemperature())  usbDebug.printf("DS2782_TEMP_READ Fuck UP \r\n");
        //else usbDebug.printf("DS2782_TEMP_READ  Fucking OK!\r\n");
        if(!ds2782->readCurrent())  usbDebug.printf("DS2782_CURRENT_READ Fuck UP \r\n");
        if(!ds2782->readVoltage())  usbDebug.printf("DS2782_VOLTAGE_READ Fuck UP \r\n");

#endif



        counter++;
        lcd.cls();
        //lcd.printf("%d[A]",counter);
#ifdef MAX4070_ENABLED
        lcd.printf("%3.2f[V]\n",  max4070Voltage->getResult());
#endif

#ifdef LTC2460_ENABLED
    lcd.printf("%3.2f[V]\n", ltc2460->readVoltage());
#endif


#ifdef MAX9611_ENABLED
        lcd.printf("%3.2f[mA]", max9611->getCSAOutput());
#endif
#ifdef SI7020_ENABLED
        lcd.printf("%3.2f[C]", si7020->getTemp());
        lcd.printf("%3.2f[%]", si7020->getHumidity());
#endif
#ifdef DS2782_ENABLED
        //lcd.printf("%3.2f[C] ",  ds2782->getTemperature());
        lcd.printf("%3.2f[mA] ", ds2782->getCurrent());
        lcd.printf("%3.2f[mV]", ds2782->getVoltage());


#endif
//measPrintMutex.unlock();
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

#ifdef LTC2460_ENABLED
    usbDebug.printf("%3.2f[V]\n", ltc2460->readVoltage());
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



#ifdef PANEL
// SENSORS Phototransistors
        /*
             uint16_t resLeft = sensorInputLeft.read_u16();
             uint16_t resRight = sensorInputRight.read_u16();
             float realLeftSensorVal=( (float)((resLeft *(3.3/0xFFFF))));
             float realRightSensorVal=( (float)((resRight *(3.3/0xFFFF))));
             usbDebug.printf("LEFT_SENSOR= %3.2f [V]\r\n",realLeftSensorVal);
             usbDebug.printf("RIGHT_SENSOR= %3.2f [V]\r\n", realRightSensorVal);
             static int counter =0;
             counter++;
             if(counter==1){
                //setMotorDirection(LEFT_MOTOR);
             }
             else if(counter==10){

                //setMotorDirection(RIGHT_MOTOR);

             }
             if(counter==20)
               counter=0;
        */
        usbDebug.printf("LEFT_SENSOR= %3.2f [V]\r\n",((float)(sensorInputLeft.read_u16())*(3.3/0xFFFF)));
        usbDebug.printf("RIGHT_SENSOR= %3.2f [V]\r\n", ((float)(sensorInputRight.read_u16())*(3.3/0xFFFF)));
        checkLightSensorStatus();

#endif

#endif

        Thread::wait(2000);
    }
}







int SENSORS::saveDataToUSB(void const* args)
{
    while(1) {
        measPrintMutex.lock();


        if(!msd->connect()) {
#ifdef USB_DEBUG
            usbDebug.printf("ERROR!: USB Flash drive not found. is not connected or broken -> just try to connect it\r\n");
#endif
        } else {

#ifdef USB_DEBUG
            //usbDebug.printf("PENDRIVE IS CONNECTED\r\n");
#endif

            if(!fileCurrent) {
                fileCurrent=fopen("/usb/Current.txt", "a");
            } else {
#ifdef MAX9611_ENABLED
                fprintf(fileCurrent,"%5.2f\r\n", max9611->getCSAOutput());
#endif
                fclose(fileCurrent);
                fileCurrent=NULL;
            }
            if(!fileVoltage) {
                fileVoltage=fopen("/usb/Voltage.txt", "a");
            } else {
#ifdef MAX4070_ENABLED
                fprintf(fileVoltage,"%5.2f\r\n", /*max4070Voltage->getResult()*/ ltc2460->readVoltage());
#endif
                fclose(fileVoltage);
                fileVoltage=NULL;
            }
        }
        measPrintMutex.unlock();
        Thread::wait(500);
    }
}


void SENSORS:: showError(void)
{
    PwmOut r (LED_RED);
    PwmOut g (LED_GREEN);
    PwmOut b (LED_BLUE);


    r.period(0.001);
    g.period(0.001);
    b.period(0.001);

    while (true) {
        for (float i = 0.0; i < 1.0 ; i += 0.001) {
            float p = 3 * i;
            r = 1.0 - ((p < 1.0) ? 1.0 - p : (p > 2.0) ? p - 2.0 : 0.0);
            g = 1.0 - ((p < 1.0) ? p : (p > 2.0) ? 0.0 : 2.0 - p);
            b = 1.0 - ((p < 1.0) ? 0.0 : (p > 2.0) ? 3.0 - p : p - 1.0);
            wait (0.0025);
        }
    }
}
