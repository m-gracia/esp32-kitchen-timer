#include <time.h>
#include <lodepng.h>
#include "weather.h"
#include "my_def.h"
#include "my_debug.h"
#include "ui.h"

const lv_image_dsc_t * getWeatherIcon(int id) {
 switch(id){
  case 800: return &ui_img_sun_png; break;
  case 801: 
  case 802: return &ui_img_cloudy_png; break;
  case 803: 
  case 804: return &ui_img_cloud_png; break;
  
  case 200: 
  case 201: 
  case 202: 
  case 210: 
  case 211: 
  case 212: 
  case 221: 
  case 230: 
  case 231: 
  case 232: return &ui_img_lightning_png; break;

  case 300: 
  case 301: 
  case 302: 
  case 310: 
  case 311: 
  case 312: 
  case 313: 
  case 314: 
  case 321: // lightRain; break;

  case 500: 
  case 501: 
  case 502: 
  case 503: 
  case 504: 
  case 511: return &ui_img_rainy_png; break;
  case 520: 
  case 521: // moderateRain; break;
  case 522: 
  case 531: return &ui_img_rainy_hard_png; break;

  case 600: // lightSnow; break;
  case 601: 
  case 602: // snow; break;
  case 611: 
  case 612: 
  case 615: 
  case 616: 
  case 620: // lightSnow; break;
  case 621: 
  case 622: return &ui_img_snowy_png; break;

  case 701: 
  case 711: 
  case 721: 
  case 731: 
  case 741: 
  case 751: 
  case 761: 
  case 762: 
  case 771: 
  case 781: return &ui_img_fog_png; break;

  default: return &ui_img_sun_png; break; // Draws sun
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
    if (statusWifi != STATUS_WARN)
    statusWifi = STATUS_WARN;
  } else {
    DEBUG_WEB_PRINTLN("Weather connected OK");
    if (statusWifi != STATUS_OK)
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
    char weatherSunriseChar[6];
    snprintf(weatherSunriseChar, sizeof(weatherSunriseChar), "%02d:%02d", timeinfoSR->tm_hour, timeinfoSR->tm_min);
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
      lv_label_set_text_fmt(ui_lblMainSunrise, "%s", weatherSunriseChar);
      lv_label_set_text_fmt(ui_lblMainSunset, "%d:%d", timeinfoSS->tm_hour, timeinfoSS->tm_min);
      xSemaphoreGive(xGuiSemaphore);
    }
  }
  weather_client.stop();
  DEBUG_WEB_PRINTLN("Weather Disconnected");
}

void getSeeing(){
  WiFiClient wifi_client;
  String http_url;

  http_url = SEEING_PNG_PATH;
  DEBUG_WEB_PRINT("Seeing URL: ");
  DEBUG_WEB_SECRETPRINTLN(http_url);

  HttpClient seeing_client(wifi_client, seeing_server, seeing_port);
  seeing_client.beginRequest();

  if(seeing_client.get(http_url) != 0){
    DEBUG_WEB_PRINTLN("Seeing fail getting data");
    if (statusWifi != STATUS_WARN)
    statusWifi = STATUS_WARN;
  } else {
    DEBUG_WEB_PRINTLN("Seeing connected OK");
    if (statusWifi != STATUS_OK)
    statusWifi = STATUS_OK;

    seeing_client.sendHeader("Connection", "close");
    seeing_client.endRequest();

    // Read png from server
    int contentLength = seeing_client.contentLength();
    uint8_t seeingPngBuffer[4000];       // Seeing PNG downloaded
    int seeingPngSize = 0;

    while (seeing_client.available() && seeingPngSize < contentLength) { 
      int c = seeing_client.read(); 
      if (c < 0) 
        break; 
      seeingPngBuffer[seeingPngSize++] = (uint8_t)c; 
    }

    // Decode
    uint8_t* decoded_pixel_data = NULL;
    uint32_t width, height;
    unsigned error = lodepng_decode32(&decoded_pixel_data, &width, &height, 
      seeingPngBuffer, seeingPngSize);    

    if(error) {
        DEBUG_WEB_PRINT("Seeing Error LodePNG: ");
        DEBUG_WEB_PRINTLN(lodepng_error_text(error));
    } else {

      // Change to RGB565 / 16b
      uint16_t* final_buffer = (uint16_t*) malloc(width * height * 2);
      for(uint32_t i = 0; i < width * height; i++) {
        uint8_t r = decoded_pixel_data[i*4 + 0];
        uint8_t g = decoded_pixel_data[i*4 + 1];
        uint8_t b = decoded_pixel_data[i*4 + 2];
        final_buffer[i] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
      }
      free(decoded_pixel_data);

      // Move data to img_dsc_t
      seeing_img_dsc.header.cf = LV_COLOR_FORMAT_RGB565;
      seeing_img_dsc.header.magic = LV_IMAGE_SRC_VARIABLE;
      seeing_img_dsc.header.w = width;
      seeing_img_dsc.header.h = height;
      seeing_img_dsc.data_size = width * height * 4;
      seeing_img_dsc.data = (const uint8_t*)final_buffer;

      // Print image
      if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
        lv_image_set_src(ui_imgMainSeeing, &seeing_img_dsc);
        xSemaphoreGive(xGuiSemaphore);
      }
    }   
  }
  seeing_client.stop();
  DEBUG_WEB_PRINTLN("Seeing Disconnected"); 
}