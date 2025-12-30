#include <EEPROM.h>
#include "my_def.h"
#include "my_debug.h"
#include "audio.h"
#include "audio_i2s.h"
#include "ui.h"


void playAlarm(){
    if ((statusAlarm || testAlarm) && timerAudio < millis()) {
        switch (soundTheme){
            case SOUND_THEME_ALARM:  playSoundVol(alarm_wav, alarm_wav_len,soundVolume); break;
            case SOUND_THEME_BEEP:   playSoundVol(beepbeep_wav, beepbeep_wav_len,soundVolume); break;
            case SOUND_THEME_BIP:    playSoundVol(bip_wav, bip_wav_len,soundVolume); break;
            case SOUND_THEME_BOAT:   playSoundVol(boat_wav, boat_wav_len,soundVolume); break;
            case SOUND_THEME_CUCKOO: playSoundVol(cuckoo_wav, cuckoo_wav_len,soundVolume); break;
            case SOUND_THEME_MORSE:  playSoundVol(morse_wav, morse_wav_len,soundVolume); break;
        }
        // playTone(10000, 0.3, 50);
        timerAudio = millis() + 3000; // 3 sec
        testAlarm = false;
        DEBUG_AUDIO_PRINTLN("PLAY SOUND");
    }
}

void setAudioTheme(int themeid) {
    // Check for wrong ID
    if (themeid >= 0 && themeid < 6){
        soundTheme = themeid;
        EEPROM.write(EEPROM_THEME, themeid);
        EEPROM.commit();
        testAlarm = true;
    }
}

void setAudioVolume(int volumeid) {
    // Check for wrong ID
    if (volumeid >= 0 && volumeid < 4){
        setAudioVolumeIcon(volumeid);
        EEPROM.write(EEPROM_VOLUME,soundVolume);
        EEPROM.commit();
        DEBUG_AUDIO_PRINT("AUDIO VOLUME: ");
        DEBUG_AUDIO_PRINT(volumeid);
        DEBUG_AUDIO_PRINTLN(soundVolume);
        testAlarm = true;
    }
}

void setAudioVolumeIcon(int volumeid) {
    // if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
        switch (volumeid){
            case 0: 
                soundVolume = VOLUME_OFF;
                lv_image_set_src(ui_imgTempHeaderVol, &ui_img_volume_off_png);
                break;

            case 1: 
                soundVolume = VOLUME_LOW;
                lv_image_set_src(ui_imgTempHeaderVol, &ui_img_volume_low_png);
                break;

            case 2: 
                soundVolume = VOLUME_MID;
                lv_image_set_src(ui_imgTempHeaderVol, &ui_img_volume_mid_png);
                break;

            case 3: 
                soundVolume = VOLUME_HIGH;
                lv_image_set_src(ui_imgTempHeaderVol, &ui_img_volume_up_png);
                break;
        }
    //     xSemaphoreGive(xGuiSemaphore); 
    // }
}

void setAudioVolumeLabel(int volumeid){
    char lblBuffer[16];

    switch(volumeid){
        case 1: sprintf(lblBuffer,"Volumen\n%d%%", VOLUME_LOW); break;
        case 2: sprintf(lblBuffer,"Volumen\n%d%%", VOLUME_MID); break;
        case 3: sprintf(lblBuffer,"Volumen\n%d%%", VOLUME_HIGH); break;
        case 0: sprintf(lblBuffer,"Volumen\n%d%%", VOLUME_OFF);
        default: break;
    }
    lv_label_set_text(ui_lblTempSoundVolume, lblBuffer); 
}

void setup_audio() {
    EEPROM.begin(2);
    soundTheme = EEPROM.read(EEPROM_THEME);
    soundVolume = EEPROM.read(EEPROM_VOLUME);
    int volumeid = 0;
    switch(soundVolume){
        case VOLUME_OFF: volumeid = 0; break;
        case VOLUME_LOW: volumeid = 1; break;
        case VOLUME_MID: volumeid = 2; break;
        case VOLUME_HIGH: volumeid = 3; break;
        default: volumeid = 2; soundVolume = VOLUME_MID; break;
    }

    // Print changes
    if (xSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(SEMAPHORE_WAIT)) == pdTRUE) {
        lv_roller_set_selected(ui_rollSoundTheme, soundTheme, LV_ANIM_OFF);
        lv_slider_set_value(ui_sldTempSoundVolume, volumeid, LV_ANIM_OFF);
        setAudioVolumeLabel(volumeid);
        setAudioVolumeIcon(volumeid);
        xSemaphoreGive(xGuiSemaphore);
    }
}