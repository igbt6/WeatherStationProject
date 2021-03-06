#include "Energia.h"
#include "CC3000/TCPclient.h"
#include "CC3000/TCPserver.h"
#include "CC3000/WiFi.h"
#include "CC3000/WiFiUdp.h"
#include "RF22/RF22ReliableDatagram.h"
#include <driverlib/timer.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>
#include <driverlib/rom.h>
#include <driverlib/rom_map.h>
#include <inc/hw_ints.h>
#include <string.h>
#include "aJson/aJSON.h"
#include "dataParser.h"
#include "dataSerializer.h"

void setup();
void loop();

#define STATION_ADDRESS 1
#define SERVER_ADDRESS 2
#define RFM23B_SLAVE_SELECT_PIN  PE_1
#define RFM23B_SHUTDOWN_PIN PE_2
#define RFM23B_INTERRUPT_PIN PE_3

#define SET 1
#define NOTSET 0

#define CC3000_ENABLEDx
#define RFM23D_ENABLED

#define DEBUG_ENABLED true
#define INIT_DEBUG() (DEBUG_ENABLED? Serial.begin(115200): (void)0)
#define PRINT_DEBUG(data) do{if(DEBUG_ENABLED) Serial.print(data);} while(0)

/*////////////////////////////////////////RFM23B MODULE TESTS ///////////////////////////////////////////////////////
 static volatile uint32_t askStationFlag = 0;
 //private functions

 static void initTimer0(void) {
 SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
 TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC_UP);
 TimerPrescaleSet(TIMER0_BASE, TIMER_B, 255);
 // Set the Timer0B load value to 1ms.
 TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet() / 1000000);
 // Enable processor interrupts.
 IntMasterEnable();
 // Configure the Timer0B interrupt for timer timeout.
 TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT)
 // Enable the Timer0B interrupt on the processor (NVIC).
 IntEnable(INT_TIMER0B);
 // Enable Timer0B.
 TimerEnable(TIMER0_BASE, TIMER_B);
 // Loop forever while the Timer0B runs.
 }

 // create singleton objects
 RF22ReliableDatagram rfm23b(SERVER_ADDRESS, RFM23B_SLAVE_SELECT_PIN,
 RFM23B_SHUTDOWN_PIN, RFM23B_INTERRUPT_PIN);

 uint8_t data[] = "DATA";
 // Dont put this on the stack:
 uint8_t buf[30]; //RF22_MAX_MESSAGE_LEN

 void setup() {
 //  Run at system clock at 80MHz
 SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
 SYSCTL_XTAL_16MHZ); //in wiring.c clock 80MHZ enabled
 Serial.begin(115200);
 if (!rfm23b.init()) {
 Serial.println("RF22 init failed");
 while (1)
 ;
 }
 // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
 initTimer0();
 }

 void loop() {
 while (1) {
 if (askStationFlag == SET) {
 // Wait for a message addressed to us from the client
 uint8_t len = sizeof(buf);
 uint8_t from;
 // Turn off Timer0B interrupt.
 TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
 // Clear any pending interrupt flag.
 TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
 IntDisable(INT_TIMER0B);
 if (!rfm23b.sendtoWait(data, sizeof(data), STATION_ADDRESS)) {
 Serial.print("sending request to station failed...");
 } else {
 if (rfm23b.recvfromAckTimeout(buf, &len, 1000, &from)) {
 Serial.print("got data from Station : 0x");
 Serial.print(from, HEX);
 Serial.print(": ");
 Serial.print((char*) buf);
 Serial.print("\r\n");

 } else {
 Serial.print(
 "No response from station, is station running?\n\n");
 }
 }
 TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
 // Enable Timer0B.
 TimerEnable(TIMER0_BASE, TIMER_B);
 IntEnable(INT_TIMER0B);
 askStationFlag = NOTSET;
 }
 delay(500);
 }
 }

 //extern "C" void Timer0BIntHandler(void);
 extern "C" void Timer0BIntHandler(void) {
 // Clear the timer interrupt flag.
 TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
 static uint8_t timer0Counter = 0;
 if (!askStationFlag) {
 timer0Counter++;
 if (timer0Counter >= 20) {
 timer0Counter = 0;
 askStationFlag = SET;

 }
 }
 }
 */
