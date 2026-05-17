#include <Arduino.h>
#include <EEPROM.h>
#include <lvgl.h>
#include "my_def.h"
#include "my_debug.h"
#include "mqtt.h"
#include "weather.h"
#include "display.h"
#include "ui.h"
#include "audio_i2s.h"
#include "audio.h"

void checkTimers() {
  // Update timer labels
  if (timer1.hasChanged())
    lv_label_set_text(ui_lblTempTimer1Count, timer1.getTimeChar());
  if (timer2.hasChanged()) 
    lv_label_set_text(ui_lblTempTimer2Count, timer2.getTimeChar());
  if (timer3.hasChanged()) 
    lv_label_set_text(ui_lblTempTimer3Count, timer3.getTimeChar());
  if (timer4.hasChanged()) 
    lv_label_set_text(ui_lblTempTimer4Count, timer4.getTimeChar());

  statusAlarm = false;

  // If some timer has overflowed change color to red and activate the alarm
  if (timer1.isOverflow()) {
    if (timer1.getStatus() == STATUS_TIMER_ON) statusAlarm = true;

    ui_object_set_themeable_style_property(ui_contTempTemp1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_contTempTemp1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer1Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer1Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer1Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer1Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
      _ui_theme_alpha_colorTimerOut);
  }

  if (timer2.isOverflow()) {
    if (timer2.getStatus() == STATUS_TIMER_ON) statusAlarm = true;
    ui_object_set_themeable_style_property(ui_contTempTemp2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_contTempTemp2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer2Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer2Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer2Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer2Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
      _ui_theme_alpha_colorTimerOut);
  }

  if (timer3.isOverflow()) {
    if (timer3.getStatus() == STATUS_TIMER_ON) statusAlarm = true;
    ui_object_set_themeable_style_property(ui_contTempTemp3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_contTempTemp3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer3Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer3Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer3Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer3Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
      _ui_theme_alpha_colorTimerOut);
  }

  if (timer4.isOverflow()) {
    if (timer4.getStatus() == STATUS_TIMER_ON) statusAlarm = true;
    ui_object_set_themeable_style_property(ui_contTempTemp4, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_contTempTemp4, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer4Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer4Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
      _ui_theme_alpha_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer4Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
      _ui_theme_color_colorTimerOut);
    ui_object_set_themeable_style_property(ui_lblTempTimer4Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
      _ui_theme_alpha_colorTimerOut);
  }
}

// TASK ON CORE 0 //
void loopOthers (void * parameter){
  for(;;) {    
    checkTimers();

    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(10)) == pdTRUE) {
      lv_timer_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
    delay(10);    // For WDog feeding
  }
}
// -------------- //

void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  DEBUG_PRINTLN("Manuel Gracia.May-2026");
  DEBUG_PRINTLN("https://github.com/m-gracia");
  DEBUG_PRINTLN("esp32-kitchen-timer_20260516");

  // Serial.printf("Tamaño total PSRAM: %d bytes\n", ESP.getPsramSize());
  //   Serial.printf("PSRAM libre: %d bytes\n", ESP.getFreePsram());
    
  //   if (ESP.getPsramSize() == 0) {
  //       Serial.println("!!! ERROR: PSRAM no detectada. Revisa la config de platformio.ini !!!");
  //   }

  // Init Setup
  setupI2S();
  initDisplay();    // Must be initiated first
  setup_audio();
  setup_wifi();
  reconnect_mqtt();

  configTzTime(NTP_ZONE, NTP_SERVER);

  xTaskCreatePinnedToCore(
      loopOthers, // Function to implement the task
      "loopOthers", // Name of the task
      20000,  // Stack size in words
      NULL,  // Task input parameter
      1,  // Priority of the task
      &T_loopOthers,  // Task handle.
      0); // Core where the task should run
      
  DEBUG_PRINTLN("Setup end");
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    setup_wifi();

  } else {
    if(!mqtt.connected()) reconnect_mqtt();

    if(timerNTP < millis()) {
      // ntp.update();
      struct tm timeinfo;
      configTzTime(NTP_ZONE, NTP_SERVER);
      getLocalTime(&timeinfo);
      char bufferTime[8];
      strftime(bufferTime, sizeof(bufferTime), "%H:%M", &timeinfo);
      char bufferDate[64];
      strftime(bufferDate, sizeof(bufferDate), "%A, %B %d %Y", &timeinfo); //Eg: Saturday, May 16 2026

      DEBUG_NTP_PRINT("NTP TIME: "); DEBUG_NTP_PRINTLN(bufferTime);
      DEBUG_NTP_PRINT("NTP DATE: "); DEBUG_NTP_PRINTLN(bufferDate);
      if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
        lv_label_set_text_fmt(ui_lblMainTime, bufferTime);
        lv_label_set_text_fmt(ui_lblTempHeader, "TEMPORIZADORES - %s", bufferTime);
        lv_label_set_text_fmt(ui_lblMainDate, bufferDate);
        lv_calendar_set_today_date(ui_calMain, timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
        lv_calendar_set_showed_date(ui_calMain, timeinfo.tm_year + 1900, timeinfo.tm_mon + 1);
        xSemaphoreGive(xGuiSemaphore);
      }
      timerNTP = millis() + 30000; // 30 sec
    }

    if (statusMQTT == STATUS_OK) {
      sendMQTT();
      mqtt.loop();
    }

    if (timerWeather < millis()){
      getWeather();
      getSeeing();
      timerWeather = millis() + 600000;  // 10 min
    }
  }

  playAlarm();

  delay(10);  // For WDog feeding
}