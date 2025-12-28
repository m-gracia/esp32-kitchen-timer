/*
 * Debug functions
 */
#ifndef _MY_DEBUG_H_
#define _MY_DEBUG_H_

#define DEBUG       // General debug switch. No data sent if commented

// Uncomment to enable
#define DEBUG_WIFI
#define DEBUG_MQTT
#define DEBUG_NTP
#define DEBUG_TFT
#define DEBUG_WEB
//#define DEBUG_WEB_SECRET    // When enabled, URLs with API keys are sended through serial COM



// Don't change below this line
#ifdef DEBUG
    #define DEBUG_PRINT(x)  Serial.print(x)
    #define DEBUG_PRINTLN(x)  Serial.println(x)

    #ifdef DEBUG_WIFI
    #define DEBUG_WIFI_PRINT(x)  Serial.print(x)
    #define DEBUG_WIFI_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_WIFI_PRINT(x)
    #define DEBUG_WIFI_PRINTLN(x)
    #endif

    #ifdef DEBUG_MQTT
    #define DEBUG_MQTT_PRINT(x)  Serial.print(x)
    #define DEBUG_MQTT_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_MQTT_PRINT(x)
    #define DEBUG_MQTT_PRINTLN(x)
    #endif
  
    #ifdef DEBUG_NTP
    #define DEBUG_NTP_PRINT(x)  Serial.print(x)
    #define DEBUG_NTP_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_NTP_PRINT(x)
    #define DEBUG_NTP_PRINTLN(x)
    #endif

    #ifdef DEBUG_TFT
    #define DEBUG_TFT_PRINT(x)  Serial.print(x)
    #define DEBUG_TFT_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_TFT_PRINT(x)
    #define DEBUG_TFT_PRINTLN(x)
    #endif

    #ifdef DEBUG_WEB
    #define DEBUG_WEB_PRINT(x)  Serial.print(x)
    #define DEBUG_WEB_PRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_WEB_PRINT(x)
    #define DEBUG_WEB_PRINTLN(x)
    #endif

    #ifdef DEBUG_WEB_SECRET
    #define DEBUG_WEB_SECRETPRINT(x)  Serial.print(x)
    #define DEBUG_WEB_SECRETPRINTLN(x)  Serial.println(x)
    #else
    #define DEBUG_WEB_SECRETPRINT(x) Serial.print("**Hidden**")
    #define DEBUG_WEB_SECRETPRINTLN(x) Serial.println("**Hidden**")
    #endif

#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_WIFI_PRINT(x)
    #define DEBUG_WIFI_PRINTLN(x)
    #define DEBUG_MQTT_PRINT(x)
    #define DEBUG_MQTT_PRINTLN(x)
    #define DEBUG_NTP_PRINT(x)
    #define DEBUG_NTP_PRINTLN(x)
    #define DEBUG_TFT_PRINT(x)
    #define DEBUG_TFT_PRINTLN(x)
    #define DEBUG_WEB_PRINT(x)
    #define DEBUG_WEB_PRINTLN(x)
    #define DEBUG_WEB_SECRETPRINT(x)
    #define DEBUG_WEB_SECRETPRINTLN(x)
#endif

#endif  // _MY_DEBUG_H_