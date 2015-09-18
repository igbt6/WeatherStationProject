#include "mbed.h"
#include <string.h>
#include "main.h"
#include "RF22ReliableDatagram.h"
#include "dataParser.h"
 





#define SET 1
#define NOTSET 0








//MAIN APPLICATION##########################################


static void debugInit(void)
{   
    if(DEBUG_ENABLED)
    { 
        usbDebug =new Serial(USBTX, USBRX);
        usbDebug->baud(115200);
    }
}



// create singleton objects
//RFM23B
static RF22ReliableDatagram* rfm23b=NULL;
static DataParser *dataParser=NULL;


uint8_t data[] = "DATA_FROM_WIFI_MODULE";
uint8_t buf[RF22_MAX_MESSAGE_LEN];


static volatile uint32_t askStationFlag = SET;
//private functions

int main() {
    debugInit();
    DEBUG("HELLO SYSTEM!\r\n");
#ifdef RFM23D_ENABLED
    rfm23b =new RF22ReliableDatagram(SERVER_ADDRESS,RFM_PIN_nSEL, RFM_PIN_SDI ,RFM_PIN_SDO,RFM_PIN_SCLK,RFM_PIN_nIRQ,RFM_PIN_SDN);
    if(!rfm23b->init()) {
        DEBUG("rfm23b init failed\r\n");
        while(1);
    } else
        DEBUG("rfm23b init succes\r\n");
#endif
    while(1) {
    #ifdef RFM23D_ENABLED
        if (askStationFlag == SET) {
            // Wait for a message addressed to us from the client
            uint8_t len = sizeof(buf);
            uint8_t from;


            if (!rfm23b->sendtoWait(data, sizeof(data), STATION_ADDRESS)) 
            {
                DEBUG("sending request to station failed...");
            } 
            else 
            {
                if (rfm23b->recvfromAckTimeout(buf, &len, 1000, &from)) {
                    DEBUG("received data from Station : 0x%d", from);
                    //DEBUG("DATA %s", buf);
#endif
            


                dataParser= new DataParser((char*) buf);
                if(dataParser!=NULL){
                
                    for (int dataIdx = DataParser::eHumidity;
                            dataIdx < DataParser::eMaxNrOfTypes; ++dataIdx) {
    
                            if (dataIdx == DataParser::eHumidity) {
                                dataParser->createHumObj(
                                        dataParser->extractDataFromJsonObj<
                                                HUMIDITY_DATA_TYPE>(
                                                (DataParser::DataTypes) dataIdx));
                               //DEBUG("humidity: ");
                               DEBUG(" %.2f",(HUMIDITY_DATA_TYPE )dataParser->getHumObj()->getDataValue());
                                if(!(dataParser->getHumObj()->isDataValid())){
                                    dataParser->getHumObj()->setDataValue(INVALID_VALUE);
                                }
                            }
                     }
                     delete dataParser;
                     dataParser=NULL;
                }
   /*                      else if (dataIdx == DataParser::eTemperature) {
                            dataParser->createTempObj(
                                    dataParser->obtainDataObject<
                                            TEMPERATURE_DATA_TYPE>(
                                            (DataParser::DataTypes) dataIdx));
                           DEBUG("temp: ");
                           DEBUG(
                                    (TEMPERATURE_DATA_TYPE )dataParser->getTempObj()->getDataValue());
                            if(!(dataParser->getTempObj()->isDataValid())){
                                dataParser->getTempObj()->setDataValue(INVALID_VALUE);
                            }
                        }

                        else if (dataIdx == DataParser::ePressure) {
                            dataParser->createPressObj(
                                    dataParser->obtainDataObject<
                                            PRESSURE_DATA_TYPE>(
                                            (DataParser::DataTypes) dataIdx));
                           DEBUG("pressure: ");
                           DEBUG(
                                    (PRESSURE_DATA_TYPE )dataParser->getPressObj()->getDataValue());
                            if(!(dataParser->getPressObj()->isDataValid())){
                                dataParser->getPressObj()->setDataValue(INVALID_VALUE);
                            }
                        }

                        else if (dataIdx == DataParser::eLight) {
                            dataParser->createLightObj(
                                    dataParser->obtainDataObject<LIGHT_DATA_TYPE>(
                                            (DataParser::DataTypes) dataIdx));
                           DEBUG("light: ");
                           DEBUG(
                                    (LIGHT_DATA_TYPE )dataParser->getLightObj()->getDataValue());
                            if(!(dataParser->getLightObj()->isDataValid())){
                                dataParser->getLightObj()->setDataValue(INVALID_VALUE);
                            }
                        }

                    }
                DataSerializer *serializer = new DataSerializer();
                if(serializer->serializeData(dataParser)){
                    //delete dataParser;

                    //aJsonStream jsonStream(&Serial);
                    //jsonStream.printObject(serializer.getJson());

                }
                delete serializer;
                delete dataParser;
*/

            } 
            else 
            {
               DEBUG("No response from station, is station running?\n\n");
            }
            //askStationFlag = NOTSET;
        }
        }
        //wait_ms(3000);
    }//while
}//main
    
