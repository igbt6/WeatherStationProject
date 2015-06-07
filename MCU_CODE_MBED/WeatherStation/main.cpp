
#include "mbed.h"
#include "sensors.h"
#include "RF22ReliableDatagram.h"
#include "SLCD.h"


//DEBUG
static void timerCounter(void const *arg)
{
    SLCD slcd;
    static int counter =0;
    counter++;
    slcd.printf("%d", counter);
}




/////////////////////// MAIN APPLICATION ////////////////////////////////////////////////////////

SENSORS sensors;

void SensorsMeasurementFuncWrapper(void const* args)
{
    sensors.measurement(args);
}
void SensorsPrintfDataFuncWrapper(void const* args)
{
    sensors.getResults(args);
}

void SensorsWaitAsyncEventsWrapper(void const* args)
{
    sensors.waitForEvents(args);
}



int main()
{
    RtosTimer debugTimer(timerCounter, osTimerPeriodic, (void *)0);
    Thread measThread(SensorsMeasurementFuncWrapper,NULL,osPriorityAboveNormal);
    Thread printResultsThread(SensorsPrintfDataFuncWrapper,NULL,osPriorityNormal);
    Thread waitForEventsThread(SensorsWaitAsyncEventsWrapper,NULL,osPriorityHigh);
    debugTimer.start(1000);
    while(1) {
    }
    return 0;
}



///////////////////////GPS TESTS////////////////////////////////////////////////////////

/*
#include "mbed.h"
#include "gts4E60.h"
#define GPS_PIN_RX  PTE17    //UART2 on frdmkl46z
#define GPS_PIN_TX  PTE16
int main()
{
    GTS4E60 gps(GPS_PIN_TX,GPS_PIN_RX,GPS_PIN_SHUTDOWN);
    Serial debug(USBTX, USBRX);
    debug.baud(115200);
    debug.printf("hello world");
    while(1) {
        if(gps.isDataAvailable()) {
            if(gps.parseData()) {
                struct UTC_Time utcTime= gps.getTime();
                struct Date date= gps.getDate();
                debug.printf("GPS_UTC_TIME: %02d:%02d:%02.3f\r\n",utcTime.hours, utcTime.minutes, utcTime.seconds);
                debug.printf("GPS_DATE: %02d.%02d.%02d\r\n", date.day, date.month, date.year);
                debug.printf("GPS_DATA: fixtype: %d, satelites: %d, altitude: %f, speed: %f, heading: %f\r\n",gps.getFixType(), gps.getSatellites(), gps.getAltitude(), gps.getSpeedKm(), gps.getHeading());
                debug.printf("GPS_DATA: status: %c, latitude: %f, ns :%c, longitude: %f, ew: %c\r\n",gps.getStatus(), gps.getLatitude(), gps.getNS(), gps.getLongitude(), gps.getEW());
            } else {
                debug.printf("NO GPS FIX FOUND\r\n");
            }
        }
        else {debug.printf("No Gps data available\r\n "); 
        wait_ms(500);}
    }
    return 0;
}




*/
/////////////////////// RFM23 MODULES TESTS////////////////////////////////////////////////////////



/*

#define RFM_PIN_SDO  PTA17    //MISO
#define RFM_PIN_SDI   PTA16    //MOSI
#define RFM_PIN_SCLK  PTA15    //SCK
#define RFM_PIN_nSEL  PTA14
#define RFM_PIN_nIRQ  PTA6    //(as IRQ)
#define RFM_PIN_SDN   PTA5

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2
// DATAGRAMM EXAMPLE

int main()
{RtosTimer debugTimer(timerCounter, osTimerPeriodic, (void *)0);
//PinName slaveSelectPin , PinName mosi, PinName miso, PinName sclk, PinName interrupt
    // Singleton instance of the radio
    RF22ReliableDatagram rfm23b(CLIENT_ADDRESS,RFM_PIN_nSEL, RFM_PIN_SDI ,RFM_PIN_SDO,RFM_PIN_SCLK,RFM_PIN_nIRQ,RFM_PIN_SDN  );
    Serial debug(USBTX, USBRX);
    debug.baud(115200);
    wait_ms(2000);
    if(!rfm23b.init())
        debug.printf("rfm23b init failed");
    // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
    else
        debug.printf("rfm23b init succes");

    uint8_t data[] = "HelloWorld!";
    // Dont put this on the stack:
    uint8_t buf[20];
    //debugTimer.start(1000);
    while(1) {
            // Send a message to rf23_server
    debug.printf("Sending to rf23_datagram_server\r\n");
    if (!rfm23b.sendtoWait(data, sizeof(data), SERVER_ADDRESS))
        debug.printf("Sending failed....\r\n");
    else{
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (rfm23b.recvfromAckTimeout(buf, &len,1000, &from)) {
            debug.printf("got request from : 0x%x",from);
            debug.printf(": ");
            debug.printf((char*)buf);
            // Send a reply back to the originator client

        }
        else
            debug.printf("No reply, is rf22_datagram_server running?\n");
    }
    }
    return 0;
}
*/
/*
// CLIENT NORMAL
int main()
{
    RtosTimer debugTimer(timerCounter, osTimerPeriodic, (void *)0);
//PinName slaveSelectPin , PinName mosi, PinName miso, PinName sclk, PinName interrupt
    // Singleton instance of the radio
    RF22 rfm23b(RFM_PIN_nSEL, RFM_PIN_SDI ,RFM_PIN_SDO,RFM_PIN_SCLK,RFM_PIN_nIRQ,RFM_PIN_SDN  );
    Serial debug(USBTX, USBRX);
    debug.baud(115200);
    wait_ms(2000);
    if(!rfm23b.init())
        debug.printf("rfm23b init failed");
    // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
    else
        debug.printf("rfm23b init succes");

    uint8_t data[] = "HelloWorld!";
    // Dont put this on the stack:
    uint8_t buf[20];
    //debugTimer.start(1000);
    while(1) {
        // Send a message to rf23_server
        debug.printf("Sending to rf23_datagram_server\r\n");
        rfm23b.send(data, sizeof(data));
        rfm23b.waitPacketSent();
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (rfm23b.waitAvailableTimeout(5000)) {
            // Should be a message for us now
            if (rfm23b.recv(buf, &len)) {
                debug.printf("got reply: ");
                debug.printf((char*)buf);
            } else {
                debug.printf("recv failed");
            }
        } else {
            debug.printf("No reply, is rf22_server running?");
        }
    }

    return 0;
}
*/