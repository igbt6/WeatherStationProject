#include "ds2782.h"


DS2782::DS2782(PinName sda, PinName scl,int i2cFrequencyHz,uint8_t address):mI2c(sda,scl),mI2cAddr(address){
    
    mI2c.frequency(i2cFrequencyHz);
    mTemperature=0;
}   
    
    
bool DS2782::initDS2782(void){
     
     return true;
}

//write data to the sensor
bool DS2782::write(uint8_t regAddress, uint8_t* data,int dataLength)
{
    uint8_t tempBuf[dataLength+1];
    tempBuf[0]=regAddress;
    memcpy(&(tempBuf[1]),data,dataLength);
    return mI2c.write(mI2cAddr,(char*)tempBuf,dataLength+1)==0;

}

//read data from the sensor
bool DS2782::read(uint8_t regAddress, uint8_t *data,int dataLength)
{
    mI2c.write(mI2cAddr,(char*)&regAddress,1,true);
    return (mI2c.read(mI2cAddr,(char*)data,dataLength)==0);
}

bool DS2782::readTemperature(void)
{  
   uint8_t rawData[2];
   uint16_t rawTemp=0;
   if(!read(TEMP_MSB_REG, rawData,2)) return false;
      rawTemp= (((rawData[0]&~(1<<7))<<3)|((rawData[1]>>5)&0xF));
      mTemperature = (float)(rawTemp*0.125);
   return true;
}

float DS2782::getTemperature(void)
{
    return mTemperature;
}


bool DS2782::readCurrent(void){

   uint8_t rawData[2];
   uint16_t rawRes=0;
   if(!read(CURRENT_MSB_REG, rawData,2)) return false;
      rawRes= get16BitData(rawData[0],rawData[1]);
      //rawRes&=~(1<<15);
    if(rawRes &0x8000){
      mCurrent = (float)(rawRes-65536)*0.07813;
    }
    else 
      //mCurrent = (float)(rawRes-32768)*0.07813;
      mCurrent = (float)(rawRes)*0.07813;
   return true;
}

float DS2782::getCurrent(void)
{
    return mCurrent;
}



bool DS2782::readVoltage(void){

   uint8_t rawData[2];
   uint16_t rawVolt=0;
   if(!read(VOLT_MSB_REG, rawData,2)) return false;
      rawVolt= (((rawData[0]&~(1<<7))<<3)|((rawData[1]>>5)&0xF));
      mVoltage= (float)(rawVolt*4.88);
   return true;
}

float DS2782::getVoltage(void)
{
    return mVoltage;
}


bool DS2782::setACRRegister(uint16_t reg)
{    
    uint8_t buf[2];
    buf[0]= ((reg>>8)&0xFF);
    buf[1]= ((reg)&0xFF);
    if(!(write(ACR_MSB_REG, buf,2))) return false;
    return true;        
}


float DS2782::readTest(void){

   uint8_t rawData[2];
   uint16_t rawRes=0;
   /*if(!read(ACR_MSB_REG, rawData,2)) return false;
      rawRes= get16BitData(rawData[0],rawData[1]);
      */
    /*if(rawRes &0x8000){
      return ((float)(rawRes-65536)*0.07813);
    }
    else 
    */
    if(!read(RARC_REG, rawData,1)) return false;
      rawRes= get16BitData(rawData[0],rawData[1]);
    return ((float)(rawData[0]*0.3906));
}
