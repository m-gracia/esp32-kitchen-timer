https://icomoon.io/app
https://m3.material.io/
https://demo.alessioatzeni.com/meteocons/

Hack colores invertidos:
https://github.com/moononournation/Arduino_GFX/issues/684
Arduino_GFX/src/display/Arduino_RGB_Display.h
Line 511 in 365a70b
 // WRITE_COMMAND_8, 0x21,   // 0x20 normal, 0x21 IPS 
WRITE_COMMAND_8, 0x20,   // 0x20 normal, 0x21 IPS 

Line 419 in 365a70b
// WRITE_C8_D8, 0xCD, 0x08, 
WRITE_C8_D8, 0xCD, 0x00,//0x08

python3 LVGLImage.py --cf RGB565 image.png

## Secrets.h file
A _secrets.h_ file must be created inside of the _/include_ folder with this data:
```
#ifndef _SECRETS_H_
#define _SECRETS_H_

#define WEATHER_APIKEY "your_openweathermap_api_key"
#define WEATHER_CITYID "3104324"    // Zaragoza

#define WIFI_SSID   "mySSID"        // Your Wifi SSID
#define WIFI_PASS   "myWIFIPass"    // Your Wifi password

#define MQTT_SERVER         "192.168.1.1"       // MQTT Server IP Address
#define MQTT_SERVERPORT     1883                // MQTT Server port
#define MQTT_USERNAME       "mymqttusername"    // MQTT Username
#define MQTT_PASS           "mymqttpassword"    // MQTT Password
#define MQTT_CLIENTID       "client01"   // MQTT server Client ID
#define MQTT_SSL_FINGERPRINT    "00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF 00 11 22 33"       // MQTT Server SSL fingerprint

#endif  // _SECRETS_H_
```