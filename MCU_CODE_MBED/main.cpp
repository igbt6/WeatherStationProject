#include "mbed.h"
#include "sensors.h"
#include "SLCD.h"
//#include "LCD40x2.h"

//DigitalOut myled(LED_GREEN);


SENSORS sensors;
void SensorsMeasurementFuncWrapper(void const* args){
    sensors.measurement(args);
} 
void SensorsPrintfDataFuncWrapper(void const* args){
    sensors.getResults(args);
} 
/*
void SensorsSaveDataToUSBdeviceFuncWrapper(void const* args){
    sensors.saveDataToUSB(args);
} 
*/


SLCD slcd; //[88:88][8.8.8.8] SegmentLCD


int main(){
    slcd.printf("AAA");
    Thread measThread(SensorsMeasurementFuncWrapper,NULL,osPriorityAboveNormal);
    Thread printResultsThread(SensorsPrintfDataFuncWrapper,NULL,osPriorityHigh);

  while(1){}
  return 0;
}
