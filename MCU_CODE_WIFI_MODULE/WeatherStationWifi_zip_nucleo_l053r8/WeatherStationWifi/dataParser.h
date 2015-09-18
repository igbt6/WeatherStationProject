/*
 * dataParser.h
 *
 *  Created on: 4 sie 2015
 *      Author: lukasz
 */

#ifndef DATAPARSER_H_
#define DATAPARSER_H_

#include "MbedJSONValue.h"


typedef double HUMIDITY_DATA_TYPE;
typedef double TEMPERATURE_DATA_TYPE;
typedef double LIGHT_DATA_TYPE;
typedef double PRESSURE_DATA_TYPE;

#define INVALID_VALUE 0xFFFFFFFF

static const char* dataDescriptors[] = { "HUM", "TEM", "LHT", "PRE", "GPS_E",
		"GPS_T", "GPS_D", "GPS_P", "BAT", "LGT_D" };

template<typename T> class MeteoDataType {

public:
	
	MeteoDataType(){
		this->value = 0;
		this->strVal = " ";
	}
	
	MeteoDataType(T value, const char* strValue =" "){
		this->value = value;
		this->strVal = strValue;
	}

		T getDataValue(void) {
		return value;
	}

	void setDataValue(T value) {
		this->value = value;
	}

protected:
	


	std::string & getDataStrValue(void) {
		return strVal;
	}
	
	virtual bool isDataValid(void)=0;

private: 
	T value;
	std::string  strVal;

};

template<typename T> class Humidity: public MeteoDataType<T> {

public:

	Humidity(T value, const char* strValue =" "):MeteoDataType<T>(value,strValue) {
	}
	virtual bool isDataValid(void) {
		if (this->getDataValue()>= 0 &&this->getDataValue() <= 100) {
			return true;
		}
		return false;
	}
};

template<typename T> class Light: public MeteoDataType<T> {

public:

	Light(T value, const char* strValue =" "):MeteoDataType<T>(value,strValue) {
	}

	virtual bool isDataValid(void) {

		if (this->getDataValue()>= 0 && this->getDataValue() <= 500000) {
			return true;
		}
		return false;
	}
};

template<typename T> class Temperature: public MeteoDataType<T>{

public:

	Temperature(T value, const char* strValue =" "):MeteoDataType<T>(value,strValue) {
	}

	virtual bool isDataValid(void) {

		if (this->getDataValue()>= -70 && this->getDataValue() <= 150) {
			return true;
		}
		return false;
	}
};

template<typename T> class Pressure: public MeteoDataType<T> {

public:
	Pressure(T value, const char* strValue =" "):MeteoDataType<T>(value,strValue) {
	}

	virtual bool isDataValid(void) {

		if (this->getDataValue() >= 500 && this->getDataValue()<= 1500) {
			return true;
		}
		return false;
	}
};



class DataParser {

	friend class DataSerializer;

public:

	typedef enum {

		eHumidity,
		eTemperature,
		eLight,
		ePressure,
		eGpsError,
		eGpsTime,
		eGpsDate,
		eGpsPosition,
		eBatteryData, //current, voltage
		eLightningDetection,
		eMaxNrOfTypes
	} DataTypes;

	DataParser(const char* data);
	virtual ~DataParser();
	bool validateData(DataTypes type);
	template<typename Type> Type extractDataFromJsonObj(DataTypes type);

	//setters
	template<typename T> MeteoDataType<T>* createHumObj(T val) {
		MeteoDataType<T>* ptr = new Humidity<T>(val);
		hum =(Humidity<HUMIDITY_DATA_TYPE>*)ptr;
		return ptr;
	}

	template<typename T> MeteoDataType<T>* createTempObj(T val) {
		MeteoDataType<T>* ptr = new Temperature<T>(val);
		return ptr;
	}

	template<typename T> MeteoDataType<T>* createPressObj(T val) {
		MeteoDataType<T>* ptr = new Pressure<T>(val);
		return ptr;
	}

	template<typename T> MeteoDataType<T>*  createLightObj(T val) {
		MeteoDataType<T>* ptr =  = new Light<T>(val);
		return ptr;
	}
	//getters
	inline Humidity<HUMIDITY_DATA_TYPE>* getHumObj() {
		return hum;
	}

	inline Temperature<TEMPERATURE_DATA_TYPE>* getTempObj() {
		return temp;
	}

	inline Pressure<PRESSURE_DATA_TYPE>* getPressObj() {
		return press;
	}

	inline Light<LIGHT_DATA_TYPE>* getLightObj() {
		return light;
	}

protected:

private:

	Humidity<HUMIDITY_DATA_TYPE>* hum;
	Light<LIGHT_DATA_TYPE>* light;
	Temperature<TEMPERATURE_DATA_TYPE>* temp;
	Pressure<PRESSURE_DATA_TYPE>*press;
	MbedJSONValue rootJson;

};

template<typename Type> Type DataParser::extractDataFromJsonObj(DataTypes type) {
	Type dataVal;
	if (type >= eMaxNrOfTypes)
		return (Type) -1;
	dataVal = rootJson[dataDescriptors[type]].get<Type>();
	switch (type) {

	case eHumidity:
	case eLight:
	case eTemperature:
	case ePressure:
		return (Type) (dataVal);
		break;

	default:
		return (Type) -1;
	
	}
}
#endif /* DATAPARSER_H_ */

