#include "my_def.h"
#include "my_debug.h"
#include "mqtt.h"
#include "secrets.h"
#include "ui.h"

void callback(MQTTClient *client, char topic[], char payload[], int length) {
  payload[length] = '\0';
  int rcv = atoi((char *)payload);

  DEBUG_MQTT_PRINT("MQTT Received: ");
  DEBUG_MQTT_PRINTLN(rcv);
  DEBUG_MQTT_PRINT("MQTT Length: ");
  DEBUG_MQTT_PRINTLN(length);
    
  if (strcmp(topic,MQTT_TOPIC_IRRIGATIONONOFF)==0){
    if(rcv == 0) irrigationOnOff=0;
    else irrigationOnOff=1;
    DEBUG_MQTT_PRINT("IRRIGATIONONOFF: ");
    DEBUG_MQTT_PRINTLN(irrigationOnOff);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      if (irrigationOnOff == 1) lv_obj_set_state(ui_swHomeTerrazaRiego, LV_STATE_CHECKED, true);
      else lv_obj_set_state(ui_swHomeTerrazaRiego, LV_STATE_CHECKED, false);
      xSemaphoreGive(xGuiSemaphore);
    }
    
  } else if (strcmp(topic,MQTT_TOPIC_IRRIGATIONDURATION)==0){
    irrigationDuration = rcv;
    DEBUG_MQTT_PRINT("IRRIGATIONDURATION: ");
    DEBUG_MQTT_PRINTLN(irrigationDuration);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_arc_set_value(ui_arcHomeTerrazaRiego, irrigationDuration);
      lv_label_set_text_fmt(ui_lblHomeTerrazaRiegoMin, "%d min", irrigationDuration);
      xSemaphoreGive(xGuiSemaphore);
    }
    
  } else if (strcmp(topic,MQTT_TOPIC_IRRIGATIONONTIME)==0){
    char temp[2];
    temp[0] = payload[0];
    temp[1] = payload[1];
    irrigationOnHour = atoi(temp);
    temp[0] = payload[3];
    temp[1] = payload[4];
    irrigationOnMinute = atoi(temp);
    DEBUG_MQTT_PRINT("IRRIGATIONONTIME: ");
    DEBUG_MQTT_PRINT(irrigationOnHour); DEBUG_MQTT_PRINT(":"); DEBUG_MQTT_PRINTLN(irrigationOnMinute);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text(ui_lblHomeTerrazaRiegoTime, payload);
      xSemaphoreGive(xGuiSemaphore);
    }

  } else if (strcmp(topic,MQTT_TOPIC_IRRIGATIONLASTON)==0){
    DEBUG_MQTT_PRINT("IRRIGATIONLASTON: ");
    DEBUG_MQTT_PRINTLN(payload);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text(ui_lblHomeTerrazaRiegoLastOn, payload);
      xSemaphoreGive(xGuiSemaphore);
    }

  } else if (strcmp(topic,MQTT_TOPIC_TERR_TIME)==0){
    DEBUG_MQTT_PRINT("TERRAZATIME: ");
    DEBUG_MQTT_PRINTLN(payload);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text(ui_lblHomeTerrazaTime, payload);
      xSemaphoreGive(xGuiSemaphore);
    }

  } else if (strcmp(topic,MQTT_TOPIC_TERR_TEMP)==0){
    DEBUG_MQTT_PRINT("TERRAZATEMP: ");
    DEBUG_MQTT_PRINTLN(payload);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text_fmt(ui_lblHomeTerrazaTemp, "%s C", payload);
      xSemaphoreGive(xGuiSemaphore);
    }
    
  } else if (strcmp(topic,MQTT_TOPIC_ENT_TIME)==0){
    DEBUG_MQTT_PRINT("ENTRADATIME: ");
    DEBUG_MQTT_PRINTLN(payload);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text(ui_lblHomeEntradaTime, payload);
      xSemaphoreGive(xGuiSemaphore);
    }

  } else if (strcmp(topic,MQTT_TOPIC_ENT_TEMP)==0){
    DEBUG_MQTT_PRINT("ENTRADATEMP: ");
    DEBUG_MQTT_PRINTLN(payload);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text_fmt(ui_lblHomeEntradaTemp, "%s C", payload);
      xSemaphoreGive(xGuiSemaphore);
    }
    
  } else if (strcmp(topic,MQTT_TOPIC_ENT_HUMEDAD)==0){
    DEBUG_MQTT_PRINT("ENTRADAHUMEDAD: ");
    DEBUG_MQTT_PRINTLN(payload);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_label_set_text_fmt(ui_lblHomeEntradaHumidity, "%s%%", payload);
      xSemaphoreGive(xGuiSemaphore);
    }
    
  } else if (strcmp(topic,MQTT_TOPIC_LEDW)==0){
    ledw = rcv;
    DEBUG_MQTT_PRINT("LEDW: ");
    DEBUG_MQTT_PRINTLN(ledw);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_arc_set_value(ui_arcHomeEntradaLight, ledw);
      xSemaphoreGive(xGuiSemaphore);
    }

  } else if (strcmp(topic,MQTT_TOPIC_DISH)==0){
    if(rcv == 0) dishwasherOnOff=0;
    else dishwasherOnOff=1;
    DEBUG_MQTT_PRINT("DISHWASHERONOFF: ");
    DEBUG_MQTT_PRINTLN(dishwasherOnOff);
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      if (dishwasherOnOff == 1) lv_obj_set_state(ui_swHomeEntradaDish, LV_STATE_CHECKED, true);
      else lv_obj_set_state(ui_swHomeEntradaDish, LV_STATE_CHECKED, false);
      xSemaphoreGive(xGuiSemaphore);
    }
  }
}

