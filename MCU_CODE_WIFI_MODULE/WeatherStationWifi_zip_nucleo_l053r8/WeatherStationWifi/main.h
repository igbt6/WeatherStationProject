

#define DEBUG_ENABLED 1
#define DEBUG(...) do{if(DEBUG_ENABLED) usbDebug->printf(__VA_ARGS__);} while(0)
Serial* usbDebug;

#define RFM23D_ENABLED
#define RFM_PIN_SDO  PB_14     //MISO
#define RFM_PIN_SDI   PB_15   //MOSI
#define RFM_PIN_SCLK  PB_13    //SCK
#define RFM_PIN_nSEL  PB_12
#define RFM_PIN_nIRQ  PB_2    //(as IRQ)
#define RFM_PIN_SDN   PA_10

#define STATION_ADDRESS 1
#define SERVER_ADDRESS 2

