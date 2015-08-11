/*
 * dataSerializer.h
 *
 *  Created on: 14 sie 2015
 *      Author: lukasz
 */

#ifndef DATASERIALIZER_H_
#define DATASERIALIZER_H_

#include "dataParser.h"
#include "aJson/aJSON.h"




class DataSerializer{





private:
aJsonObject* jsonDataPacket;
aJsonClass aJsonModel;


public:
	DataSerializer();
	bool serializeData(DataParser* dataToBeParsed);

};






#endif /* DATASERIALIZER_H_ */