void sendMQTT() {
  if (dataChanged != 0) {
    if (bitRead(dataChanged,1)){ // Dishwasher
      if (!dishwasherOnOff) 
        mqtt.publish(MQTT_TOPIC_DISH, "0", true /*Retained*/, 1 /*QoS*/);
      else
        mqtt.publish(MQTT_TOPIC_DISH, "1", true /*Retained*/, 1 /*QoS*/);
      
      DEBUG_MQTT_PRINT("MQTT DISH: ");
      DEBUG_MQTT_PRINTLN(dishwasherOnOff);
    }

    if (bitRead(dataChanged,2)){ // IrrigationOnOff
      if (!irrigationOnOff) 
        mqtt.publish(MQTT_TOPIC_IRRIGATIONONOFF, "0", true /*Retained*/, 1 /*QoS*/);
      else
        mqtt.publish(MQTT_TOPIC_IRRIGATIONONOFF, "1", true /*Retained*/, 1 /*QoS*/);
      
      DEBUG_MQTT_PRINT("MQTT IRRIGATIONONOFF: ");
      DEBUG_MQTT_PRINTLN(irrigationOnOff);
    }

    if (bitRead(dataChanged,3)){ // IrrigationDuration
      mqtt.publish(MQTT_TOPIC_IRRIGATIONDURATION, String(irrigationDuration).c_str(), true /*Retained*/, 1 /*QoS*/);
      if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
          lv_label_set_text_fmt(ui_lblHomeTerrazaRiegoMin, "%d min", irrigationDuration);
          xSemaphoreGive(xGuiSemaphore);
      }
      DEBUG_MQTT_PRINT("MQTT IRRIGATIONDURATION: ");
      DEBUG_MQTT_PRINTLN(irrigationDuration);
    }

    if (bitRead(dataChanged,4)){ // LedW
      mqtt.publish(MQTT_TOPIC_LEDW, String(ledw).c_str(), true /*Retained*/, 1 /*QoS*/);
      DEBUG_MQTT_PRINT("MQTT LEDW: ");
      DEBUG_MQTT_PRINTLN(ledw);
    }

    dataChanged = 0;
  }
}

