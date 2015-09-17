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

template<typename T> class DataType {

protected:
	virtual T getDataValue(void)=0;
	virtual void setDataValue(T val)=0;
	virtual char* getDataStrValue(void)=0;
	virtual bool isDataValid(void)=0;

};

template<typename T> class Humidity: public DataType<T> {

public:
	Humidity(T value, char* strValue = NULL) {
		this->value = value;
		this->strVal = strValue;
	}

	T getDataValue(void) {
		return value;
	}

	void setDataValue(T value) {
		this->value = value;
	}

	char* getDataStrValue(void) {
		return strVal;
	}

	bool isDataValid(void) {

		if (value >= 0 && value <= 100) {
			return true;
		}
		return false;
	}

private:
	T value;
	char* strVal;
};

template<typename T> class Light: public DataType<T> {

public:
	Light(T value, char* strValue = NULL) {
		this->value = value;
		this->strVal = strValue;
	}

	T getDataValue(void) {
		return value;
	}

	void setDataValue(T value) {
		this->value = value;
	}

	char* getDataStrValue(void) {
		return strVal;
	}

	bool isDataValid(void) {

		if (value >= 0 && value <= 500000) {
			return true;
		}
		return false;
	}

private:
	T value;
	char* strVal;
};

template<typename T> class Temperature: public DataType<T> {

public:
	Temperature(T value, char* strValue = NULL) {
		this->value = value;
		this->strVal = strValue;
	}

	T getDataValue(void) {
		return value;
	}

	void setDataValue(T value) {
		this->value = value;
	}

	char* getDataStrValue(void) {
		return strVal;
	}

	bool isDataValid(void) {

		if (value >= -70 && value <= 150) {
			return true;
		}
		return false;
	}

private:
	T value;
	char* strVal;
};

template<typename T> class Pressure: public DataType<T> {

public:
	Pressure(T value, char* strValue = NULL) {
		this->value = value;
		this->strVal = strValue;
	}

	T getDataValue(void) {
		return value;
	}

	void setDataValue(T value) {
		this->value = value;
	}

	char* getDataStrValue(void) {
		return strVal;
	}

	bool isDataValid(void) {

		if (value >= 500 && value <= 1500) {
			return true;
		}
		return false;
	}

private:
	T value;
	char* strVal;
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
	//template<typename Type> Type obtainDataObject(DataTypes type);

	//setters
	inline void createHumObj(HUMIDITY_DATA_TYPE val) {
		hum = new Humidity<HUMIDITY_DATA_TYPE>(val);
	}

	inline void createTempObj(TEMPERATURE_DATA_TYPE val) {
		temp = new Temperature<TEMPERATURE_DATA_TYPE>(val);
	}

	inline void createPressObj(PRESSURE_DATA_TYPE val) {
		press = new Pressure<PRESSURE_DATA_TYPE>(val);
	}

	inline void createLightObj(LIGHT_DATA_TYPE val) {
		light = new Light<LIGHT_DATA_TYPE>(val);
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
/*
template<typename Type> Type DataParser::obtainDataObject(DataTypes type) {

	if (type >= eMaxNrOfTypes || !rootJson)
		return (Type) -1;

	aJsonObject* temp = aJson.getObjectItem(rootJson, dataDescriptors[type]);
	switch (type) {

	case eHumidity:
	case eLight:
	case eTemperature:
	case ePressure:
		return (Type) (temp->valuefloat);
		break;

	default:
		return (Type) -1;
	
	}

}
*/
#endif /* DATAPARSER_H_ */

