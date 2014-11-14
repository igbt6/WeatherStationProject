
#include "sensors.h"

/////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// /////////////////////////////////////////////// ///////////////////////////////////////////////

SENSORS::SENSORS():usbDebug(USBTX, USBRX),lcd(PTD7,PTE31,PTD6, PTC17,PTC16,PTC13,PTC12)// rs,rw,e,d4-d7
{

    lcd.printf("HELLO\n");
    #ifdef  MAX4070_ENABLED
    max4070= new MAX4070(MAX4070_PIN_ANALOG_IN ,1 /*4mv ->1mA*/);
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
    

    msd = new  USBHostMSD("usb");
#ifdef USB_DEBUG
      usbDebug.printf(" HERERERRE\r\n");
#endif
    if (!msd->connect()) {
        #ifdef USB_DEBUG
        usbDebug.printf(" USB Flash drive not found.\r\n");
        #endif
    } else {
       
        fileCurrent= fopen("/usb/VOLTAGE_1.txt", "w"); //rewrite, or create
        if (fileCurrent) {
            #ifdef USB_DEBUG 
            usbDebug.printf("(/usb/pCurrent.txt)... sucess file-open!\r\n\r\n");
             #endif
            fprintf(fileCurrent, " LOG VOLTAGE [V] - VOLTAGE_1:\r\n INFO: Dane zapisywane sa co 0.5 sek.\r\n\r\n");
            fclose(fileCurrent);
            fileCurrent=NULL;
        } 
        #ifdef USB_DEBUG  
         else usbDebug.printf(" ... failed file-open (/usb/pCurrent.txt)!\r\n\r\n");
         #endif
        fileVoltage=fopen("/usb/VOLTAGE_2.txt", "w");
        if (fileVoltage) {
            #ifdef USB_DEBUG 
            usbDebug.printf("(/usb/pVoltage.txt)... sucess file-open!\r\n\r\n");
             #endif
            fprintf(fileVoltage, " LOG VOLTAGE [V]- VOLTAGE_2:\r\n INFO: Dane zapisywane sa co 0.5 sek.\r\n\r\n");
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

}





void SENSORS:: measurement (void const* args)
{
     static int counter=0;
   while(1) {
 //      measPrintMutex.lock();
 #ifdef MAX4070_ENABLED
        max4070->readValueFromInput();
        results.MAX4070chargerCurrent=max4070->getResult();

        max4070Voltage->readValueFromInput();
        results.MAX4070chargerVoltage=max4070Voltage->getResult();
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
        else usbDebug.printf("MAX9611_CSA_Reading Fucking OK!\r\n");   
 #endif
 
 #ifdef SI7020_ENABLED       
  
        //if(!si7020->readTemp())  usbDebug.printf("SI7020_TEMP_READ Fuck UP \n");    
        //else usbDebug.printf("SI7020_TEMP_READ  Fucking OK!\r\n");   
        if(!si7020->readHumidity())  usbDebug.printf("SI7020_HUMIDITY_READ Fuck UP\r\n"); 
 #endif
 
 
 counter++; 
    lcd.cls();
     //lcd.printf("%d[A]",counter);
#ifdef MAX9611_ENABLED      
    lcd.printf("%3.2f[mA]", max9611->getCSAOutput());
#endif   
#ifdef SI7020_ENABLED 
    lcd.printf("%3.2f[C]", si7020->getTemp());
    lcd.printf("%3.2f[%]", si7020->getHumidity());
#endif
//measPrintMutex.unlock();
        Thread::wait(777);
   
    }
}






void SENSORS::getResults (void const* args)
{
    while(1) {
        
#ifdef USB_DEBUG
        #ifdef MAX4070_ENABLED
        usbDebug.printf("MAX4070_CurrentValue: %5.2f\r\n",results.MAX4070chargerCurrent);
        usbDebug.printf("MAX4070_VoltageValue: %5.2f\r\n",results.MAX4070chargerVoltage);
        #endif
#ifdef BMP180_ENABLED
        if(results.BMP180pressure!=-999&&results.BMP180temperature!=-999)
            usbDebug.printf("Pressure(hPa):   %5.2f\r\nTemperatureBMP180(C):   %5.2f\r\n", results.BMP180pressure, results.BMP180temperature);
        else
            usbDebug.printf("BMP180_ERROR\r\n");
#endif

#ifdef MAX9611_ENABLED 
    //usbDebug.printf("MAX9611_Temperature[C]:   %5.2f\r\n", max9611->getTemp());
    usbDebug.printf("MAX9611_CSA [mA]:   %5.2f\r\n", max9611->getCSAOutput());
    usbDebug.printf("MAX9611_CSA_RAW:   0x%04x\r\n", max9611->mRawInt);
#endif

#ifdef SI7020_ENABLED 
    usbDebug.printf("SI7020_TEMP= %3.2f [C]\r\n", si7020->getTemp());
    usbDebug.printf("SI7020_HUMIDITY= %3.2f [%]\r\n", si7020->getHumidity());
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
                fileCurrent=fopen("/usb/VOLTAGE_1.txt", "a");
            } else {
                #ifdef MAX4070_ENABLED
                fprintf(fileCurrent,"%5.2f\r\n", results.MAX4070chargerCurrent);
                #endif
                #ifdef MAX9611_ENABLED 
              //  fprintf(fileCurrent,"%5.2f\r\n", max9611->getCSAOutput());
                #endif
                fclose(fileCurrent);
                fileCurrent=NULL;
            }
            if(!fileVoltage) {
                fileVoltage=fopen("/usb/VOLTAGE_2.txt", "a");
            } else {
                #ifdef MAX4070_ENABLED
                fprintf(fileVoltage,"%5.2f\r\n", results.MAX4070chargerVoltage);
                #endif
                #ifdef MAX9611_ENABLED 
                fprintf(fileVoltage,"TEST\r\n");
                #endif
                fclose(fileVoltage);
                fileVoltage=NULL;
            }
        } 
        measPrintMutex.unlock();
        Thread::wait(500);
    }
}


void SENSORS:: showError(void){
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
