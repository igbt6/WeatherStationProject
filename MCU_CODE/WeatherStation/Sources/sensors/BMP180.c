/*
 @file BMP180.cpp

 @brief Barometric Pressure and Temperature Sensor BMP180 Breakout I2C Library

 @Author spiridion (http://mailme.spiridion.net)

 Tested on LPC1768 and FRDM-KL25Z

 Copyright (c) 2014 spiridion
 Released under the MIT License (see http://mbed.org/license/mit)

 Documentation regarding the BMP180 can be found here:
 http://mbed.org/media/uploads/spiridion/bst-bmp180-ds000-09.pdf
 */

#include "BMP180.h"
#include <string.h>
#include <math.h>
#include "timeout/timeout.h"

// Uncomment to test the documentation algorithm against the documentation example 
// Result should be 699.64 hPa and 15°C
//#define BMP180_TEST_FORMULA

/*************private variables:*************/
int mOss;
float mTemperature;
float mPressure;
float mAltitude;
static I2C_MODULE mI2cModule;

short ac1, ac2, ac3;
unsigned short ac4, ac5, ac6;
short b1, b2;
short mb, mc, md;
long x1, x2, x3, b3, b5, b6;
unsigned long b4, b7;

/*************private methods:*************/

//transmit data to the sensor
static bool bmp180Write(uint8_t regAddress, uint8_t *data, int dataLength) {
	LDD_TError retValue;
	//uint8_t temp[dataLength + 1];
	//temp[0] = regAddress;
	//memcpy(&temp[1], data, dataLength);
	return i2cWrite(BMP180_I2C_ADDRESS, regAddress, data, dataLength,
			mI2cModule);
}

//read data from the sensor
static bool bmp180Read(uint8_t regAddress, uint8_t *data, int dataLength) {
	return i2cRead(BMP180_I2C_ADDRESS, regAddress, data, dataLength, mI2cModule);
}

