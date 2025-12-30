#ifndef _AUDIO_I2S_H_
#define _AUDIO_I2S_H_

#include <Arduino.h>

void setupI2S();        // Prepare I2S communication
void playSound(const uint8_t* data, uint32_t len);      // Plays a sound at maximum volume
void playSoundVol(const uint8_t* data, uint32_t len, int volume);   // Plays a sound at maximum volume
void playTone(float frecuency, float duration, int volume); // Plays a tone

#endif  // _AUDIO_I2S_H_