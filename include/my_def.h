#ifndef _MY_DEF_H_
#define _MY_DEF_H_

#include <Arduino.h>
#include "secrets.h" // To store secret information used here. You must create first. Look on https://github.com/m-gracia for the contents.

// Display
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
enum BoardConstants { GFX_BL=38/*-1*/, LVGL_BUFFER_RATIO=6 };
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 480;
enum { SCREENBUFFER_SIZE_PIXELS = screenWidth * LVGL_BUFFER_RATIO };
static lv_color_t *buf;
// Broken after Arduino_GFX upgrade
// Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
//   1 /* CS */, 12 /* SCK */, 11 /* SDA */,
//   45 /* DE */, 4/* VSYNC */, 5 /* HSYNC */, 21 /* PCLK */,
//   39 /* R0 */, 40 /* R1 */, 41 /* R2 */, 42 /* R3 */, 2 /* R4 */,
//   0 /* G0/P22 */, 9 /* G1/P23 */, 14 /* G2/P24 */, 47 /* G3/P25 */, 48 /* G4/P26 */, 3 /* G5 */,
//   6 /* B0 */, 7 /* B1 */, 15 /* B2 */, 16 /* B3 */, 8 /* B4 */
// );
// 
// Arduino_ST7701_RGBPanel *gfx = new Arduino_ST7701_RGBPanel(
//   bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */,
//   true /* IPS */, 480 /* width */, 480 /* height */,
//   st7701_type1_init_operations, sizeof(st7701_type1_init_operations),
//   true /* BGR */);

static Arduino_DataBus *bus = new Arduino_SWSPI(
    GFX_NOT_DEFINED /* DC */, 39 /* CS */,
    48 /* SCK */, 47 /* SDA or MOSI */, GFX_NOT_DEFINED /* MISO */);

static Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    18 /* DE */, 17 /* VSYNC */, 16 /* HSYNC */, 21 /* PCLK */,
    11 /* R0 */, 12 /* R1 */, 13 /* R2 */, 14 /* R3 */, 0 /* R4 */,
    8 /* G0 */, 20 /* G1 */, 3 /* G2 */, 46 /* G3 */, 9 /* G4 */, 10 /* G5 */,
    4 /* B0 */, 5 /* B1 */, 6 /* B2 */, 7 /* B3 */, 15 /* B4 */,
    1 /* hsync_polarity */, 10 /* hsync_front_porch */, 8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
    1 /* vsync_polarity */, 10 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 20 /* vsync_back_porch */);

static Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    480 /* width */, 480 /* height */, rgbpanel, 2 /* rotation */, true /* auto_flush */,
    bus, GFX_NOT_DEFINED /* RST */, st7701_type1_init_operations, sizeof(st7701_type1_init_operations));

// Touch
#include <Wire.h>
#include <TAMC_GT911.h>
#define TOUCH_GT911
#define TOUCH_GT911_SCL 45 //18
#define TOUCH_GT911_SDA 19 //17
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST -1 //38
#define TOUCH_GT911_ROTATION ROTATION_INVERTED //ROTATION_NORMAL
#define TOUCH_MAP_X1 480
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 480
#define TOUCH_MAP_Y2 0
extern int touch_last_x;
extern int touch_last_y;
static TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

// NTP
#include <WiFiUdp.h>
#include <NTP.h>
#define NTP_SERVER      "0.pool.ntp.org"
static WiFiUDP wifiUdp;
extern NTP ntp;

// Wifi
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoHttpClient.h>  // https://github.com/arduino-libraries/ArduinoHttpClient
static WiFiClient wifiClient;
static const char wlan_ssid[] = WIFI_SSID;  // Defined in secrets.h
static const char wlan_pass[] = WIFI_PASS;  // Defined in secrets.h

// MQTT
#include <MQTTClient.h>
extern MQTTClient mqtt;

static String mqtt_server =         MQTT_SERVER;        // Defined in secrets.h
static int mqtt_serverport =        MQTT_SERVERPORT;    // Defined in secrets.h
static String mqtt_username =       MQTT_USERNAME;      // Defined in secrets.h
static String mqtt_pass =           MQTT_PASS;          // Defined in secrets.h
static String mqtt_clientid =       MQTT_CLIENTID;      // Defined in secrets.h
static String mqtt_fingerprint =    MQTT_SSL_FINGERPRINT; // Defined in secrets.h

