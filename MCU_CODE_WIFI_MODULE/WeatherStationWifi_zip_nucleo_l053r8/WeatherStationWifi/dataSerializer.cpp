/*
 * dataSerializer.cpp
 *
 *  Created on: 14 sie 2015
 *      Author: lukasz
 */

#include "dataSerializer.h"
DataSerializer::DataSerializer() :jsonData() {

};

DataSerializer::~DataSerializer() {
	//if(jsonDataPacket!=NULL)
	//	aJsonModel.deleteItem(jsonDataPacket);
};

bool DataSerializer::serializeData(DataParser* dataToBeParsed) {

	if (dataToBeParsed==NULL) {
		return false;
	}
	//jsonData["HUM"]=dataToBeParsed->hum->getDataValue();
	//jsonData["TEMP"]= dataToBeParsed->temp->getDataValue();
	//jsonData["PRE"]=dataToBeParsed->press->getDataValue();
	//jsonData["LHT"]=dataToBeParsed->light->getDataValue();
	jsonDataPacket =jsonData.serialize();

	return true;
};


string& DataSerializer::getJson(void){
	return jsonDataPacket;
}

