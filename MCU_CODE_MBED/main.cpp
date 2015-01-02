#include "mbed.h"
#include "sensors.h"
#include "SLCD.h"


//DigitalOut myled(LED_GREEN);



/*SENSORS sensors;
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
*/
//DEBUG
static void timerCounter(void const *arg)
{

    SLCD slcd;
    static int counter =0;
    counter++;
    slcd.printf("%d", counter);
}

int main()
{
    RtosTimer debugTimer(timerCounter, osTimerPeriodic, (void *)0);
    //TESTS:
    GTS4E60 gps(GPS_PIN_TX,GPS_PIN_RX);
    Serial debug(USBTX, USBRX);
    debug.baud(115200);
    //Thread measThread(SensorsMeasurementFuncWrapper,NULL,osPriorityAboveNormal);
    //Thread printResultsThread(SensorsPrintfDataFuncWrapper,NULL,osPriorityHigh);
    //Thread waitForEventsThread(SensorsWaitAsyncEventsWrapper,NULL,osPriorityHigh);
    debugTimer.start(1000);
    while(1) {
        if(gps.isDataAvailable()) {
            if(gps.parseData()) {
                struct UTC_Time utcTime= gps.getTime();
                struct Date date= gps.getDate();
                debug.printf("GPS_DATA: %2d:%2d:%02.3f\r\n",utcTime.hours, utcTime.minutes, utcTime.seconds);
                debug.printf("GPS_DATA: fixtype: %d, satelites: %d, altitude: %f\r\n",gps.getFixType(), gps.getSatellites(), gps.getAltitude());
                debug.printf("GPS_DATA: validity: %c, latitude: %f, ns :%c, longitude: %f, ew: %c\r\n",gps.getStatus(), gps.getLatitude(), gps.getNS(), gps.getLongitude(), gps.getEW());
                debug.printf("GPS_DATA: speed: %f, heading: %f, DATE: %02d %02d %02d\r\n", gps.getSpeedKm(), gps.getHeading(), date.day, date.month, date.year);
            } else {
              debug.printf("NO GPS FIX FOUND\r\n");
            }
        }
    }
    return 0;
}
