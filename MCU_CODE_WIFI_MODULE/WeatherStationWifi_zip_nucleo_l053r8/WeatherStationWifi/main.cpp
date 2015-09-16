#include "mbed.h"
#include <string.h>
#include "main.h"
#include "RF22ReliableDatagram.h"
 





#define SET 1
#define NOTSET 0








//MAIN APPLICATION##########################################


static void debugInit(void)
{   
    if(DEBUG_ENABLED)
    { 
        usbDebug =new Serial(USBTX, USBRX);
        usbDebug->baud(115200);
    }
}



// create singleton objects
//RFM23B
static RF22ReliableDatagram* rfm23b;



uint8_t data[] = "DATA_FROM_WIFI_MODULE";
uint8_t buf[RF22_MAX_MESSAGE_LEN];


static volatile uint32_t askStationFlag = 0;
//private functions

int main() {
    debugInit();
    DEBUG("HELLO SYSTEM!\r\n");
#ifdef RFM23D_ENABLED
    rfm23b =new RF22ReliableDatagram(STATION_ADDRESS,RFM_PIN_nSEL, RFM_PIN_SDI ,RFM_PIN_SDO,RFM_PIN_SCLK,RFM_PIN_nIRQ,RFM_PIN_SDN  );
    int res= rfm23b->init();
    //if(rfm23b->init()==333) {
        //DEBUG("rfm23b init failed\r\n");
        DEBUG("RES: %.2d\r\n", res);
         //printf("RES: %d %%\n", res);
        //while(1);
    //} else
        //DEBUG("rfm23b init succes\r\n");
    //    DEBUG("RES: %d\r\n",res);
#endif
    while(1) {
    #ifdef RFM23D_ENABLED
        if (askStationFlag == SET) {
            // Wait for a message addressed to us from the client
            uint8_t len = sizeof(buf);
            uint8_t from;

    
            if (!rfm23b->sendtoWait(data, sizeof(data), STATION_ADDRESS)) {
                DEBUG("sending request to station failed...");
            } 
            else {
                if (rfm23b->recvfromAckTimeout(buf, &len, 1000, &from)) {
                    DEBUG("received data from Station : 0x");
                    DEBUG("from");
                    /*Serial.print(": ");
                     Serial.print((char*) buf);
                     Serial.print("\r\n");
                     */
                }
            }
    #endif
        }
    }
}