#define MQTT_TOPIC_SENSOR               "/home/kitchen/kitchen01"
#define MQTT_TOPIC_DISH                 "/home/kitchen/dishwasher"
extern byte dishwasherOnOff;
#define MQTT_TOPIC_TERRAZA              "/home/terraza/"
#define MQTT_TOPIC_TERR_TIME            MQTT_TOPIC_TERRAZA "riego/time"
#define MQTT_TOPIC_TERR_TEMP            MQTT_TOPIC_TERRAZA "riego/temp"
#define MQTT_TOPIC_IRRIGATIONONOFF      MQTT_TOPIC_TERRAZA "riego/onoff" //(bool)
extern byte irrigationOnOff;
#define MQTT_TOPIC_IRRIGATIONDURATION   MQTT_TOPIC_TERRAZA "riego/duration" //(min 1-256)
extern byte irrigationDuration;
#define MQTT_TOPIC_IRRIGATIONONTIME     MQTT_TOPIC_TERRAZA "riego/ontime" //(hh:mm)
#define MQTT_TOPIC_IRRIGATIONLASTON     MQTT_TOPIC_TERRAZA "riego/laston" //(yyyy-mm-dd hh:mm)
extern byte irrigationOnHour;
extern byte irrigationOnMinute;

#define MQTT_TOPIC_BASE_ENT             "/home/pasillo/entrada/"
#define MQTT_TOPIC_ENT_TIME             MQTT_TOPIC_BASE_ENT "time" //(hh:mm)
#define MQTT_TOPIC_ENT_TEMP             MQTT_TOPIC_BASE_ENT "temp"
#define MQTT_TOPIC_ENT_HUMEDAD          MQTT_TOPIC_BASE_ENT "humedad"
#define MQTT_TOPIC_RGBONOFF             MQTT_TOPIC_BASE_ENT "rgbonoff" //(bool)
#define MQTT_TOPIC_LEDW                 MQTT_TOPIC_BASE_ENT "ledw" //(byte)
extern byte ledw;


// Weather OpenWeatherMap
#include <ArduinoJson.h>    // https://github.com/bblanchon/ArduinoJson
static const char weather_server[] = "api.openweathermap.org";
static const int weather_port = 80;
static String weather_apikey = WEATHER_APIKEY; // Defined in secrets.h
static String weather_cityId = WEATHER_CITYID; // Default city ID. Defined in secrets.h
// extern String weatherLocation;          // City
extern float weatherTemperature;       // Temperature
extern int weatherHumidity;       // Humidity
//extern String weatherWeather;         // Weather text
extern String weatherDescription;       // Weather description
extern float weatherWind;               // Wind speed
extern float weatherSunrise;            // Sunrise time
extern float weatherSunset;             // Sunset time
extern int weatherIcon;                 // Weather icon

// Timers
#include "timerChrono.h"
extern timerChrono timer1;
extern timerChrono timer2;
extern timerChrono timer3;
extern timerChrono timer4;

// Audio
#include <driver/i2s.h>
#define I2S_DOUT        40
#define I2S_BCLK        1
#define I2S_LRC         2
#define I2S_NUM         I2S_NUM_0
#define VOLUME_HIGH     100
#define VOLUME_MID      50
#define VOLUME_LOW      30
#define VOLUME_OFF      0
#define SOUND_THEME_ALARM   0
#define SOUND_THEME_BEEP    1
#define SOUND_THEME_BIP     2
#define SOUND_THEME_BOAT    3
#define SOUND_THEME_CUCKOO  4
#define SOUND_THEME_MORSE   5
#define EEPROM_THEME    0
#define EEPROM_VOLUME   1
extern byte soundTheme;
extern byte soundVolume;
extern bool testAlarm;

//Status IDs
#define STATUS_UNK 8        // Unknown
#define STATUS_CRIT 2       // Critical
#define STATUS_WARN 1       // Warning
#define STATUS_OK 0         // OK
#define STATUS_POWERON 1    // Powering ON

//Status variables
extern unsigned char statusWifi;        // Wifi Status
extern unsigned char statusMQTT;        // MQTT Status
extern bool statusAlarm;                // Alarm ON/OFF

// Run timers
extern unsigned long timerWeather;
extern unsigned long timerMQTT;
extern unsigned long timerNTP;
extern unsigned long timerAudio;

/* To send changes to MQTT
 *
 * The bits are set when a new information needs to be sended by MQTT
 * 1 - Dishwasher
 * 2 - IrrigationOnOff
 * 3 - IrrigationDuration
 * 4 - LedW
 * 5 - 
 * 6 - 
 * 7 - 
 * 8 - 
 * 9 - 
 * 10 - 
 * 11 - 
 * 12 - 
 * 13 - 
 * 14 - 
 * 15 - 
 */
extern byte dataChanged;

// Tasks and semaphore
#define SEMAPHORE_WAIT  100         // Time to wait for the semaphore
extern TaskHandle_t T_loopOthers;
extern SemaphoreHandle_t xGuiSemaphore;


#endif  // _MY_DEF_H_