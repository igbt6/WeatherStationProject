/*
 @file adt7410.h

 @brief Temperature Sensor ADT7410 Breakout I2C Library

 @Author lukasz uszko(luszko@op.pl)

 Tested on FRDM-KL46Z

 Copyright (c) 2014 luszko
 Released under the MIT License (see http://mbed.org/license/mit)

 Documentation regarding the ADT7410 can be found here:
 http://www.analog.com/static/imported-files/data_sheets/ADT7410.pdf
 */

#ifndef __adt7410_H
#define __adt7410_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c/i2c.h"

#define ADT7410_I2C_ADDRESS 0x48/*0x97*/   //A0 and A1 PIN are conected to GND#define ADT7410_2_I2C_ADDRESS 0x90   //A0 and A1 PIN are conected to GND
typedef enum {
	_13_BIT = 0, _16_BIT = 1
} CONF_RESOLUTION;

void adt7410Init(LDD_TDeviceData* i2cHandlePtr,I2C_MODULE i2cModule);
/** Read temperature from the ADT7410.
 * @param temperature (C)
 * @returns
 *   1 on success,
 *   0 on error
 */
bool adt7410ReadTemp();

int adt7410GetIdNumber(void);

/** Set resolution of read data
 *
 *
 */
int adt7410SetResolution(CONF_RESOLUTION res);

/** Get temperature from a previous measurement
 *
 * @returns
 *   temperature (C)
 */
float adt7410GetTemperature(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
