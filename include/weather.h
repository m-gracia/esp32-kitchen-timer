#ifndef _WEATHER_H_
#define _WEATHER_H_
#include "ui.h"

const lv_image_dsc_t * getWeatherIcon(int id);   // Return weather icon
void getWeather();                      // Get data from OpenWeatherMap

#endif  // _WEATHER_H_