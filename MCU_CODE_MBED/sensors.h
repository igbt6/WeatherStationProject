#include "mbed.h"

#include "rtos.h"
#include "USBSerial.h"
#include "BufferedSerial.h"
#include "BMP180.h"
#include "max9611.h"
#include "si7020.h"
#include "AS3935.h"
#include "ds2782.h"
#include "adt7410.h"
#include "max44009.h"

#define NR_OF_THREADS 3
#define USB_DEBUG


#define SI7020_ENABLED
#define AS3935_ENABLED
#define DS2782_ENABLEDx
#define MAX9611_ENABLEDx
#define BMP180_ENABLED
#define ADT7410_ENABLED
#define MAX44009_ENABLED
#define BTM222_ENABLEDx



#define ADT7410_PIN_SDA PTE0    //I2C1
#define ADT7410_PIN_SCL PTE1

#define MAX44009_PIN_SDA PTE0    //I2C1
#define MAX44009_PIN_SCL PTE1

#define BMP180_PIN_SDA PTE0    // I2C1
#define BMP180_PIN_SCL PTE1

#define MAX9611_PIN_SDA PTC9    // I2C0
#define MAX9611_PIN_SCL PTC8

#define DS2782_PIN_SDA PTC9    // I2C0
#define DS2782_PIN_SCL PTC8

#define SI7020_PIN_SDA PTE0    // I2C1
#define SI7020_PIN_SCL PTE1

#define AS3935_PIN_SDA PTC9    // I2C0
#define AS3935_PIN_SCL PTC8
#define AS3935_PIN_INTERRUPT PTA7  //Only the pins of port A and D can be used as interrupt in pins. (PTA[0-31] and PTD[0-31])


class SENSORS {

public: 

SENSORS();
    
~SENSORS();
    
//public methods to handle in other threads    
 void measurement (void const* args);  
 void getResults (void const* args);  // get or print all results from the sensors 
 void waitForEvents(void const*args); // handle here all asynch events that come from irqs mainly

    
private:
 BMP180* bmp180;
 SI7020* si7020;
 AS3935* as3935;
 MAX9611* max9611;
 DS2782* ds2782;
 ADT7410* adt7410;
 MAX44009* max44009;
 Mutex measPrintMutex;


//USBSerial usbDebug;
Serial usbDebug;

    
};