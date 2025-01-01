/***********************************************************************
  Program      :  CMRI - Node-EPS32-Functions
  Author       :  H&HExpres, Hai faessen
  Description  :  This Section Contains the Functions for CMRI Reading/Setting values and Checking that JMRI can Talk to the Node 

                  Do Not Change the Function Names unless you change them in the Main Program
                  
  Version      :  1.01
  Date         :  28 December 2024
  CopyRight (c):  H&HExpress 1996-2025

  Change History:

      1.01     :  Official Release for the Basic Sketch
*/

void InitializingPinsToBeUsed() {                  // Do not Change the Name of the Function
  // Basic Setup for the I2C Components attached to the ESP32  or the use of the standard Pins

  //Individual GPIO Pins on the ESP32
  pinMode(23, INPUT_PULLUP);         // Example for the Sensor
  pinMode(14, OUTPUT);               // Example for the Light output
  digitalWrite(14,HIGH);
  
  // Initialize the I2C Components  Like the  Servo Driver and InPut Output Ports as an Example
  Serial.println(F("Init:   Additinal I2C Components"));
  Serial.print(F("  Servo_Driver_00 : "));
  Servo_Driver_00.begin();
  Servo_Driver_00.setOscillatorFrequency(27000000);
  Servo_Driver_00.setPWMFreq(PWM_Frequency);  // Analog servos run at ~50 Hz updates between 40-1600  1600 = This is the maximum PWM frequency
  for ( int i=0; i<=15; i++) { Servo_Driver_00.setPWM(i, 0, 4096); } //Fully Off
  Serial.println(F("OK"));
  delay(5000);
  Serial.println(F("  Set Servo SY_TO_01 Turnouts Straight: "));
  Servo_Driver_00.writeMicroseconds(Servo_TO_01, USMAX);  //Default to straight = USMAX   divergent = USMIN
  Servo_Driver_00.writeMicroseconds(Servo_TO_02, USMAX);  //Default to straight = USMAX   divergent = USMIN
  Servo_Driver_00.writeMicroseconds(Servo_TO_03, USMAX);  //Default to straight = USMAX   divergent = USMIN
  delay(3000);
  Serial.println(F("  Set Servo SY_TO_01 Turnouts Diverted: "));
  Servo_Driver_00.writeMicroseconds(Servo_TO_01, USMIN);  //Default to straight = USMAX   divergent = USMIN
  Servo_Driver_00.writeMicroseconds(Servo_TO_02, USMIN);  //Default to straight = USMAX   divergent = USMIN
  Servo_Driver_00.writeMicroseconds(Servo_TO_03, USMIN);  //Default to straight = USMAX   divergent = USMIN
  delay(3000);
  Serial.println(F("  Set Servo SY_TO_01 Turnouts Straight: "));
  Servo_Driver_00.writeMicroseconds(Servo_TO_01, USMAX);  //Default to straight = USMAX   divergent = USMIN
  Servo_Driver_00.writeMicroseconds(Servo_TO_02, USMAX);  //Default to straight = USMAX   divergent = USMIN
  Servo_Driver_00.writeMicroseconds(Servo_TO_03, USMAX);  //Default to straight = USMAX   divergent = USMIN
  delay(5000);

  Serial.print(F("  Port Expander 00 : "));
  for (int i=0; i<16;i++) { Port_Expander_PCF8575_00.pinMode(i,OUTPUT); }
  for (int i=0; i<16;i++) { Port_Expander_PCF8575_00.digitalWrite(i,HIGH); }
  Serial.println(F("OK"));
  
  Serial.print(F("  Port Expander 01 : "));
  for (int i=0; i<8;i++) { Port_Expander_PCF8574_01.pinMode(i,OUTPUT); }
  for (int i=0; i<8;i++) { Port_Expander_PCF8574_01.digitalWrite(i,HIGH); }
  Serial.println(F("OK"));
  
}


void ReadingSensors() {                         // Do not Change the Name of the Function
  cmri.set_bit(0, !digitalRead(HeartBeatLed));  // Connected to the 1st Bit of the Node in JMRI with node 1 = 1001

  // Example of a Sensor Read on GPIO in 23 of the ESP32.  This could be any Sensor in JMRI with node 1 = 1002
  cmri.set_bit(1, !digitalRead(23));

  
}

void SettingOutputs() {                         // Do not Change the Name of the Function

  // Example of a Light output on GPIO pin 14 of the ESP 32.  In JMRI with node 1 = 1001
  int OutPut0 = cmri.get_bit(0);
  if (OutPut0 == 1) { digitalWrite(14, LOW);}
     else { digitalWrite(14, HIGH); }

  // Example for a 2 bit Turnout using a Snap Switch
  int TurnOut0a = cmri.get_bit(24);                                     // in JMRI with Node 1  1025
  if (TurnOut0a == 1) { Port_Expander_PCF8575_00.digitalWrite(0,LOW); }
     else { Port_Expander_PCF8575_00.digitalWrite(0,HIGH); }
  int TurnOut0b = cmri.get_bit(25);
  if (TurnOut0b == 1) { Port_Expander_PCF8575_00.digitalWrite(1,LOW); }
     else { Port_Expander_PCF8575_00.digitalWrite(1,HIGH); }
  int TurnOut1a = cmri.get_bit(26);                                     // in JMRI with Node 1  1027
  if (TurnOut1a == 1) { Port_Expander_PCF8575_00.digitalWrite(2,LOW); }
     else { Port_Expander_PCF8575_00.digitalWrite(2,HIGH); }
  int TurnOut1b = cmri.get_bit(27);
  if (TurnOut1b == 1) { Port_Expander_PCF8575_00.digitalWrite(3,LOW); }
     else { Port_Expander_PCF8575_00.digitalWrite(3,HIGH); }

// /*  Example section for using Servo's attached to a PCA9685
  // Turnouts for the Staging Yard
  int Servo0 = cmri.get_bit(36);                                        // in JMRI with Node 1  1037
  if (Servo0 == 1) {Servo_Driver_00.writeMicroseconds(Servo_TO_01, USMIN); }  
     else { Servo_Driver_00.writeMicroseconds(Servo_TO_01, USMAX); }             
  int Servo1 = cmri.get_bit(38);                                        // in JMRI with Node 1  1039
  if (Servo1 == 1) {Servo_Driver_00.writeMicroseconds(Servo_TO_02, USMIN); }  
     else { Servo_Driver_00.writeMicroseconds(Servo_TO_02, USMAX); }             
  int Servo2 = cmri.get_bit(40);                                        // in JMRI with Node 1  1039
  if (Servo2 == 1) {Servo_Driver_00.writeMicroseconds(Servo_TO_03, USMIN); }  
     else { Servo_Driver_00.writeMicroseconds(Servo_TO_03, USMAX); } 
// */            
     
}
