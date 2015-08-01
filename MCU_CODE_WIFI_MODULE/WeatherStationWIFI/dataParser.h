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

	enum DataTypes {

		Humidity,
		Temperature,
		Light,
		Pressure,
		GpsError,
		GpsTime,
		GpsDate,
		GpsPosition,
		BatteryCurrent,
		BatterVoltage,
		LightningDetection;
	}

	static const** dataDescriptors= {"HUM","TEM","LHT","PRE","GPS_E","GPS_T","GPS_D","GPS_P","BAT_C","BAT_V","LGT_D"};




};




#endif /* DATAPARSER_H_ */
