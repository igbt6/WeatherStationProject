#include "Energia.h"
#include <SPI.h>
#include "CC3000/TCPclient.h"
#include "CC3000/TCPserver.h"
#include "CC3000/WiFi.h"
#include "CC3000/WiFiUdp.h"
#include "RF22/RF22ReliableDatagram.h"

void setup();
void loop();
////////////////////////////////////////RFM23B MODULE TESTS ///////////////////////////////////////////////////////
#define STATION_ADDRESS 1
#define SERVER_ADDRESS 2
#define RFM23B_SLAVE_SELECT_PIN PE_1
#define RFM23B_SHUTDOWN_PIN PE_2
#define RFM23B_INTERRUPT_PIN PE_3

// RELIABLE DATAGRAMMMMM
RF22ReliableDatagram rfm23b(SERVER_ADDRESS, RFM23B_SLAVE_SELECT_PIN,
RFM23B_SHUTDOWN_PIN, RFM23B_INTERRUPT_PIN);

void setup() {
	Serial.begin(115200);
	if (!rfm23b.init())
		Serial.println("RF22 init failed");
	// Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
}

uint8_t data[] = "DATA";
// Dont put this on the stack:
uint8_t buf[30]; //RF22_MAX_MESSAGE_LEN

void loop() {
	while (1) {
		// Wait for a message addressed to us from the client
		uint8_t len = sizeof(buf);
		uint8_t from;

		if (!rfm23b.sendtoWait(data, sizeof(data), STATION_ADDRESS)) {
			Serial.print("sending request to station failed...");
		} else {
			if (rfm23b.recvfromAckTimeout(buf, &len, 5000, &from)) {
				Serial.print("got data from Station : 0x");
				Serial.print(from, HEX);
				Serial.print(": ");
				Serial.print((char*) buf);
				Serial.print("\n");

			} else {
				Serial.print(
						"No response from station, is station running?\n\n");
			}
		}
		delay(500);
	}
}

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
 Serial.print("SSID: ");
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
 WiFi.begin(ssid, pass);
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

/*

 //MAIN APPLICATION##########################################
 //Useful Variables
 //CC3000
 char ssid[] = "UPC1512586";     //  your network SSID (name)
 char pass[] = "TRRANEXG";      //  your network password
 int keyIndex = 0;         // your network key Index number (needed only for WEP)
 unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
 boolean lastConnected = false; // state of the connection last time through the main loop
 const unsigned long postingInterval = 10 * 1000; // delay between updates, in milliseconds
 IPAddress server(50, 62, 217, 1); // numeric IP for Energia.nu (no DNS)
 //RFM23B
 uint8_t data[] = "hello back from WIFI SERVER";
 // Dont put this on the stack:
 uint8_t buf[30]; //RF22_MAX_MESSAGE_LEN

 //objects
 RF22ReliableDatagram rfm23b(SERVER_ADDRESS, RFM23B_SLAVE_SELECT_PIN,
 RFM23B_SHUTDOWN_PIN, RFM23B_INTERRUPT_PIN);
 WiFiClient client;

 static void printWifiStatus() {
 // print the SSID of the network you're attached to:
 Serial.print("SSID: ");
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
