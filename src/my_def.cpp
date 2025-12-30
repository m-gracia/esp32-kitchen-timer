#include <Arduino.h>
#include "my_def.h"

int touch_last_x = 0;
int touch_last_y = 0;

NTP ntp(wifiUdp);

MQTTClient mqtt;

byte dishwasherOnOff = 0;
byte irrigationOnOff = 0;
byte irrigationDuration = 0;
byte irrigationOnHour = 0;
byte irrigationOnMinute = 0;
byte ledw = 0;

// String weatherLocation = "";
float weatherTemperature;
int weatherHumidity = 0;
//String weatherWeather;
String weatherDescription;
float weatherWind;
float weatherSunrise;
float weatherSunset;
int weatherIcon = 0; //Shows nothing

timerChrono timer1;
timerChrono timer2;
timerChrono timer3;
timerChrono timer4;

byte soundTheme = SOUND_THEME_BEEP;
byte soundVolume = VOLUME_MID;
bool testAlarm = false;

unsigned char statusWifi = STATUS_UNK;
unsigned char statusMQTT = STATUS_UNK;
bool statusAlarm = false;

unsigned long timerWeather = 0;
unsigned long timerMQTT = 0;
unsigned long timerNTP = 0;
unsigned long timerAudio = 0;

byte dataChanged = 0;

TaskHandle_t T_loopOthers = NULL;
SemaphoreHandle_t xGuiSemaphore = xSemaphoreCreateMutex();