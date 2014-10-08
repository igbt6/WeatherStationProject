#include "adt7410.h"

/*  static LDD_TDeviceData* mI2c;


 static I2C_DeviceData mI2C1_DeviceData;
 */

/*
 ADT7410::ADT7410(LDD_TDeviceData* i2c,CONF_RESOLUTION res ){
 mI2c = i2c;
 if(res==_16_BIT){
 setResolution(_16_BIT);
 }
 }
 */

void initADT7410(void) {
	/*	  mI2C1_DeviceData.dataReceivedFlag=0;
	 mI2C1_DeviceData.dataReceivedFlag=0;
	 mI2c=  I2C1_Init(&mI2C1_DeviceData);

	 I2C1_SelectSlaveDevice( mI2c, LDD_I2C_ADDRTYPE_7BITS, ADT7410_I2C_ADDRESS);
	 */
	i2cInit(I2C1_mod, ADT7410_I2C_ADDRESS);
}

bool /*ADT7410::*/write(uint8_t regAddress, uint8_t data) {
	LDD_TError retValue;
	char temp[2];
	temp[0] = regAddress;
	temp[1] = data;
	// return mI2c.write(i2cAddr,temp,2)==0;
	// return I2C1_MasterSendBlock(mI2c,temp,2,LDD_I2C_SEND_STOP);
	return i2cWrite(regAddress, temp, 2, I2C1_mod);
}

//read data from the sensor
int /*ADT7410::*/read(uint8_t regAddress, uint8_t *data, int length) {
	//mI2c.write(i2cAddr,(char*)&regAddress,1);
	// if(mI2c.read(i2cAddr,(char*)data,length)==0) return 1;
	/*
	 LDD_TError retValue;
	 I2C1_MasterSendBlock(mI2c,&regAddress,1,LDD_I2C_NO_SEND_STOP);
	 while(!mI2C1_DeviceData.dataTransmitFlag);
	 mI2C1_DeviceData.dataTransmitFlag=0;
	 retValue=I2C1_MasterReceiveBlock( mI2c,data,length,LDD_I2C_SEND_STOP);
	 while(!mI2C1_DeviceData.dataReceivedFlag);
	 mI2C1_DeviceData.dataReceivedFlag=0;
	 if(retValue==ERR_OK)return 1;


	 return -1;

	 */

	return i2cRead(regAddress, data, length, I2C1_mod);
}

//configuration of ADT7410 sensor
/*int ADT7410::initADT7410(CONF_FAULT_QUEUE faultQueue, CONF_CT_PIN_POLARITY ctPinPolarity, CONF_INT_PIN_POLARITY intPinPolarity, CONF_INT_CT_MODE intCtMode, CONF_OPERATION_MODE operMode, CONF_RESOLUTION res){

 uint8_t confByte=0;
 int retVal=0;

 confByte=(res<<7|operMode<<5|intCtMode<<4|intPinPolarity<<3|ctPinPolarity<<2|faultQueue);
 if(!write(0x03,confByte))retVal=-1;
 else retVal=1;
 return retVal;

 }
 */
// read 13 bit temperature
int /*ADT7410::*/readTemp() {

	char rData[2] = { 0, 0 };
	float tempFin = 0;
	int tempRaw = 0;

	// set address pointer to temperature register
	//   if(mI2c.write(i2cAddr, 0x00, 1))return -1;

	// read temperature register, two bytes
	//  if(mI2c.read(i2cAddr, rData, 2))return -1;

	// temperature returned is only 13 bits
	// discard alarm flags in lower bits
	tempRaw = (rData[0] << 8) | (rData[1]);
	if (resolution == _13_BIT) { ////resolution 13 --- bit 0.0625°C
		tempRaw >>= 3;
		if (tempRaw & 0x1000) {
			tempFin = (float) (tempRaw - 8192) / 16;
		} else {
			tempFin = (float) tempRaw / 16;
		}
	} else {  //resolution 16bit --- 0.0078°C.

		if (tempRaw & 0x8000) {
			tempFin = (float) (tempRaw - 65536) / 128;
		} else
			tempFin = (float) tempRaw / 128;
	}

	currentTemperature = tempFin;
	return 1;
}

int /*ADT7410::*/setResolution(CONF_RESOLUTION res) {

	uint8_t temp = 0;

	int retVal = 0;
	if (!read(0x03, &temp, 1))
		return -1;
	temp |= res << 7;
	if (!write(0x03, temp))

		retVal = 0;
	else
		retVal = 1;

	return retVal;
}

int /* ADT7410::*/getIdNumber(void) {

	uint8_t data = 0;
	uint8_t regAddress = 0x0B;

	//if(mI2c.write(i2cAddr,(char*)&regAddress,1,true)) return -1;
	//if(mI2c.read(i2cAddr,(char*)&data,1)) return -1;
	// if(I2C1_MasterReceiveBlock( mI2c,&data,1,LDD_I2C_SEND_STOP)==ERR_OK)
	if (read(regAddress, &data, 1))
		return data;
	else
		return 2;

}
