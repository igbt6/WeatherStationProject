
#include "AS3935.h"

AS3935::AS3935(PinName sda, PinName scl, PinName irqPin,int i2cFrequencyHz,uint8_t address):mI2c(sda,scl),mI2cAddr(address),mIrqPinInterrupt(irqPin)
{

    mI2c.frequency(i2cFrequencyHz);
    mIrqPinInterrupt.rise(this,&AS3935::handleIrqInterrupt);
    if(!initAS3935()); //while(1); //TODO handle error
    wait_ms(11);
}


bool AS3935::initAS3935(void)
{

    if(!powerUp())return false;
    return true;
}

void AS3935::handleIrqInterrupt(void)
{
    uint8_t typeOfInterrupt=readInterruptSource();
    switch(typeOfInterrupt) {
    
    case INTERRUPTS_INT_NH:  //Noise level too high
         //do nothing
    break;
    
    case INTERRUPTS_INT_D:   //diturber detected
         // do nothing
    break;
    
    case INTERRUPTS_INT_L:  //Lightning interrupt
        int distance = lightningDistanceKm();
        if(distance!=-1)
            queue.put((uint8_t*)&distance);
    break;
    }
}



osEvent AS3935::checkQueueState(void){
    return queue.get();
}


bool AS3935::reset()
{
    bool retVal;
    uint8_t cmd[2];
    cmd[0]=0x3C;
    cmd[1]=0x96;
    retVal=write(cmd[0] ,&cmd[1], 1);
    wait_ms(2);
    return retVal;
}



bool AS3935::powerDown()
{
    return writeReg(AS3935_PWD,1);
}

bool AS3935::powerUp()
{
    int retVal=0;
    uint8_t cmd[2];
    cmd[0]=0x3D;
    cmd[1]=0x96;
    readReg(AS3935_PWD,0);
    retVal+=write(cmd[0] ,&cmd[1], 1);
    wait_ms(3);
    retVal+=writeReg(AS3935_DISP_TRCO,1);
    wait_ms(2);
    retVal+=writeReg(AS3935_DISP_TRCO,0);
    if(retVal==3)return true;
    return false;
}

int AS3935::readInterruptSource()
{
    uint8_t data;
    if(!readReg(AS3935_INT,&data)) return -1;
    return data;
}

bool AS3935::disableDisturbers()
{
    return writeReg(AS3935_MASK_DIST,1);
}

bool AS3935::enableDisturbers()
{
    return writeReg(AS3935_MASK_DIST,0);
}

int AS3935::getMinimumLightnings()
{
    uint8_t data;
    if(!readReg(AS3935_MIN_NUM_LIGH,&data)) return -1;
    return data;
}

int AS3935::setMinimumLightnings(int minlightning)
{
    writeReg(AS3935_MIN_NUM_LIGH,minlightning);
    return getMinimumLightnings();
}

int AS3935::lightningDistanceKm()
{
    uint8_t data;
    if(!readReg(AS3935_DISTANCE,&data)) return -1;
    return data;
}

void AS3935::setIndoors()
{
    writeReg(AS3935_AFE_GB,AS3935_AFE_INDOOR);
}

void AS3935::setOutdoors()
{
    writeReg(AS3935_AFE_GB,AS3935_AFE_OUTDOOR);
}

int AS3935::getNoiseFloor()
{
    uint8_t data;
    if(!readReg(AS3935_NF_LEV,&data)) return -1;
    return data;
}

int AS3935::setNoiseFloor(int noisefloor)
{
    writeReg(AS3935_NF_LEV,noisefloor);
    return getNoiseFloor();
}

int AS3935::getSpikeRejection()
{
    uint8_t data;
    if(!readReg(AS3935_SREJ,&data)) return -1;
    return data;
}

int AS3935::setSpikeRejection(int srej)
{
    writeReg(AS3935_SREJ, srej);
    return getSpikeRejection();
}

int AS3935::getWatchdogThreshold()
{
    uint8_t data;
    if(!readReg(AS3935_WDTH,&data)) return -1;
    return data;
}

int AS3935::setWatchdogThreshold(int wdth)
{
    writeReg(AS3935_WDTH,wdth);
    return getWatchdogThreshold();
}

int AS3935::getTuneCap()
{
    uint8_t data;
    if(!readReg(AS3935_TUN_CAP,&data)) return -1;
    return data;
}

int AS3935::setTuneCap(int cap)
{
    writeReg(AS3935_TUN_CAP,cap);
    return getTuneCap();
}

void AS3935::clearStats()
{
    writeReg(AS3935_CL_STAT,1);
    writeReg(AS3935_CL_STAT,0);
    writeReg(AS3935_CL_STAT,1);
}









//privates
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


uint8_t AS3935::getShiftValue(uint8_t dataBitMask)
{
    uint8_t shiftVal=0;
    while(!( dataBitMask & 1)) {
        dataBitMask >>= 1;
        shiftVal++;
    }
    return shiftVal;
}



bool AS3935::writeReg(uint8_t regAddress, uint8_t dataBitMask, uint8_t data)
{

    uint8_t tempVal;
    if(!read(regAddress,&tempVal,1)) return false;
    tempVal&=~(dataBitMask);
    tempVal|= data<<getShiftValue(dataBitMask);
    return write(regAddress, &tempVal,1);

}

bool AS3935::readReg(uint8_t regAddress, uint8_t dataBitMask, uint8_t *data)
{

    uint8_t tempVal;
    if(!read(regAddress,&tempVal,1)) return false;
    tempVal&=dataBitMask;
    tempVal>>=getShiftValue(dataBitMask);
    *data= tempVal;
    return true;
}

