#ifndef _WEATHER_H_
#define _WEATHER_H_
#include "ui.h"

const lv_image_dsc_t * getWeatherIcon(int id);   // Return weather icon
void getWeather();                      // Get data from OpenWeatherMap
void getSeeing();                       // Get image from ClearOutside

#endif  // _WEATHER_H_