/*
 * max9611.c
 *
 *  Created on: 10 lis 2014
 *      Author: lukasz
 */
#include "max9611.h"

/**********private members and methods********************************/

/***************************************private typedefs*****************************/
typedef enum {
	CHANNEL_A_0 = 0, /*Read current-sense amplifier output from ADC, gain = 1x*/
	CHANNEL_A_1, /*Read current-sense amplifier output from ADC, gain = 4x*/
	CHANNEL_A_2, /*Read current-sense amplifier output from ADC, gain = 8x*/
	CHANNEL_B, /*Read average voltage of RS+ (input common-mode voltage) from ADC*/
	CHANNEL_C, /*Read voltage of OUT from ADC*/
	CHANNEL_D, /*Read voltage of SET from ADC*/
	CHANNEL_E, /*Read internal die temperature from ADC*/
	ALL_CHANNELS /*Read all channels in fast-read mode, sequentially every 2ms. Uses last gain setting.*/
} eCtrlReg1MUX;

typedef enum {
	NORMAL_OPERATION_SHDN = 0, SHUTDOWN_MODE
} eCtrlReg1SHDN;

typedef enum {
	NORMAL_OPERATION_LR = 0, RESET
} eCtrlReg1LR;

typedef enum {
	NORMAL_OPERATION_MODE = 0, COMPARATOR_MODE = 7, OPAMP_MODE = 3
} eCtrlReg1MODE;

//watchdog delay time
typedef enum {
	_1MS = 0, _100US = 1
} eCtrlReg2DTIM;

//watchdog retry delay time
typedef enum {
	_50MS = 0, _10MS = 1
} eCtrlReg2RTIM;

//watchdog retry delay time
typedef enum {
	CSA_DATA_BYTE_MSB_ADRR = 0x00,
	CSA_DATA_BYTE_LSB_ADRR = 0x01,
	RS_DATA_BYTE_MSB_ADRR = 0x02,
	RS_DATA_BYTE_LSB_ADRR = 0x03,
	OUT_DATA_BYTE_MSB_ADRR = 0x04,
	OUT_DATA_BYTE_LSB_ADRR = 0x05,
	SET_DATA_BYTE_MSB_ADRR = 0x06,
	SET_DATA_BYTE_LSB_ADRR = 0x07,
	TEMP_DATA_BYTE_MSB_ADRR = 0x08,
	TEMP_DATA_BYTE_LSB_ADRR = 0x09,
	CONTROL_REGISTER_1_ADRR = 0x0A,
	CONTROL_REGISTER_2_ADRR = 0x0B
} eRegAddresses;

/***************************************private members*****************************/

static I2C_MODULE mI2c;
//static int mI2cAddr;   for future use
static float mTemperature;
static float mCurrentSenseAmplifierOutput;
const uint16_t csaCurrentValueOffset = 0x0a; //0x10;

/***************************************private methods*****************************/
//write data to the sensor
static bool max9611Write(uint8_t regAddress, uint8_t* data, int dataLength) {

	return i2cWrite(MAX9611_I2C_ADDRESS, regAddress, data, dataLength, mI2c);
}

//read data from the sensor
static bool max9611Read(uint8_t regAddress, uint8_t *data, int dataLength) {

	return i2cRead(MAX9611_I2C_ADDRESS, regAddress, data, dataLength, mI2c);
}


/** configuration of MAX9611: sets member values and configuration registers, ought to be invoked in the body of constructor
 * @returns
 *    true on success,
 *    false on error
 */
static bool max9611Configuration(eCtrlReg1MUX mux, eCtrlReg1SHDN shdn,
		eCtrlReg1LR lr, eCtrlReg1MODE mode, eCtrlReg2DTIM watchdogDelay,
		eCtrlReg2RTIM watchdogRetryDelay) {

	uint8_t retVal = 0;
	uint8_t controlReg1 = 0;
	uint8_t controlReg2 = 0;

	controlReg1 = (mode << 5 | lr << 4 | shdn << 3 | mux);
	controlReg2 = (watchdogDelay << 3 | watchdogRetryDelay << 2);
	retVal += max9611Write(CONTROL_REGISTER_1_ADRR, &controlReg1, 1);
	retVal += max9611Write(CONTROL_REGISTER_2_ADRR, &controlReg2, 1);
	if (retVal != 2)
		return false;
	return true;
}

