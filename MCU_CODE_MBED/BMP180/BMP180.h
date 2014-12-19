/*
  @file BMP180.h

  @brief Barometric Pressure and Temperature Sensor BMP180 Breakout I2C Library     

  @Author lukasz uszko(luszko@op.pl) based on spiridion's (http://mailme.spiridion.net) BMP180 Breakout I2C Library  library
   

  Tested on FRDM-KL46Z and FRDM-KL25Z
  
  Copyright (c) 2014 lukasz uszko
  Released under the MIT License (see http://mbed.org/license/mit)

  Documentation regarding the BMP180  might be found here: 
  https://www.bosch-sensortec.com/en/homepage/products_3/environmental_sensors_1/bmp180_1/bmp180
*/


#ifndef BMP180_H
#define BMP180_H

#include "mbed.h"

///  default address is 0xEF
#define BMP180_I2C_ADDRESS 0xEF

// Oversampling settings
#define BMP180_OSS_ULTRA_LOW_POWER 0        // 1 sample  and  4.5ms for conversion
#define BMP180_OSS_NORMAL          1        // 2 samples and  7.5ms for conversion
#define BMP180_OSS_HIGH_RESOLUTION 2        // 4 samples and 13.5ms for conversion
#define BMP180_OSS_ULTRA_HIGH_RESOLUTION 3  // 8 samples and 25.5ms for conversion

#define UNSET_BMP180_PRESSURE_VALUE -999
#define UNSET_BMP180_TEMPERATURE_VALUE -999 

/** BMP180 class.
 *  Read Pressure and temperature from the BMP180 Breakout I2C sensor
 *
 * How to use:
 * @code
 * #include "mbed.h"
 * #include "BMP180.h"
 * 
 * //for FRDM_46KLZ //I2C1
 * #define BMP_180_PIN_SDA PTE0   
 * #define BMP_180_PIN_SCL PTE1

 *
 * int main()
 * {
 *     BMP180 bmp180(BMP_180_PIN_SDA, BMP_180_PIN_SCL);
 *     float pressure, temperature
 *
 *     while(1)
 *     {
 *         if (bmp180.readData())
 *             printf("Pressure(hPa): %8.2f \t Temperature(C): %8.2f\n", bmp180.getPressure(), bmp180.getTemperature());
 *         wait(1);
 *     }
 * }
 * @endcode
 */
class BMP180
{

public:

    /** Create a BMP180 instance
     * @param sda pin
     * @param scl pin
     * @param address: I2C slave address
     */
    BMP180(PinName sda, PinName scl, int address = BMP180_I2C_ADDRESS);

    /** Create a BMP180 instance
     * @param i2c object
     * @param address: I2C slave address
     */
    BMP180(I2C& i2c, int address = BMP180_I2C_ADDRESS);

    /** Initialization: set member values and read BMP180 calibration parameters
     * @param altitude (in meter)
     * @param overSamplingSetting
     */
    int setConfiguration(float altitude = 0.F, int overSamplingSetting = BMP180_OSS_NORMAL);

    /** Read pressure and temperature from the BMP180.
     * @param pressure (hPa)
     * @param temperature (C)
     * @returns
     *   1 on success,
     *   0 on error
     */
    bool readData(void);

    /** Get temperature from a previous measurement
     *
     * @returns
     *   temperature (C)
     */
    float getTemperature();

    /** Get pressure from a previous measurement
     *
     * @returns
     *   pressure (hPa)
     */
    float getPressure();

protected:


    /** Write data to the given register
    *
    * @returns
    *   1 on success,
    *   0 on error
    */
    bool write(uint8_t regAddress, uint8_t* data,int dataLength);

    /** Write data to the given register
     * @param register Address
     * @param data to read
     * @param length of data to read
     * @returns
     *   1 on success,
     *   0 on error
     */
    bool read(uint8_t regAddress, uint8_t* data,int length);




    /** Perform temperature measurement
     *
     * @returns
     *   temperature (C)
     */
    int readRawTemperature(long* pUt);

    /** Perform pressure measurement
     *
     * @returns
     *   temperature (C)
     */
    int readRawPressure(long* pUp);

    /** Calculation of the temperature from the digital output
     */
    float trueTemperature(long ut);

    /** Calculation of the pressure from the digital output
     */
    float truePressure(long up);

    int mOss;
    float mTemperature;
    float mPressure;
    float mAltitude;

    I2C mI2c;
    int mI2cAddr;
    char mData[4];

    short ac1, ac2, ac3;
    unsigned short ac4, ac5, ac6;
    short b1, b2;
    short mb, mc, md;
    long x1, x2, x3, b3, b5, b6;
    unsigned long b4, b7;

};

#endif