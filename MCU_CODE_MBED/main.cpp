#include "mbed.h"
#include "sensors.h"
#include "SLCD.h"



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
    Thread measThread(SensorsMeasurementFuncWrapper,NULL,osPriorityAboveNormal);
    Thread printResultsThread(SensorsPrintfDataFuncWrapper,NULL,osPriorityHigh);
    Thread waitForEventsThread(SensorsWaitAsyncEventsWrapper,NULL,osPriorityHigh);
    debugTimer.start(1000);
    while(1) {
    }
    return 0;
}
