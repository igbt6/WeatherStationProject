
#include "AS3935.h"

AS3935::AS3935(PinName sda, PinName scl, PinName irqPin,int i2cFrequencyHz,uint8_t address):mI2c(sda,scl),mI2cAddr(address) {        
        
    mI2c.frequency(i2cFrequencyHz);
    if(!initAS3935()); //while(1); //TODO handle error
        wait_ms(11);
}

   
bool AS3935::initAS3935(void){
     
     //uint8_t  data;
     //data= heaterEnabled<<2|measRes ;
     //return write(WRITE_RH_T,&data,1);
     return true;
}


//write data to the sensor
bool AS3935::write(uint8_t regAddress, uint8_t* data,int dataLength)
{
    uint8_t tempBuf[dataLength+1];
    tempBuf[0]=regAddress;
    memcpy(&(tempBuf[1]),data,dataLength);
    return mI2c.write(mI2cAddr,(char*)tempBuf,dataLength+1)==0;

}

//read data from the sensor
bool AS3935::read(uint8_t regAddress, uint8_t *data,int dataLength)
{
    mI2c.write(mI2cAddr,(char*)&regAddress,1,true);
    return (mI2c.read(mI2cAddr,(char*)data,dataLength)==0);
}


uint8_t AS3935::getShiftValue(uint8_t dataBitMask){
    uint8_t shiftVal=0;
    while(!( dataBitMask & 1)) {
          dataBitMask >>= 1;
          shiftVal++;
    }
    return shiftVal;
}



bool AS3935::writeReg(uint8_t regAddress, uint8_t dataBitMask, uint8_t data){
    
    uint8_t tempVal;
    if(!read(regAddress,&tempVal,1)) return false;
    tempVal&=~(dataBitMask);
    tempVal|= data<<getShiftValue(dataBitMask);
    return write(regAddress, &tempVal,1);
    
}

bool AS3935::readReg(uint8_t regAddress, uint8_t dataBitMask, uint8_t *data){
    
    uint8_t tempVal;
    if(!read(regAddress,&tempVal,1)) return false;
    tempVal&=dataBitMask;
    tempVal>>=getShiftValue(dataBitMask);
    *data= tempVal;
    return true;
}


