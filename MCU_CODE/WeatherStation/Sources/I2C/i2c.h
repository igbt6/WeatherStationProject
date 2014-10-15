/*
 * i2c.h
 *
 *  Created on: 8 paü 2014
 *      Author: lukasz
 */

#ifndef I2C_H_
#define I2C_H_

#include "I2C1.h"
#include <stdbool.h>
typedef enum{

	I2C0_mod,
	I2C1_mod

}I2C_MODULE;

typedef struct{
 	 volatile bool dataReceivedFlag;  /*set TRUE by interrupt, when we have received a block of data*/
 	 volatile bool dataTransmitFlag;

}I2C_UsrData;



void i2cInit(I2C_MODULE module, uint8_t slaveAddr );

bool i2cRead(uint8_t slaveAddr,uint8_t regAddress, uint8_t *data,int length,I2C_MODULE module);


bool i2cWrite(uint8_t slaveAddr,uint8_t regAddress, uint8_t *data, int dataLength,I2C_MODULE module);



/* this method returns a pointer to initialized I2C protocol earlier */

LDD_TDeviceData* i2cGetI2CHandle(I2C_MODULE i2cModule);




#endif /* I2C_H_ */