//NORMAL SERVER INSTANCE
// Singleton instance of the radio
/*
 RF22 rf22(RFM23B_SLAVE_SELECT_PIN,RFM23B_SHUTDOWN_PIN,RFM23B_INTERRUPT_PIN);
 void setup()
 {
 Serial.begin(115200);
 if (!rf22.init())
 Serial.println("RF22 init failed");
 else
 Serial.println("RF22 init succed!");
 rf22.setModeRx();
 // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
 }
 void loop()
 {
 if (rf22.available())
 {
 // Should be a message for us now
 uint8_t buf[RF22_MAX_MESSAGE_LEN];
 uint8_t len = sizeof(buf);
 if (rf22.recv(buf, &len))
 {
 Serial.print("got request: ");
 Serial.println((char*)buf);

 // Send a reply

 uint8_t data[] = "And hello back to you";
 rf22.send(data, sizeof(data));
 rf22.waitPacketSent(3000);
 Serial.println("Sent a reply");
 }
 else
 {
 Serial.println("recv failed");
 }
 }
 delay(500);
 }
 */

/*
 ////////////////////////////////////////WIFI MODULE TESTS ///////////////////////////////////////////////////////
 //useful variables
 unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
 boolean lastConnected = false; // state of the connection last time through the main loop
 const unsigned long postingInterval = 10 * 1000; // delay between updates, in milliseconds
 IPAddress server(50, 62, 217, 1); // numeric IP for Energia.nu (no DNS)
 // Initialize the WiFi client library
 // with the IP address and port of the server
 // that you want to connect to (port 80 is default for HTTP):
 WiFiClient client;

 static void printWifiStatus() {
 // print the SSID of the network you're attached to:
 Serial.print("SSID-------: ");
 Serial.println(WiFi.SSID());
 // print your WiFi shield's IP address:
 IPAddress ip = WiFi.localIP();
 Serial.print("IP Address: ");
 Serial.println(ip);
 }

 static void httpRequest() {
 // if there's a successful connection:
 if (client.connect(server, 80)) {
 Serial.println("connecting...");
 // send the HTTP PUT request:
 client.println("GET /latest.txt HTTP/1.1");
 client.println("Host: energia.nu");
 client.println("User-Agent: WeatherStationWIFI");
 client.println("Connection: close");
 client.println();

 // note the time that the connection was made:
 lastConnectionTime = millis();
 } else {
 // if you couldn't make a connection:
 Serial.println("connection failed");
 Serial.println("disconnecting.");
 client.stop();
 }
 }

 static bool smartConfig(void) {
 pinMode(RED_LED, OUTPUT);
 uint8_t configButton = PF_1;
 pinMode(configButton, INPUT_PULLUP);
 if (digitalRead(configButton) == LOW) {
 digitalWrite(RED_LED, 1);
 WiFi.begin();
 Serial.print("SMART Config started");
 if (WiFi.startSmartConfig() == 0) {
 Serial.print("SMART Config Finished Succesfully");
 digitalWrite(RED_LED, 0);
 } else {
 Serial.print("SMART Config Failed");
 return false;
 }
 }
 return true;
 }

 char ssid[] = "UPC1512586";     //  your network SSID (name)
 char pass[] = "TRRANEXG";      //  your network password
 int keyIndex = 0;         // your network key Index number (needed only for WEP)

 void setup() {
 //Initialize serial and wait for port to open:
 Serial.begin(115200);

 // Set communication pins for CC3000
 WiFi.setCSpin(18);  // 18: P2_2 @ F5529, PE_0 @ LM4F/TM4C
 WiFi.setENpin(2);   //  2: P6_5 @ F5529, PB_5 @ LM4F/TM4C
 WiFi.setIRQpin(19); // 19: P2_0 @ F5529, PB_2 @ LM4F/TM4C

 // attempt to connect to Wifi network:

 // smartConfig();

 Serial.print("Attempting to connect to SSID: ");
 Serial.println(ssid);
 // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
 uint8_t mac[6]={1,2,3,4,5,6};

 if(WiFi.begin(ssid, pass)==-6){
 Serial.print("INIT SPI FUCKED UP ");
 }
 WiFi.macAddress(mac);
 for (int i= 0;i<6;i++){
 Serial.print(mac[i]);
 }


 Serial.println("Connected to wifi");
 Serial.println("Waiting for DHCP address....");
 // wait for 5 seconds for connection:
 delay(5000);
 printWifiStatus();

 }

 void loop() {
 // if there are incoming bytes available
 // from the server, read them and print them:
 while (client.available()) {
 char c = client.read();
 Serial.write(c);
 }

 // if the server's disconnected, stop the client:
 if (!client.connected() && lastConnected) {
 Serial.println();
 Serial.println("disconnecting from server.");
 client.stop();

 }

 if (!client.connected()
 && (millis() - lastConnectionTime > postingInterval)) {
 httpRequest();

 }

 lastConnected = client.connected();
 }
 */
