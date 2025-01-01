// Header File for the Node_ESP32_Functions 

#include <PCF8574.h>                      //If not needed  comment out this section 
#include <PCF8575.h>                      //If not needed  comment out this section 
#include <Adafruit_PWMServoDriver.h>      //If not needed  comment out this section 

// Settings of the Port Expander
PCF8575 Port_Expander_PCF8575_00(0x20);   // Adding 16 Additional Input/Output Ports for Sensors or Switches
// Settings of the Port Expander
PCF8575 Port_Expander_PCF8574_01(0x21);   // Adding 8 Additional Input/Output Ports for Sensors or Switches

// Servo Drivers or Light Dimmers                                                        
Adafruit_PWMServoDriver Servo_Driver_00 = Adafruit_PWMServoDriver(0x40);    // Adding the Servo Driver

#define PWM_Frequency    50  // Analog servos run at ~50 Hz updates

//the difference between USMIN and USMAX for the Servo  you will need to set your own
#define USMIN  612                        // This is the rounded 'minimum' microsecond length based for the divergent setting
#define USMAX  850                        // This is the rounded 'maximum' microsecond length based for the straight setting

#define Servo_TO_01 00                       // Servo Turnout 1
#define Servo_TO_02 01                       // Servo Turnout 2
#define Servo_TO_03 02                       // Servo Turnout 3
