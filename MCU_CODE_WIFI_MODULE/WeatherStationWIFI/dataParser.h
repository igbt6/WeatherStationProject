/*
 * dataParser.h
 *
 *  Created on: 4 sie 2015
 *      Author: lukasz
 */

#ifndef DATAPARSER_H_
#define DATAPARSER_H_




class DataParser{



private:

	typedef enum  {

		Humidity,
		Temperature,
		Light,
		Pressure,
		GpsError,
		GpsTime,
		GpsDate,
		GpsPosition,
		BatteryData, //current, voltage
		LightningDetection,
		MaxNrOfTypes;
	}DataTypes;

	static const** dataDescriptors= {"HUM","TEM","LHT","PRE","GPS_E","GPS_T","GPS_D","GPS_P","BAT","LGT_D"};


	aJsonObject* rootJson;
public:

	DataParser(char* data);
	bool (*validateData)(DataTypes type)



};




#endif /* DATAPARSER_H_ */