#if 1

//MAIN APPLICATION##########################################
//Useful Variables
//CC3000
char ssid[] = "UPC1512586"; //  your network SSID (name)
char pass[] = "TRRANEXG"; //  your network password
int keyIndex = 0; // your network key Index number (needed only for WEP)
unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
boolean lastConnected = false; // state of the connection last time through the main loop
const unsigned long postingInterval = 10 * 1000; // delay between updates, in milliseconds
IPAddress server(50, 62, 217, 1); // numeric IP for Energia.nu (no DNS)

// create singleton objects
//RFM23B
static RF22ReliableDatagram* rfm23b;
//CC3000
WiFiClient client;

uint8_t data[] = "DATA_FROM_WIFI_MODULE";
// Dont put this on the stack better:
uint8_t buf[RF22_MAX_MESSAGE_LEN];

static void printWifiStatus() {
	// print the SSID of the network you're attached to:
	PRINT_DEBUG("SSID: ");
	PRINT_DEBUG(WiFi.SSID());
	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	PRINT_DEBUG("IP Address: ");
	PRINT_DEBUG(ip);
}

static void httpRequest() {
	// if there's a successful connection:
	if (client.connect(server, 80)) {
		PRINT_DEBUG("connecting...");
		// send the HTTP PUT request:
		client.println("GET /latest.txt HTTP/1.1");
		client.println("Host: energia.nu");
		client.println("User-Agent: WeatherStationWIFI");
		client.println("Connection: close");
		client.println();

		// note the time that the connection was made:
		lastConnectionTime = millis();
	} else {
		// if you couldn't make a connection:
		PRINT_DEBUG("connection failed");
		PRINT_DEBUG("disconnecting.");
		client.stop();
	}
}

static bool smartConfig(void) {
	pinMode(RED_LED, OUTPUT);
	uint8_t configButton = PF_1;
	pinMode(configButton, INPUT_PULLUP);
	if (digitalRead(configButton) == LOW) {
		digitalWrite(RED_LED, 1);
		WiFi.begin();
		PRINT_DEBUG("SMART Config started");
		if (WiFi.startSmartConfig() == 0) {
			PRINT_DEBUG("SMART Config Finished Succesfully");
			digitalWrite(RED_LED, 0);
		} else {
			PRINT_DEBUG("SMART Config Failed");
			return false;
		}
	}
	return true;
}

static volatile uint32_t askStationFlag = 0;
//private functions

static void initTimer0(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC_UP);
	TimerPrescaleSet(TIMER0_BASE, TIMER_B, 255);
	// Set the Timer0B load value to 1ms.
	TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet() / 1000000);
	// Enable processor interrupts.
	IntMasterEnable();
	// Configure the Timer0B interrupt for timer timeout.
	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	// Enable the Timer0B interrupt on the processor (NVIC).
	IntEnable(INT_TIMER0B);
	// Enable Timer0B.
	TimerEnable(TIMER0_BASE, TIMER_B);
	// Loop forever while the Timer0B runs.
}

