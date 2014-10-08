/*
 * i2c.c
 *
 *  Created on: 8 paz 2014
 *      Author: lukasz
 */

#include "i2c.h"

#define IS_I2C_MODULE(x) if(x==I2C0_mod||x==I2C1_mod)

/*
 static LDD_TDeviceData* mI2C1 =NULL;
 static LDD_TDeviceData* mI2C0 =NULL;
 static I2C_DeviceData mI2C1_DeviceData;
 static I2C_DeviceData mI2C0_DeviceData;
 */

typedef struct {
	LDD_TDeviceData* mI2c;
	I2C_DeviceData mI2c_DeviceData;
} I2cHandle;

static I2cHandle mI2c1Handle;
static I2cHandle mI2c0Handle;

void i2cInit(I2C_MODULE module, uint8_t slaveAddr) {

	if (module == I2C0_mod) {

	} else {
		mI2c1Handle.mI2c_DeviceData.dataReceivedFlag = false;
		mI2c1Handle.mI2c_DeviceData.dataTransmitFlag = false;
		mI2c1Handle.mI2c = I2C1_Init(&mI2c1Handle.mI2c_DeviceData);
		I2C1_SelectSlaveDevice(mI2c1Handle.mI2c, LDD_I2C_ADDRTYPE_7BITS,
				slaveAddr);

	}

}

bool i2cRead(uint8_t regAddress, uint8_t *data, int dataLength,
		I2C_MODULE module) {

	if (module == I2C0_mod) {

	} else {
		LDD_TError res;
		res = I2C1_MasterSendBlock(mI2c1Handle.mI2c, &regAddress, 1,
				LDD_I2C_NO_SEND_STOP);
		if (res != ERR_OK) {
			return false;
		}
		while (!mI2c1Handle.mI2c_DeviceData.dataTransmitFlag)
			;
		mI2c1Handle.mI2c_DeviceData.dataTransmitFlag = false;
		res = I2C1_MasterReceiveBlock(mI2c1Handle.mI2c, data, dataLength,
				LDD_I2C_SEND_STOP);
		if (res != ERR_OK) {
			return false;
		}
		while (!mI2c1Handle.mI2c_DeviceData.dataReceivedFlag)
			;
		mI2c1Handle.mI2c_DeviceData.dataReceivedFlag = false;
		return true;
	}
}

bool i2cWrite(uint8_t regAddress, uint8_t *data, int dataLength,I2C_MODULE module) {
	if (module == I2C0_mod) {

	} else {
		LDD_TError res;
		res = I2C1_MasterSendBlock(mI2c1Handle.mI2c, &regAddress, 1,
				LDD_I2C_NO_SEND_STOP);
		if (res != ERR_OK) {
			return false;
		}
		while (!mI2c1Handle.mI2c_DeviceData.dataTransmitFlag)
			;
		mI2c1Handle.mI2c_DeviceData.dataTransmitFlag = false;

		res = I2C1_MasterSendBlock(mI2c1Handle.mI2c, data, dataLength,
				LDD_I2C_SEND_STOP);
		if (res != ERR_OK) {
			return false;
		}
		while (!mI2c1Handle.mI2c_DeviceData.dataTransmitFlag)
			;
		mI2c1Handle.mI2c_DeviceData.dataTransmitFlag = false;

		return true;
	}

}
