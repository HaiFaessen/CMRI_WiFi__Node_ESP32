//HeartBeat Settings
// Definitions LEDS
#ifndef LEDOFF
#define LEDOFF HIGH   // NOTE: HIGH = LED is OFF
#endif
#ifndef LEDON
#define LEDON LOW     // NOTE: LOW  = LED is ON
#endif
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define HeartBeatLed LED_BUILTIN // for Arduino LED_BUILTIN
bool HeartBeatLed_OnOff = false;
long heartbeatcMillis = 0;
long heartbeatpMillis = 0;
