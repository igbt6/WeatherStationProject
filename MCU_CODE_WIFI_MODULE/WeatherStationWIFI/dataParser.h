/*
 * dataParser.h
 *
 *  Created on: 4 sie 2015
 *      Author: lukasz
 */

#ifndef DATAPARSER_H_
#define DATAPARSER_H_

#include "aJson/aJSON.h"




static const char* dataDescriptors[]= {"HUM","TEM","LHT","PRE","GPS_E","GPS_T","GPS_D","GPS_P","BAT","LGT_D"};



template <typename T> class DataType {



protected:
	virtual T getDataValue(void)=0;
	virtual char* getDataStrValue(void)=0;

};



template <typename T>class Humidity:public DataType<T>{

public:
	Humidity(T value,char* strValue=NULL){
		this->value=value;
		this->strVal= strValue;
	}

	T getDataValue(void){
		return value;
	}
	char* getDataStrValue(void){
		return strVal;
	}


private:
	T value;
	char* strVal;
};


template <typename T>class Light:public DataType<T>{

public:
	Light(T value,char* strValue=NULL){
		this->value=value;
		this->strVal= strValue;
	}

protected:
	T getDataValue(void){
		return value;
	}
	char* getDataStrValue(void){
		return strVal;
	}


private:
	T value;
	char* strVal;
};


template <typename T>class Temperature:public DataType<T>{

public:
	Temperature(T value,char* strValue=NULL){
		this->value=value;
		this->strVal= strValue;
	}

protected:
	T getDataValue(void){
		return value;
	}
	char* getDataStrValue(void){
		return strVal;
	}


private:
	T value;
	char* strVal;
};


template <typename T>class Pressure:public DataType<T>{

public:
	Pressure(T value,char* strValue=NULL){
		this->value=value;
		this->strVal= strValue;
	}

protected:
	T getDataValue(void){
		return value;
	}
	char* getDataStrValue(void){
		return strVal;
	}

private:
	T value;
	char* strVal;
};


class DataParser{


public:
	typedef enum  {

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
		}DataTypes;

	DataParser(const char* data);
	bool validateData(DataTypes type);
	template <typename Type> Type obtainDataObject(DataTypes type);


	//setters
	inline void createHumObj(Humidity<double>* humObj){	if(humObj!= NULL)
		hum= humObj;}
	inline Humidity<double>* getHumObj(){
		return hum;
	}


private:

	Humidity<double>* hum;
	Light<double>* light;
	Temperature<double>* temp;
	Pressure<double>*press;
	aJsonObject* rootJson;

};





#endif /* DATAPARSER_H_ */
