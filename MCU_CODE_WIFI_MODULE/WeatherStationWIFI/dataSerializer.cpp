/*
 * dataSerializer.cpp
 *
 *  Created on: 14 sie 2015
 *      Author: lukasz
 */

#include "dataSerializer.h"
DataSerializer::DataSerializer() :
		aJsonModel() {

};

DataSerializer::~DataSerializer() {
	if(jsonDataPacket!=NULL)
		aJsonModel.deleteItem(jsonDataPacket);
};

bool DataSerializer::serializeData(DataParser* dataToBeParsed) {


	if(jsonDataPacket==NULL)
		jsonDataPacket = aJsonModel.createObject();
	if (jsonDataPacket == NULL||dataToBeParsed==NULL) {
		return false;
	}

	aJsonModel.addItemToObject(jsonDataPacket, "name", aJsonModel.createItem(
					"METEO"));
	aJsonObject* meteoData= aJsonModel.createObject();
	if (meteoData != NULL) {
		aJsonModel.addItemToObject(jsonDataPacket, "data", meteoData);
		aJsonModel.addNumberToObject(meteoData, "HUM", dataToBeParsed->hum->getDataValue());
		aJsonModel.addNumberToObject(meteoData, "TEMP", dataToBeParsed->temp->getDataValue());
		aJsonModel.addBooleanToObject(meteoData, "PRE", dataToBeParsed->press->getDataValue());
		aJsonModel.addNumberToObject(meteoData, "LHT", dataToBeParsed->light->getDataValue());
	}
	else return false;
	return true;
};


aJsonObject* DataSerializer::getJson(void){
	return jsonDataPacket;
}
