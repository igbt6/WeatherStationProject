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
        gps.parseData();
        debug.printf("GPS_DATA: %2d:%2d:%02.3f\r\n",gps.hours, gps.minutes, gps.seconds);
    
    }
    return 0;
}
