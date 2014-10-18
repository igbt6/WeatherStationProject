/*
 @file BMP180.h

 @brief Barometric Pressure and Temperature Sensor BMP180 Breakout I2C Library

 @Author lukasz uszko
 */

#ifndef __BMP180_H
#define __BMP180_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c/i2c.h"

///  default address is 0xEF 
#define BMP180_I2C_ADDRESS 0x77

// Oversampling settings
#define BMP180_OSS_ULTRA_LOW_POWER 0        // 1 sample  and  4.5ms for conversion#define BMP180_OSS_NORMAL          1        // 2 samples and  7.5ms for conversion#define BMP180_OSS_HIGH_RESOLUTION 2        // 4 samples and 13.5ms for conversion#define BMP180_OSS_ULTRA_HIGH_RESOLUTION 3  // 8 samples and 25.5ms for conversion
#define UNSET_BMP180_PRESSURE_VALUE 0.F
#define UNSET_BMP180_TEMPERATURE_VALUE -273.15F // absolute zero
/** Init method of bmp180 sensor
 */
void bmp180Init(LDD_TDeviceData* i2cHandlePtr,I2C_MODULE i2cModule);
/** Initialization: set member values and read BMP180 calibration parameters
 * @param altitude (in meter)
 * @param overSamplingSetting
 */
//int Initialize(float altitude = 0.F,
//		int overSamplingSetting = BMP180_OSS_NORMAL);

/** Read pressure and temperature from the BMP180.
 * @returns
 *   1 on success,
 *   0 on error
 */
bool bmp180ReadData(void);

/** Get temperature from a previous measurement
 *
 * @returns
 *   temperature (C)
 */
float bmp180GetTemperature();


/** Get pressure from a previous measurement
 *
 * @returns
 *   pressure (hPa)
 */
float bmp180GetPressure();

//protected:

/** Perform temperature measurement
 *
 * @returns
 *   temperature (C)
 */
int bmp180ReadRawTemperature(long* pUt);

/** Perform pressure measurement
 *
 * @returns
 *   temperature (C)
 */
int bmp180ReadRawPressure(long* pUp);

/** Calculation of the temperature from the digital output
 */
float bmp180TrueTemperature(long ut);

/** Calculation of the pressure from the digital output
 */
float bmp180TruePressure(long up);



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