void setup() {
	//  Run at system clock at 80MHz
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
	SYSCTL_XTAL_16MHZ); //in wiring.c clock 80MHZ enabled
	INIT_DEBUG();
	//Serial.begin(115200); /////////////////////////

#ifdef CC3000_ENABLED

	// attempt to connect to Wifi network:
	// Set communication pins for CC3000
	WiFi.setCSpin(PE_0);//PE_0 @ LM4F/TM4C
	WiFi.setENpin(PB_5);//PB_5 @ LM4F/TM4C
	WiFi.setIRQpin(PB_2);// PB_2 @ LM4F/TM4C

	// attempt to connect to Wifi network:
	// smartConfig();
	Serial.print("Attempting to connect to SSID: ");
	Serial.println(ssid);
	// Connect to WPA/WPA2 network. Change this line if using open or WEP network:

	//WiFi.begin(ssid, pass);

	Serial.println("Connected to wifi");
	Serial.println("Waiting for DHCP address....");
	// wait for 3 seconds for connection:
	delay(1000);
	//printWifiStatus();

#endif

	//digitalWrite(PB_5, LOW);
#ifdef RFM23D_ENABLED
	rfm23b = new RF22ReliableDatagram(SERVER_ADDRESS, RFM23B_SLAVE_SELECT_PIN,
	RFM23B_SHUTDOWN_PIN, RFM23B_INTERRUPT_PIN);
	//HardwareSpiCC3000.end();
	//pinMode(PB_2, OUTPUT);
	//digitalWrite(PB_5,LOW);
	//noInt
	/*
	 if (!rfm23b->init()) { // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
	 Serial.println("RF23D init failed");
	 //	while (1)
	 //		;
	 } else
	 Serial.println("RF23D init succeded");
	 */

	while (!rfm23b->init()) { // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
		delay(100);
		Serial.println("RF23D init failed");
	}
	Serial.println("RF23D init succeded");
	initTimer0();
#endif

}

