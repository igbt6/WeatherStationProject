#include "mbed.h"
#include "sensors.h"
#include "LCD40x2.h"

//DigitalOut myled(LED_GREEN);


SENSORS sensors;
void SensorsMeasurementFuncWrapper(void const* args){
    sensors.measurement(args);
} 
void SensorsPrintfDataFuncWrapper(void const* args){
    sensors.getResults(args);
} 

void SensorsSaveDataToUSBdeviceFuncWrapper(void const* args){
    sensors.saveDataToUSB(args);
} 


int main(){
    Thread measThread(SensorsMeasurementFuncWrapper,NULL,osPriorityAboveNormal);
    Thread printResultsThread(SensorsPrintfDataFuncWrapper,NULL,osPriorityHigh);
    Thread saveResultsOnUSBdeviceThread(SensorsSaveDataToUSBdeviceFuncWrapper,NULL,osPriorityNormal);

  while(1){
     sensors.showError(); //should never reach here
     }
 return 0;
}
