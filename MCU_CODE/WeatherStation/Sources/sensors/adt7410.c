#include "adt7410.h"
#include <string.h>

/*************typedefs:*************/

typedef enum {
	CONT_CONV = 0, ONE_SHOT, SPS_MODE, SHUTDOWN
} CONF_OPERATION_MODE;

typedef enum {
	INTERRUPT_MODE = 0, COMPARATOR_MODE = 1
} CONF_INT_CT_MODE;

typedef enum {
	INT_ACTIVE_LOW = 0, INT_ACTIVE_HIGH = 1
} CONF_INT_PIN_POLARITY;

typedef enum {
	CT_ACTIVE_LOW = 0, CT_ACTIVE_HIGH = 1
} CONF_CT_PIN_POLARITY;

typedef enum {
	_1_FAULT = 0, _2_FAULTS, _3_FAULTS, _4_FAULTS
} CONF_FAULT_QUEUE;

/*************private variables:*************/
static float mAdt7410CurrentTemperature;
static uint8_t mAdt7410Resolution;
static I2C_MODULE mI2cModule;

/*************private methods:*************/

//transmit data to the sensor
static bool adt7410Write(uint8_t regAddress, uint8_t *data, int dataLength) {
	//LDD_TError retValue;
	//uint8_t temp[dataLength + 1];
	//temp[0] = regAddress;
	//memcpy(&temp[1], data, dataLength);
	return i2cWrite(ADT7410_I2C_ADDRESS, regAddress, data, dataLength,
			mI2cModule);
}

//read data from the sensor
static bool adt7410Read(uint8_t regAddress, uint8_t *data, int dataLength) {
	return i2cRead(ADT7410_I2C_ADDRESS, regAddress, data, dataLength, mI2cModule);
}

//configuration of ADT7410 sensor
static bool adt7410SetConfiguration(CONF_FAULT_QUEUE faultQueue,
		CONF_CT_PIN_POLARITY ctPinPolarity,
		CONF_INT_PIN_POLARITY intPinPolarity, CONF_INT_CT_MODE intCtMode,
		CONF_OPERATION_MODE operMode, CONF_RESOLUTION res) {

	uint8_t confByte = 0;
	bool retVal = 0;

	confByte = (res << 7 | operMode << 5 | intCtMode << 4 | intPinPolarity << 3
			| ctPinPolarity << 2 | faultQueue);
	if (!adt7410Write(0x03, &confByte, 1))
		retVal = false;
	else
		retVal = true;
	return retVal;

}

/*************public methods:*************/
//Init method, modify values here;
// NOTIFY!!! - this function must be used before using other functions for the sensor
void adt7410Init(LDD_TDeviceData* i2cHandlePtr,I2C_MODULE i2cModule) {
	//i2cInit(I2C1_mod, ADT7410_I2C_ADDRESS);
	//adt7410SetConfiguration(...);
	if (i2cHandlePtr == NULL)
		while (1)  //do something here. i2C has not been not initialized
			;
	mI2cModule =i2cModule;
	if(!adt7410SetResolution(_16_BIT))while (1)  //do something here. i2C has not been not initialized
		;

}

// read 13 bit temperature
int adt7410ReadTemp() {

	//char rData[2] = { 0, 0 };
	uint8_t rData[2] = { 0, 0 };
	float tempFin = 0;
	int tempRaw = 0;
	if (!adt7410Read(0x00, rData, 2))
		return 0;

	// temperature returned is only 13 bits
	// discard alarm flags in lower bits
	tempRaw = (rData[0] << 8) | (rData[1]);
	if (mAdt7410Resolution == _13_BIT) { ////resolution 13 --- bit 0.0625°C
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

	mAdt7410CurrentTemperature = tempFin;
	return 1;
}

int adt7410SetResolution(CONF_RESOLUTION res) {

	uint8_t temp = 0;

	int retVal = 0;
	if (!adt7410Read(0x03, &temp, 1))
		return 0;
	temp |= res << 7;
	if (!adt7410Write(0x03, &temp, 1))

		retVal = 0;
	else
		retVal = 1;
	mAdt7410Resolution = res;
	return retVal;
}

int adt7410GetIdNumber(void) {

	uint8_t data = 0;
	uint8_t regAddress = 0x0B;
	if (adt7410Read(regAddress, &data, 1))
		return data;
	else
		return 0;

}

float adt7410GetTemperature(void) {
	return mAdt7410CurrentTemperature;
}
