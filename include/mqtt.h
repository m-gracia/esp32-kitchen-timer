#ifndef _MQTT_H_
#define _MQTT_H_
#include <Arduino.h>

void callback(MQTTClient *client, char topic[], char payload[], int length);     // MQTT Callback function
void sendMQTT();        // Send data to MQTT Server
void reconnect_mqtt();  // Connect or reconnect to MQTT server
void setup_wifi();     // Initialize wifi and mqtt

#endif  // _MQTT_H_