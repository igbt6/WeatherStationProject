#include "Energia.h"
#include <SPI.h>
#include <WiFi.h>

void setup();
void loop();

#include <TCPclient.h>
#include <TCPserver.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "RF22/RF22ReliableDatagram.h"

////////////////////////////////////////RFM23B MODULE TESTS ///////////////////////////////////////////////////////
#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2
#define RFM23B_SLAVE_SELECT_PIN PE_1
#define RFM23B_SHUTDOWN_PIN PE_2
#define RFM23B_INTERRUPT_PIN PE_3
// PD_0 = 23;  //CLK
// PD_1 = 24;  //SS
// PD_2 = 25;  //Rx
// PD_3 = 26;  //Tx
// PE_1 = 27;  //slaveSelectPin
// PE_2 = 28;  //shutdownPin
// PE_3 = 29;  //InteruptPin

// Singleton instance of the radio
RF22ReliableDatagram rf22(CLIENT_ADDRESS,RFM23B_SLAVE_SELECT_PIN,RFM23B_SHUTDOWN_PIN,RFM23B_INTERRUPT_PIN);

void setup()
{
  Serial.begin(9600);
  if (!rf22.init())
    Serial.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
}

uint8_t data[] = "Hello World!";
// Dont put this on the stack:
uint8_t buf[RF22_MAX_MESSAGE_LEN];

void loop()
{
  while (1)
  {
    Serial.println("Sending to rf22_datagram_server");

    // Send a message to rf22_server
    if (!rf22.sendtoWait(data, sizeof(data), SERVER_ADDRESS))
      Serial.println("sendtoWait failed");
    else
    {
      // Now wait for a reply from the server
 //     Serial.println(rf22.lastRssi(), HEX); // of the ACK
      uint8_t len = sizeof(buf);
      uint8_t from;
      if (rf22.recvfromAckTimeout(buf, &len, 2000, &from))
      {
        Serial.print("got reply from : 0x");
        Serial.print(from, HEX);
        Serial.print(": ");
        Serial.println((char*)buf);
      }
      else
      {
        Serial.println("No reply, is rf22_datagram_server running?");
      }
    }
    delay(500);
  }
}



/*
////////////////////////////////////////WIFI MODULE TESTS ///////////////////////////////////////////////////////
//useful variables
unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds
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
  }
  else {
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