void loop() {
#ifdef RFM23D_ENABLED
	if (askStationFlag == SET) {
		// Wait for a message addressed to us from the client
		uint8_t len = sizeof(buf);
		uint8_t from;
		// Turn off Timer0B interrupt.
		TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
		// Clear any pending interrupt flag.
		TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
		IntDisable(INT_TIMER0B);

		if (!rfm23b->sendtoWait(data, sizeof(data), STATION_ADDRESS)) {
			PRINT_DEBUG("sending request to station failed...");
		} else {
			if (rfm23b->recvfromAckTimeout(buf, &len, 1000, &from)) {
				PRINT_DEBUG("received data from Station : 0x");
				PRINT_DEBUG((from, HEX));
				/*Serial.print(": ");
				 Serial.print((char*) buf);
				 Serial.print("\r\n");
				 */
#endif

				//aJsonObject* jsonObject = aJson.parse((char*)buf);
				//aJsonObject* humidity = aJson.getObjectItem(jsonObject, "HUM");
				//Serial.print(humidity->type);
				//Serial.print(humidity->valuefloat);

				DataParser *dataParser = new DataParser((char*) buf);
				for (int dataIdx = DataParser::eHumidity;
						dataIdx < DataParser::eMaxNrOfTypes; ++dataIdx) {



						if (dataIdx == DataParser::eHumidity) {
							dataParser->createHumObj(
									dataParser->obtainDataObject<
											HUMIDITY_DATA_TYPE>(
											(DataParser::DataTypes) dataIdx));
							PRINT_DEBUG("humidity: ");
							PRINT_DEBUG(
									(HUMIDITY_DATA_TYPE )dataParser->getHumObj()->getDataValue());
							if(!(dataParser->getHumObj()->isDataValid())){
								dataParser->getHumObj()->setDataValue(INVALID_VALUE);
							}
						}

						else if (dataIdx == DataParser::eTemperature) {
							dataParser->createTempObj(
									dataParser->obtainDataObject<
											TEMPERATURE_DATA_TYPE>(
											(DataParser::DataTypes) dataIdx));
							PRINT_DEBUG("temp: ");
							PRINT_DEBUG(
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
							PRINT_DEBUG("pressure: ");
							PRINT_DEBUG(
									(PRESSURE_DATA_TYPE )dataParser->getPressObj()->getDataValue());
							if(!(dataParser->getPressObj()->isDataValid())){
								dataParser->getPressObj()->setDataValue(INVALID_VALUE);
							}
						}

						else if (dataIdx == DataParser::eLight) {
							dataParser->createLightObj(
									dataParser->obtainDataObject<LIGHT_DATA_TYPE>(
											(DataParser::DataTypes) dataIdx));
							PRINT_DEBUG("light: ");
							PRINT_DEBUG(
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

#ifdef CC3000_ENABLED
				httpRequest();
				// if there are incoming bytes available
				// from the server, read them and print them:
				while (client.available()) {
					char c = client.read();
					Serial.write(c);
				}

				// if the server's disconnected, stop the client:
				if (!client.connected()) {
					Serial.println();
					Serial.println("disconnecting from server.");
					client.stop();
				}
#endif
#ifdef RFM23D_ENABLED
			} else {
				PRINT_DEBUG(
						"No response from station, is station running?\n\n");
			}

			TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
			// Enable Timer0B.
			TimerEnable(TIMER0_BASE, TIMER_B);
			IntEnable(INT_TIMER0B);
			askStationFlag = NOTSET;
	}
}
	//delay(3000);
#endif
}

//extern "C" void Timer0BIntHandler(void);
extern "C" void Timer0BIntHandler(void) {
	// Clear the timer interrupt flag.
	TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	static uint8_t timer0Counter = 0;
	if (!askStationFlag) {
		timer0Counter++;
		if (timer0Counter >= 20) {
			timer0Counter = 0;
			askStationFlag = SET;

		}
	}
}

#endif

/*
 void setup() {
 Serial.begin(115200);
 // Set communication pins for CC3000
 WiFi.setCSpin(18);  // 18: P2_2 @ F5529, PE_0 @ LM4F/TM4C
 WiFi.setENpin(2);   //  2: P6_5 @ F5529, PB_5 @ LM4F/TM4C
 WiFi.setIRQpin(19); // 19: P2_0 @ F5529, PB_2 @ LM4F/TM4C

 if (!rfm23b.init())
 Serial.println("RF23D init failed");
 else
 Serial.println("RF23D init succed");

 // attempt to connect to Wifi network:

 // smartConfig();

 Serial.print("Attempting to connect to SSID: ");
 Serial.println(ssid);
 // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
 //noInterrupts();
 WiFi.begin(ssid, pass);
 Serial.println("Connected to wifi");
 Serial.println("Waiting for DHCP address....");
 // wait for 5 seconds for connection:
 delay(5000);
 printWifiStatus();
 //interrupts();


 }

 void loop() {
 // Wait for a message addressed to us from the client
 uint8_t len = sizeof(buf);
 uint8_t from;

 if (rfm23b.recvfromAckTimeout(buf, &len, 5000, &from)) {
 Serial.print("got request from : 0x");
 Serial.print(from, HEX);
 Serial.print(": ");
 Serial.print((char*) buf);
 Serial.print("\n");
 // Send a reply back to the originator client
 if (!rfm23b.sendtoWait(data, sizeof(data), from))
 Serial.print("sendtoWait failed");
 } else
 Serial.print("did not receive any data\n");

 // if there are incoming bytes available
 // from the server, read them and print them:
 while (client.available()) {
 char c = client.read();
 Serial.write(c);
 }

 // if the server's disconnected, stop the client:
 if (!client.connected() && lastConnected) {
 Serial.println();
 Serial.println("disconnecting from server.");
 client.stop();

 }

 if (!client.connected()
 && (millis() - lastConnectionTime > postingInterval)) {
 httpRequest();

 }

 lastConnected = client.connected();
 delay(500);
 }



 */