void reconnect_mqtt() {
  // Loop until we're reconnected or #tries
  int i=0;
  const int tries = 5;

  statusMQTT = STATUS_CRIT;
  while (!mqtt.connected() && i < tries) {  
    DEBUG_MQTT_PRINTLN("Attempting MQTT connection...");
    mqtt.setHost(MQTT_SERVER,MQTT_SERVERPORT);
    mqtt.onMessageAdvanced(callback);
    mqtt.setWill(MQTT_TOPIC_SENSOR,"unexpected exit",false /*Will retain*/,1 /*Will QoS*/);
    
    // Attempt to connect
    if (mqtt.connect(MQTT_CLIENTID,MQTT_USERNAME,MQTT_PASS)) {
      DEBUG_MQTT_PRINTLN("MQTT Connected");
      mqtt.subscribe(MQTT_TOPIC_DISH);
      mqtt.subscribe(MQTT_TOPIC_TERR_TIME);
      mqtt.subscribe(MQTT_TOPIC_TERR_TEMP);
      mqtt.subscribe(MQTT_TOPIC_IRRIGATIONONOFF);
      mqtt.subscribe(MQTT_TOPIC_IRRIGATIONONTIME);
      mqtt.subscribe(MQTT_TOPIC_IRRIGATIONDURATION);
      mqtt.subscribe(MQTT_TOPIC_IRRIGATIONLASTON);
      mqtt.subscribe(MQTT_TOPIC_ENT_TIME);
      mqtt.subscribe(MQTT_TOPIC_ENT_TEMP);
      mqtt.subscribe(MQTT_TOPIC_ENT_HUMEDAD);
      mqtt.subscribe(MQTT_TOPIC_RGBONOFF);
      mqtt.subscribe(MQTT_TOPIC_LEDW);


      statusMQTT = STATUS_OK;
      
    } else {
      DEBUG_MQTT_PRINT("MQTT Connection Failed, rc=");
      DEBUG_MQTT_PRINTLN(mqtt.lastError());
      DEBUG_MQTT_PRINTLN("Trying again ...");
      delay(1000);
    }
    i++;
  }

  // Print status
  if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
    if (statusMQTT == STATUS_OK) lv_image_set_src(ui_imgHomeHeaderWifi, &ui_img_wifi_on_png);
    else lv_image_set_src(ui_imgHomeHeaderWifi, &ui_img_wifi_error_png);
    xSemaphoreGive(xGuiSemaphore);
  }
}

void setup_wifi() {
  // Connect to WiFi network
  DEBUG_WIFI_PRINT("Connecting to SSID: "); DEBUG_WIFI_PRINTLN(WIFI_SSID);
  statusWifi = STATUS_CRIT;
  statusMQTT = STATUS_CRIT;  

  WiFi.begin(wlan_ssid, wlan_pass);

  int i=0;
  const int tries=20;
  
  while (WiFi.status() != WL_CONNECTED && i < tries) {
    delay(500);
    DEBUG_WIFI_PRINT(".");
    i++;
  }

  if (i < tries){
    DEBUG_WIFI_PRINTLN("");
    DEBUG_WIFI_PRINTLN("WiFi connected");
    DEBUG_WIFI_PRINT("IP address: "); DEBUG_WIFI_PRINTLN(WiFi.localIP());
    statusWifi = STATUS_OK;    

    // Use WiFiClientSecure class to create TLS connection
    DEBUG_MQTT_PRINT("Connecting to MQTT: "); DEBUG_MQTT_PRINTLN(MQTT_SERVER);
    if (!wifiClient.connect(MQTT_SERVER, MQTT_SERVERPORT)) {
      DEBUG_MQTT_PRINTLN("Connection failed");
      return;
    }
  
    mqtt.begin(wifiClient);
    
    /*
    if (wifiClient.verify(MQTT_SSL_FINGERPRINT, MQTT_SERVER)) {
      DEBUG_WIFI_PRINTLN("certificate matches");
    } else {
      DEBUG_WIFI_PRINTLN("certificate doesn't match");
    } */
  }

  // Print status
  if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
    if (statusWifi == STATUS_OK) lv_image_set_src(ui_imgHomeHeaderWifi, &ui_img_wifi_error_png);
    else lv_image_set_src(ui_imgHomeHeaderWifi, &ui_img_wifi_off_png);
    xSemaphoreGive(xGuiSemaphore);
  }
}