/** Make 12 bit data from 2 bytes received from thr device data read from Data regiters of Max9611/9612 are laid in the following way :
 * Byte 1: bit7-MSB12........bit0-MSB05; Byte 2: bit7-LSB04.... bit4-LSB00
 * @param MSB byte
 * @param 4 bits of LSB bytes
 * @returns 1 2bit data
 *
 */
static inline uint16_t get12BitData(uint8_t msbByte, uint8_t lsbByte) {
	uint16_t data12Bit = (msbByte << 4) | ((lsbByte >> 4) & 0x0F);
	return data12Bit;
}

static inline uint16_t get9BitData(uint8_t msbByte, uint8_t lsbByte) {
	uint16_t data9Bit = (msbByte << 1) | ((lsbByte >> 6) & 0x01);
	return data9Bit;

}

/*************************************public methods *****************************************/

bool max9611Init(LDD_TDeviceData* i2cHandlePtr, I2C_MODULE i2cModule
/*int address*/) {

	mI2c = i2cModule;
	//mI2cAddr = address; for future use, if more than sensor exists
	if (i2cHandlePtr == NULL)
		while (1)
			;  //do something here. i2C has not been not initialized
	if (!max9611Configuration(CHANNEL_E, NORMAL_OPERATION_SHDN,
			NORMAL_OPERATION_LR, NORMAL_OPERATION_MODE, _1MS, _50MS))
		while (1)
			;  //TODO handle error

	mTemperature = 0;
	mCurrentSenseAmplifierOutput = 0;
	return true;
}

bool max9611ReadTemp(void) {
	uint8_t rawData[2];
	uint16_t rawTemp = 0;
	if (!max9611Read(TEMP_DATA_BYTE_MSB_ADRR, rawData, 2))
		return false;
	rawTemp = get9BitData(rawData[0], rawData[1]);
	//mRawInt =rawTemp;
	if (rawTemp & 0x100) {
		mTemperature = (float) (rawTemp - 256) * 0.48;
	} else {
		mTemperature = (float) (rawTemp) * 0.48;
	}

	return true;
}

bool max9611ReadCSAOutputValue(void) {
	uint8_t rawData[2];
	uint16_t rawCSAVal = 0;
	if (!max9611Read(CSA_DATA_BYTE_MSB_ADRR, rawData, 2))
		return false;
	rawCSAVal = get12BitData(rawData[0], rawData[1]);
	//mRawInt = rawCSAVal;
	if (rawCSAVal <= csaCurrentValueOffset)
		mCurrentSenseAmplifierOutput = 0; // (float)(rawCSAVal-csaCurrentValueOffset)*(0.269);
	else
		mCurrentSenseAmplifierOutput = (float) (rawCSAVal) * (0.269);

	return true;
}

const float max9611GetTemp(void) {
	return mTemperature;
}

const float max9611GetCSAOutput(void) {
	return mCurrentSenseAmplifierOutput;
}

uint16_t max9611ReadControl(void) {
	uint8_t rawData[2];
	uint16_t rawTemp = 0;
	max9611Read(CONTROL_REGISTER_1_ADRR, rawData, 2);
	rawTemp = (rawData[0] << 8) | rawData[1];
	return rawTemp;
}

uint16_t max9611ReadRsValue(void) {
	uint8_t rawData[2];
	uint16_t rawTemp = 0;
	max9611Read(RS_DATA_BYTE_MSB_ADRR, rawData, 2);
	rawTemp = get12BitData(rawData[0], rawData[1]);
	return rawTemp;
}

uint16_t max9611ReadOutValue(void) {
	uint8_t rawData[2];
	uint16_t rawTemp = 0;
	max9611Read(OUT_DATA_BYTE_MSB_ADRR, rawData, 2);
	rawTemp = get12BitData(rawData[0], rawData[1]);
	return rawTemp;
}

