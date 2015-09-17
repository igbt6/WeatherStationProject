/*
 * dataParser.cpp
 *
 *  Created on: 4 sie 2015
 *      Author: lukasz
 */

#include "dataParser.h"



DataParser::DataParser(const char* data):rootJson(){

	if(data!=NULL &&strlen(data)<256)
		parse(rootJson,data);

};


 DataParser::~DataParser(){

	//if(rootJson!=NULL){
	//	aJson.deleteItem(rootJson);
	//}

	if(hum)
		delete hum;
	if(light)
		delete light;
	if(press)
		delete press;
	if(temp)
		delete temp;
};

bool DataParser::validateData(DataTypes type){


	if(type>=eMaxNrOfTypes/*|| rootJson*/)
		return false;

	//aJsonObject* temp=  aJson.getObjectItem(rootJson,dataDescriptors[type]);
	if(temp)
		return true;
	return false;

};



