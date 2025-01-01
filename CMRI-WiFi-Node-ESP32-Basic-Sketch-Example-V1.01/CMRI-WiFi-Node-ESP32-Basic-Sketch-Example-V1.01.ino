/***********************************************************************
  Program      :  CMRI - Wifi Node For ESP32 Basic - Sketch
  Author       :  H&HExpres, Hai faessen
  Description  :  This is a Basic Sketch for a CMRI WiFi Node for a ESP32 Development kit
                  It Contains a Heart Beat Function with a LED connected to GPIO pin 13 
                  As Soon when JMRI Connects to the Node the Heart Bet will Pulse every Second.
                  The Hear Beat is also connected to Sensor 0  which can be used in JMRI for Monitoring
                  
  Version      :  1.01
  Date         :  1 Januari 2025
  CopyRight (c): H&HExpress 1996-2025
                
  The Files 
       included:  CMRI-WiFi-Node-ESP32-Basi-Sketch-Example.ino
                  CMRI.cpp                  Originals Provided As Is by Michael Adams
                  CMRI.h                    Originals Provided As Is by Michael Adams
                  Definitions.h             Contains all Definitions and Variables needed for the sketch
                  HeartBeat.h               Contains the HeartBeat Definitions as is by Hai Faessen
                  HeartBeat.ino             Contains the HeartBeat Functions   as is by Hai Faessen
                  Node_ESP32_Functions.h    Contains the Definitions and Variables Needed for your own CMRI Node
                  Node_ESP32_Functions.ino  Contains the Function Needed for your own CMRI Node

  Change History:
      1.01     :  Official first Release of the Basic Sketch for 


  Special Thanks to:  Michael Adams for supplying the CMRI Files
                      https://www.michael.net.nz/
                      Wirenwood Model RailWay  for the Basics of Handling a CMRI Node over Wifi
                      https://www.youtube.com/@WirenwoodModelRailway
*/

// Setting App Version
#define CMRINodeNumber 1
String  CMRINodeName="<CMRI-WiFi0Node-ESP32-<Basic-Sketch-Example>-<VERSION_";
String  CMRINodeVersion="V1.01";


// Basic import of Header Files
#include "CMRI.h"
#include <Wire.h>
#include <WiFi.h>

// WiFi Definitions
const char* ssid = "Set-Your-WiFi-Router-Name";            // change this to your Wifi Router Name
const char* password =  "Set-Your_WiFi-Router-Password";   // change this to your Wifi Router Password

//HeartBeat Settings
#include "Definitions.h"                       // Basic Definitions as Timers and SSID
#include "HeartBeat.h"

// Adding Header File for the Functions
#include "Node_ESP32_Functions.h"              // Holds the Libraries to include and Global Variables for your CMRI Node

// Setting up the Wifi Port for Server/Client
#define TCP_PORT 9007                          // Use this port number in the advance settings for your Network Connection
WiFiServer wifiServer(TCP_PORT);
WiFiClient jmriClient;

CMRI cmri(CMRINodeNumber, 64, 64, jmriClient); // node number, number of inputs, number of outputs, stream client

//Initial Setup of the Node
void setup() {
  Serial.begin(115200);                        //Just for debug console feedback, not CMRI connection
  delay(1000);
  Serial.print(CMRINodeName);                  // Prints Function of Node and App Version
  Serial.print(CMRINodeVersion);
  Serial.println(F(">"));
  delay(1000);

  // Starting Wifi COnnection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
  delay(1000);

  // Setup Initial Settings
  HeartBeat_setup();           // HeartBeat Setup
  InitializingPinsToBeUsed();  // Located in the Node_ESP32_Functions.ino
}

//Main Loop for the Node
void loop() {

  WaitingForJMRI();  // Waiting for JMRI to Communicate with the Node if Connected the Loop will Continue and the HeartBeat LED is Flashing
  HeartBeat();       // LED will blink every second as soon when the Connection to JMRI is established. If it disconnects it stops.
  
  cmri.process();    // Running the CMRI Process
  
  SettingOutputs();  // Setting Outputs like Turnouts, Lights etc //Located in the Node_ESP32_Functions.ino
  ReadingSensors();  // Reading Sensors so they can be processed  //Located in the Node_ESP32_Functions.ino
  
}

//Test if JMRI is Connected       
bool WaitingForJMRI() {
  bool jmriConnected = jmriClient.connected();
  while (!jmriConnected) {
    jmriClient = wifiServer.available();
    if (jmriClient && jmriClient.connected()) {
      jmriConnected = true;
      Serial.println("JMRI Connected");
    }
  }
  return true;
}
