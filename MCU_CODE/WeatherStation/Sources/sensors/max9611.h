/*
 max9611.h

 Created on: 10 lis 2014
 Author: lukasz

 @file MAX9611.h

 @brief MAX9611 High-Side, Current-Sense Amplifiers with
 12-Bit ADC and Op Amp/Comparator- Breakout I2C Library

 @Author lukasz uszko(luszko@op.pl)

 Tested on FRDM-KL46Z and FRDM-KL25Z

 Copyright (c) 2014 luszko
 Released under the MIT License (see http://mbed.org/license/mit)

 Documentation regarding the MAX9611 might be found here:
 http://datasheets.maximintegrated.com/en/ds/MAX9611-MAX9612.pdf
 */

#ifndef MAX9611_H_
#define MAX9611_H_

#include "i2c/i2c.h"

#define MAX9611_I2C_ADDRESS 0x70//(0xE1)   //A0 and A1 PIN are connected to GND , Write address 0xE0, Read Address 0xE1

/**********protected methods********************************/



/**********public methods********************************/

/** Create an MAX9611 instance
 * @param LDD_TDeviceData* i2cHandlePtr
 * @param I2C_MODULE i2cModule
 * @param address: I2C slave address
 * @returns   true on success,
 *            false on error
 */
bool max9611Init(LDD_TDeviceData* i2cHandlePtr, I2C_MODULE i2cModule
		/*int address*/);

/** Read temperature from the MAX9611.
 * @param none
 * @returns
 *   1 on success,
 *   0 on error
 */
bool max9611ReadTemp(void);

/** Get temperature from the last measurement
 *
 * @returns
 *   temperature (C)
 */
inline const float max9611GetTemp(void);

/** Read CSA output value from the MAX9611.
 * @param none
 * @returns
 *   1 on success,
 *   0 on error
 */
bool max9611ReadCSAOutputValue(void);

/** Get value of CSA output from the last measurement
 *
 * @returns
 *   Current Value [A]
 */
inline const float max9611GetCSAOutput(void) ;

//DEBUG
uint16_t mRawInt;

uint16_t max9611ReadControl(void);
uint16_t max9611ReadRsValue(void);
uint16_t max9611ReadOutValue(void);

#endif /* MAX9611_H_ */
