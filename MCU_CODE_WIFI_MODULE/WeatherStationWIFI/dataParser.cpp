/*
 * dataParser.cpp
 *
 *  Created on: 4 sie 2015
 *      Author: lukasz
 */

#include "dataParser.h"



DataParser::DataParser(const char* data){

	if(data!=NULL &&strlen(data)<256)
		rootJson= aJson.parse((char*)data);

};


bool DataParser::validateData(DataTypes type){


	if(type>=eMaxNrOfTypes|| !rootJson)
		return false;

	aJsonObject* temp=  aJson.getObjectItem(rootJson,dataDescriptors[type]);
	if(temp)
		return true;
	return false;

};


