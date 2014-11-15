/*
  @file AS3935.h
  
  @brief AS3935 Franklin Lightning Sensor
         Breakout I2C Library      

  @Author lukasz uszko(luszko@op.pl)

  Tested on FRDM-KL46Z and FRDM-KL25Z
  
  Copyright (c) 2014 lukasz uszko
  Released under the MIT License (see http://mbed.org/license/mit)

  Documentation regarding the MAX9611 might be found here: 
  http://www.ams.com/eng/Products/Lightning-Sensor
*/


#ifndef _AS3935_H
#define _AS3935_H

#include "mbed.h"


#define AS3935_I2C_ADDRESS 0x03<<1



// register access macros - register address, bitmask
#define AS3935_AFE_GB       0x00, 0x3E
#define AS3935_PWD          0x00, 0x01
#define AS3935_NF_LEV       0x01, 0x70
#define AS3935_WDTH         0x01, 0x0F
#define AS3935_CL_STAT      0x02, 0x40
#define AS3935_MIN_NUM_LIGH 0x02, 0x30
#define AS3935_SREJ         0x02, 0x0F
#define AS3935_LCO_FDIV     0x03, 0xC0
#define AS3935_MASK_DIST    0x03, 0x20
#define AS3935_INT          0x03, 0x0F
#define AS3935_DISTANCE     0x07, 0x3F
#define AS3935_DISP_LCO     0x08, 0x80
#define AS3935_DISP_SRCO    0x08, 0x40
#define AS3935_DISP_TRCO    0x08, 0x20
#define AS3935_TUN_CAP      0x08, 0x0F

// other constants
#define AS3935_AFE_INDOOR   0x12
#define AS3935_AFE_OUTDOOR  0x0E


class AS3935 {
    
    
    
    /**********public methods********************************/
    public:

    /** Create an AS3935 instance
     * @param sda pin 
     * @param scl pin 
     * @param PinName IRQ Pin
     * @param i2c bus frequency [Hz]
     * @param address: I2C slave address  
     */
     AS3935(PinName sda, PinName scl, PinName irqPin,int i2cFrequencyHz,uint8_t address); 
     
     
     bool initAS3935(void);   
        
        
        /**********private members and methods********************************/       
    private: 
     
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
    
    
    /** Write data into the given byte
     * @param register Address
     * @param dataBitMask in register
     * @param dat to be written
     * @returns
     *   1 on success,
     *   0 on error
     */
    bool writeReg(uint8_t regAddress, uint8_t dataBitMask, uint8_t data);
    
    /** Helper method for writeReg and readReg methods
     * @param uint8_t dataBitMask
     * @returns  ShiftValue
     */
    uint8_t getShiftValue(uint8_t dataBitMask);
    
    
    /** Read data from the given byte
     * @param register Address
     * @param dataBitMask in register
     * @param dat to be read
     * @returns
     *   1 on success,
     *   0 on error
     */
    bool readReg(uint8_t regAddress, uint8_t dataBitMask, uint8_t *data);
    
    
    I2C mI2c;   
    uint8_t mI2cAddr;
    
        
        
        
        
        
};









#endif