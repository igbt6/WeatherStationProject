/*
 * dataSerializer.cpp
 *
 *  Created on: 14 sie 2015
 *      Author: lukasz
 */

#include "dataSerializer.h"
DataSerializer::DataSerializer() :
		aJsonModel() {

}
;

bool DataSerializer::serializeData(DataParser* dataToBeParsed) {

	if(jsonDataPacket==NULL)
		jsonDataPacket = aJsonModel.createObject();
	if (jsonDataPacket != NULL) {
		return false;
	}

	aJsonModel.addItemToObject(jsonDataPacket, "name", aJsonModel.createItem(
					"METEO"));
	aJsonObject* fmt= aJsonModel.createObject();
	if (fmt != NULL) {
		aJsonModel.addItemToObject(jsonDataPacket, "D", fmt);
		//aJsonModel.addStringToObject(fmt, "type", "TEST");
		aJsonModel.addNumberToObject(fmt, "HUM", dataToBeParsed->hum->getDataValue());
		aJsonModel.addNumberToObject(fmt, "TEMP", dataToBeParsed->temp->getDataValue());
		aJsonModel.addBooleanToObject(fmt, "PRE", dataToBeParsed->press->getDataValue());
		aJsonModel.addNumberToObject(fmt, "LHT", dataToBeParsed->light->getDataValue());
	}
	return true;
};
