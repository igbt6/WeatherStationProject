#include "mbed.h"

#include "max4070.h"
#include "rtos.h"
#include "USBHostMSD.h"
#include "LCD40x2.h"
#include "BMP180.h"
#include "max9611.h"
#include "si7020.h"
#include "AS3935.h"
#include "ds2782.h"
#include "ltc2460.h"

#define USB_DEBUG


#define SI7020_ENABLEDx
#define AS3935_ENABLEDx
#define DS2782_ENABLEDx
#define BMP180_ENABLEDx
#define MAX4070_ENABLEDx


#define MAX9611_ENABLED
#define LTC2460_ENABLED



#define BMP180_PIN_SDA PTB1    // I2C0
#define BMP180_PIN_SCL PTB0

#define MAX4070_PIN_ANALOG_IN PTB3 //AIN 2 charging voltage sensor dla kwicinskiego na testy
#define MAX4070_PIN_ANALOG_IN_VOLTAGE PTB2 //AIN 1 charging  sensor

#define MAX9611_PIN_SDA PTB1    // I2C1
#define MAX9611_PIN_SCL PTB0

#define DS2782_PIN_SDA PTB1    // I2C0
#define DS2782_PIN_SCL PTB0

#define SI7020_PIN_SDA PTB1    // I2C0
#define SI7020_PIN_SCL PTB0

#define AS3935_PIN_SDA PTB1    // I2C0
#define AS3935_PIN_SCL PTB0
#define AS3935_PIN_INTERRUPT PTD5  //Only the pins of port A and D can be used as interrupt in pins. (PTA[0-31] and PTD[0-31])

#define LTC2460_PIN_SCK  PTD1
#define LTC2460_PIN_MOSI PTD2
#define LTC2460_PIN_MISO PTD3
#define LTC2460_PIN_CS   PTD0
/*
+SCK ---> SCK (PTD1)
+SDI ---> MOSI (PTD2)
+SDO ---> MISO (PTD3)
+/CS ---> PTD0
*/


class SENSORS {

public: 

SENSORS();
    
~SENSORS();
    
//public methods to handle in other threads    
void measurement (void const* args);  
void getResults (void const* args);  // get or print all results from the sensors 
int saveDataToUSB(void const* args);

void showError(void);
    
private:     
 USBHostMSD* msd;
 MAX4070* max4070;
 MAX4070Voltage* max4070Voltage;
 BMP180*  bmp180;
 SI7020*  si7020;
 AS3935*  as3935;
 MAX9611* max9611;
 DS2782* ds2782;
 LTC2460* ltc2460;

 FILE* fileCurrent;
 FILE* fileVoltage;
 Mutex measPrintMutex;


 struct Results{
      Results():MAX4070chargerCurrent(0),
                MAX4070chargerVoltage(0),BMP180pressure(0),BMP180temperature(0),MAX9611voltage(0),MAX9611current(0){}
    
      float MAX4070chargerCurrent;
      float MAX4070chargerVoltage;
      
      float BMP180pressure; 
      float BMP180temperature;
       
      float MAX9611voltage; 
      float MAX9611current;
};
Results results;



Serial usbDebug;
TextLCD lcd;
//charLcd lcd;

    
};