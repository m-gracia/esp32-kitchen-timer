#include <time.h>
#include "weather.h"
#include "my_def.h"
#include "my_debug.h"
#include "ui.h"

const lv_image_dsc_t * getWeatherIcon(int id) {
 switch(id){
  case 800: return &ui_img_sun_png; // drawBmpS("/weather/clear.bmp",x,y,100,100); break;
  case 801: 
  case 802: return &ui_img_cloudy_png; // drawBmpS("/weather/fewCloud.bmp",x,y,100,100); break;
  case 803: 
  case 804: return &ui_img_cloud_png; // drawBmpS("/weather/cloud.bmp",x,y,100,100); break;
  
  case 200: 
  case 201: 
  case 202: 
  case 210: 
  case 211: 
  case 212: 
  case 221: 
  case 230: 
  case 231: 
  case 232: return &ui_img_lightning_png; // drawBmpS("/weather/thunderstorm.bmp",x,y,100,100); break;

  case 300: 
  case 301: 
  case 302: 
  case 310: 
  case 311: 
  case 312: 
  case 313: 
  case 314: 
  case 321: // drawBmpS("/weather/lightRain.bmp",x,y,100,100); break;

  case 500: 
  case 501: 
  case 502: 
  case 503: 
  case 504: 
  case 511: return &ui_img_rainy_png; // drawBmpS("/weather/lightRain.bmp",x,y,100,100); break;
  case 520: 
  case 521: // drawBmpS("/weather/moderateRain.bmp",x,y,100,100); break;
  case 522: 
  case 531: return &ui_img_rainy_hard_png; //drawBmpS("/weather/heavyRain.bmp",x,y,100,100); break;

  case 600: // drawBmpS("/weather/lightSnow.bmp",x,y,100,100); break;
  case 601: 
  case 602: //drawBmpS("/weather/snow.bmp",x,y,100,100); break;
  case 611: 
  case 612: 
  case 615: 
  case 616: 
  case 620: // drawBmpR("/weather/lightSnow.bmp",x,y,100,100); break;
  case 621: 
  case 622: return &ui_img_snowy_png; //drawBmpR("/weather/snow.bmp",x,y,100,100); break;

  case 701: 
  case 711: 
  case 721: 
  case 731: 
  case 741: 
  case 751: 
  case 761: 
  case 762: 
  case 771: 
  case 781: return &ui_img_fog_png; //drawBmpR("/weather/fog.bmp",x,y,100,100); break;

  default: return &ui_img_sun_png; //break; // Draws sun
 }
}

void getWeather(){
  WiFiClient wifi_client;
  String http_url;

  http_url = "/data/2.5/forecast?id="+weather_cityId+"&units=metric&lang=es&cnt=1&appid="+weather_apikey;
  DEBUG_WEB_PRINT("Weather URL: ");
  DEBUG_WEB_SECRETPRINTLN(http_url);

  HttpClient weather_client(wifi_client, weather_server, weather_port);
  
  if(weather_client.get(http_url) != 0){
    DEBUG_WEB_PRINTLN("Weather fail getting data");
    if (statusWifi != STATUS_WARN) //bitSet(bikeDataChanged,2);
    statusWifi = STATUS_WARN;
  } else {
    DEBUG_WEB_PRINTLN("Weather connected OK");
    if (statusWifi != STATUS_OK) //bitSet(bikeDataChanged,2);
    statusWifi = STATUS_OK;
    
    String result = weather_client.responseBody();
    DEBUG_WEB_PRINTLN("Weather Readed:");
    DEBUG_WEB_PRINTLN(result);

    JsonDocument root;
    if (deserializeJson(root, result)) { 
      DEBUG_WEB_PRINTLN("parseObject() failed");
      return;
    }

    // weatherLocation = root["city"]["name"].as<String>();
    weatherIcon = root["list"][0]["weather"][0]["id"].as<int>();
    weatherTemperature = root["list"][0]["main"]["temp"].as<float>();
    weatherHumidity = root["list"][0]["main"]["humidity"]; //.as<int>()
    // weatherWeather = root["list"][0]["weather"][0]["main"].as<const char*>();
    weatherDescription = root["list"][0]["weather"][0]["description"].as<const char*>();
    weatherWind = root["list"][0]["wind"]["speed"].as<float>();
    weatherSunrise = root["city"]["sunrise"].as<float>();
    weatherSunset = root["city"]["sunset"].as<float>();

    time_t epochSR = weatherSunrise;
    struct tm *timeinfoSR = localtime(&epochSR);
    time_t epochSS = weatherSunset;
    struct tm *timeinfoSS = localtime(&epochSS);

    DEBUG_WEB_PRINT("Weather Icon:");
    DEBUG_WEB_PRINTLN(weatherIcon);
    DEBUG_WEB_PRINT("Weather Temp:");
    DEBUG_WEB_PRINTLN(weatherTemperature);
    DEBUG_WEB_PRINT("Weather Hunidity:");
    DEBUG_WEB_PRINTLN(weatherHumidity);

    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
      lv_image_set_src(ui_imgMainForecast, getWeatherIcon(weatherIcon));
      lv_label_set_text(ui_lblMainForecast, weatherDescription.c_str());
      lv_label_set_text_fmt(ui_lblMainTemp, "%d C", (int)weatherTemperature);
      lv_label_set_text_fmt(ui_lblMainHumidity, "%d%%", weatherHumidity);
      lv_label_set_text_fmt(ui_lblMainWind, "%d", (int)weatherWind);
      lv_label_set_text_fmt(ui_lblMainSunrise, "%d:%d", timeinfoSR->tm_hour, timeinfoSR->tm_min);
      lv_label_set_text_fmt(ui_lblMainSunset, "%d:%d", timeinfoSS->tm_hour, timeinfoSS->tm_min);
      xSemaphoreGive(xGuiSemaphore);
    }
  }
  weather_client.stop();
  DEBUG_WEB_PRINTLN("Weather Disconnected");
}