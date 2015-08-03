/*
 * dataParser.cpp
 *
 *  Created on: 4 sie 2015
 *      Author: lukasz
 */




DataParser::DataParser(const char* data){

	if(data!=NULL &&strlen(data)<256)
		rootJson= aJson.parse(data);


}
