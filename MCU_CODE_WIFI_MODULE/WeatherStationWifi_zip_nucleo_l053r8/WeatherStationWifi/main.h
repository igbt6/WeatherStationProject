

#define DEBUG_ENABLED 1
#define DEBUG(...) do{if(DEBUG_ENABLED) usbDebug->printf(__VA_ARGS__);} while(0)
Serial* usbDebug;

#define RFM23D_ENABLED
//SPI1 
#define RFM_PIN_SDO   PA_6//PB_4     //MISO ON uC
#define RFM_PIN_SDI   PA_7//PB_5     //MOSI
#define RFM_PIN_SCLK  PA_5//PB_3     //SCK
#define RFM_PIN_nSEL  PC_9     //PB12
#define RFM_PIN_nIRQ  PB_2    //(as IRQ)
#define RFM_PIN_SDN   PA_10

#define STATION_ADDRESS 1
#define SERVER_ADDRESS 2