static int bmp180SetConfiguration(float altitude, int overSamplingSetting) {
	uint8_t data[22];
	int errors = 0;

	mAltitude = altitude;
	mOss = overSamplingSetting;
	mTemperature = UNSET_BMP180_TEMPERATURE_VALUE;
	mPressure = UNSET_BMP180_PRESSURE_VALUE;

	// read calibration data
	data[0] = 0xAA;
	// errors = bmp180Write(m_addr, data, 1);  // set the eeprom pointer position to 0xAA
	errors += bmp180Read(data[0], data, 22); // read 11 x 16 bits at this position
	//wait_ms(10);
	//WAIT1_Waitms(10);
	timeoutSetTimeout(10);
	while (!timeoutIsTimeoutOccured())
		;

	// store calibration data for further calculus
	ac1 = data[0] << 8 | data[1];
	ac2 = data[2] << 8 | data[3];
	ac3 = data[4] << 8 | data[5];
	ac4 = data[6] << 8 | data[7];
	ac5 = data[8] << 8 | data[9];
	ac6 = data[10] << 8 | data[11];
	b1 = data[12] << 8 | data[13];
	b2 = data[14] << 8 | data[15];
	mb = data[16] << 8 | data[17];
	mc = data[18] << 8 | data[19];
	md = data[20] << 8 | data[21];

#ifdef BMP180_TEST_FORMULA
	ac1 = 408;
	ac2 = -72;
	ac3 = -14383;
	ac4 = 32741;
	ac5 = 32757;
	ac6 = 23153;
	b1 = 6190;
	b2 = 4;
	mb = -32768;
	mc = -8711;
	md = 2868;
	mOss = 0;
	errors = 0;
#endif // #ifdef BMP180_TEST_FORMULA	return errors ? 1 : 0;}
	/*************public methods:*************/
//Init method, modify values here;
// NOTIFY!!! - this function must be used before using other functions for the sensor
	void bmp180Init(LDD_TDeviceData* i2cHandlePtr, I2C_MODULE i2cModule) {
		if (i2cHandlePtr == NULL)
			while (1)
				;  //do something here. i2C has not been not initialized
		mAltitude = 0;
		mOss = BMP180_OSS_NORMAL;
		mI2cModule =i2cModule;
		mTemperature = UNSET_BMP180_TEMPERATURE_VALUE;
		mPressure = UNSET_BMP180_PRESSURE_VALUE;
		bmp180SetConfiguration(0.F, BMP180_OSS_NORMAL);
	}


	bool bmp180ReadData(void) {
		long t, p;

		if (!bmp180ReadRawTemperature(&t) || !bmp180ReadRawPressure(&p)) {
			mTemperature = UNSET_BMP180_TEMPERATURE_VALUE;
			mPressure = UNSET_BMP180_PRESSURE_VALUE;
			return false;
		}

		mTemperature = bmp180TrueTemperature(t);
		mPressure = bmp180TruePressure(p);
		return true;
	}


	int bmp180ReadRawTemperature(long* pUt) {
		int errors = 0;
		uint8_t data[2];

		// request temperature measurement
		data[0] = 0xF4;
		data[1] = 0x2E;
		errors = bmp180Write(data[0], &data[1], 1); // write 0XF2 into reg 0XF4

		// wait_ms(4.5F);
//	WAIT1_Waitms(5);
		timeoutSetTimeout(5);
		while (!timeoutIsTimeoutOccured())
			;

		// read raw temperature data
		data[0] = 0xF6;
		//errors += bmp180Write(data[0], data, 2); // set eeprom pointer position to 0XF6  //////////////////////////////////////////
		errors += bmp180Read(data[0], data, 2);  // get 16 bits at this position

#ifdef BMP180_TEST_FORMULA
		errors = 0;
#endif // #ifdef BMP180_TEST_FORMULA	if (errors<2)	return 0;		else
		*pUt = ((data[0] << 8) | data[1]);

#ifdef BMP180_TEST_FORMULA
		*pUt = 27898;
#endif // #ifdef BMP180_TEST_FORMULA	return 1;}
		int bmp180ReadRawPressure(long* pUp) {
			int errors = 0;
			char data[2];

// request pressure measurement
			data[0] = 0xF4;
			data[1] = 0x34 + (mOss << 6);
			errors = bmp180Write(data[0], &data[1], 1); // write 0x34 + (m_oss << 6) into reg 0XF4

			switch (mOss) {
			case BMP180_OSS_ULTRA_LOW_POWER: /*wait_ms(4.5);*/
				timeoutSetTimeout(5);
				while (!timeoutIsTimeoutOccured())
					;

				break;
			case BMP180_OSS_NORMAL: /*wait_ms(7.5);*/
				timeoutSetTimeout(8);
				while (!timeoutIsTimeoutOccured())
					;
				break;
			case BMP180_OSS_HIGH_RESOLUTION: /*wait_ms(13.5);*/
				timeoutSetTimeout(14);
				while (!timeoutIsTimeoutOccured())
					;
				break;
			case BMP180_OSS_ULTRA_HIGH_RESOLUTION: /*wait_ms(25.5);*/
				timeoutSetTimeout(26);
				while (!timeoutIsTimeoutOccured())
					;
				break;
			}

// read raw pressure data
			data[0] = 0xF6;
//  errors += m_i2c.write(m_addr, data, 1); // set eeprom pointer position to 0XF6
			errors += bmp180Read(data[0], data, 2); // get 16 bits at this position

#ifdef BMP180_TEST_FORMULA
			errors = 0;
#endif // #ifdef BMP180_TEST_FORMULA	if (errors<2)return 0;			else
			*pUp = (data[0] << 16 | data[1] << 8) >> (8 - mOss);
#ifdef BMP180_TEST_FORMULA
			*pUp = 23843;
#endif // #ifdef BMP180_TEST_FORMULA	return 1;}
			float bmp180TrueTemperature(long ut) {
				long t;

				// straight out from the documentation
				x1 = ((ut - ac6) * ac5) >> 15;
				x2 = ((long) mc << 11) / (x1 + md);
				b5 = x1 + x2;
				t = (b5 + 8) >> 4;

				// convert to celcius
				return t / 10.F;
			}

			float bmp180TruePressure(long up) {
				long p;


				b6 = b5 - 4000;
				x1 = (b2 * (b6 * b6 >> 12)) >> 11;
				x2 = ac2 * b6 >> 11;
				x3 = x1 + x2;
				b3 = (((ac1 * 4 + x3) << mOss) + 2) >> 2;
				x1 = (ac3 * b6) >> 13;
				x2 = (b1 * ((b6 * b6) >> 12)) >> 16; // where is my GOD now : D !!!!!!
				x3 = ((x1 + x2) + 2) >> 2;
				b4 = ac4 * (unsigned long) (x3 + 32768) >> 15;
				b7 = ((unsigned long) up - b3) * (50000 >> mOss);
				if (b7 < 0x80000000)
					p = (b7 << 1) / b4;
				else
					p = (b7 / b4) << 1;
				x1 = (p >> 8) * (p >> 8);
				x1 = (x1 * 3038) >> 16;
				x2 = (-7357 * p) >> 16;
				p = p + ((x1 + x2 + 3791) >> 4);


				// convert to hPa and, if altitude has been initialized, to sea level pressure
				if (mAltitude == 0.F)
					return p / 100.F;
				else
					return p
							/ (100.F
									* pow((1.F - mAltitude / 44330.0L), 5.255L));
			}

			/** Get temperature from a previous measurement
			 *
			 * @returns
			 *   temperature (C)
			 */
			float bmp180GetTemperature() {
				return mTemperature;
			}

			/** Get pressure from a previous measurement
			 *
			 * @returns
			 *   pressure (hPa)
			 */
			float bmp180GetPressure() {
				return mPressure;
			}
