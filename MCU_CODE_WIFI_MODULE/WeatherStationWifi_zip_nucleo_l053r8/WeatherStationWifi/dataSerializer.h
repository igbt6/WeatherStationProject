/*
 * dataSerializer.h
 *
 *  Created on: 14 sie 2015
 *      Author: lukasz
 */

#ifndef DATASERIALIZER_H_
#define DATASERIALIZER_H_
#include "mbed.h"
#include "dataParser.h"
#include <string>



class DataSerializer{


private:
MbedJSONValue jsonData;
string jsonDataPacket;

public:
	DataSerializer();
	~DataSerializer();
	bool serializeData(DataParser* dataToBeParsed);
	string& getJson(void);

};






#endif /* DATASERIALIZER_H_ */

