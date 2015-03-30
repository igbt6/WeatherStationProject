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
#include "gts4E60.h"  //gps module
#include "RF22ReliableDatagram.h"
#define NR_OF_THREADS 3
#define USB_DEBUG


#define SI7020_ENABLED
#define AS3935_ENABLEDx
#define DS2782_ENABLEDx
#define MAX9611_ENABLEDx
#define BMP180_ENABLED
#define ADT7410_ENABLED
#define MAX44009_ENABLEDx
#define BTM222_ENABLEDx
#define GPS_ENABLED
#define RFM23_ENABLED


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

#define GPS_PIN_RX  PTE17    //UART2
#define GPS_PIN_TX  PTE16
#define GPS_PIN_SHUTDOWN PTE6


#define RFM_PIN_SDO  PTA17    //MISO
#define RFM_PIN_SDI   PTA16    //MOSI
#define RFM_PIN_SCLK  PTA15    //SCK
#define RFM_PIN_nSEL  PTA14
#define RFM_PIN_nIRQ  PTA6    //(as IRQ)
#define RFM_PIN_SDN   PTB9

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2


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
 GTS4E60 * gps;
 RF22ReliableDatagram *rfm23b;
 Mutex measPrintMutex;


//USBSerial usbDebug;
Serial usbDebug;

    
};