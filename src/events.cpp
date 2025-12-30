#include "my_def.h"
#include "my_debug.h"
#include "events.h"
#include "ui.h"
#include "audio.h"

void evTempAddChronoClick(int temp){
    // Start chrono mode
    switch(temp){
        case 1:
            timer1.start(TIMER_MODE_CHRONO);
            lv_obj_remove_flag(ui_imgTempTimer1Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_add_flag(ui_panTempTemp1Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(ui_panTempTemp1Control, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(ui_lblTempTimer1Count, "00:00");
            break;

        case 2:
            timer2.start(TIMER_MODE_CHRONO);
            lv_obj_remove_flag(ui_imgTempTimer2Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_add_flag(ui_panTempTemp2Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(ui_panTempTemp2Control, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(ui_lblTempTimer2Count, "00:00");
            break;

        case 3:
            timer3.start(TIMER_MODE_CHRONO);
            lv_obj_remove_flag(ui_imgTempTimer3Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_add_flag(ui_panTempTemp3Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(ui_panTempTemp3Control, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(ui_lblTempTimer3Count, "00:00");
            break;

        case 4:
            timer4.start(TIMER_MODE_CHRONO);
            lv_obj_remove_flag(ui_imgTempTimer4Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_add_flag(ui_panTempTemp4Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(ui_panTempTemp4Control, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(ui_lblTempTimer4Count, "00:00");
            break;

        default: break;
    }	
}

void evTempPlayClick (int temp){
    // Play / Pause timer
    // If timer is paused stop alarm. It will be activated again on checkTimers() if some timer is overflowed and running
    switch(temp){
        case 1: 
            timer1.play_pause(); 
            if (timer1.getStatus() == STATUS_TIMER_PAUSE) statusAlarm = false;
            break;

        case 2: 
            timer2.play_pause(); 
            if (timer2.getStatus() == STATUS_TIMER_PAUSE) statusAlarm = false;
            break;
        case 3: 
            timer3.play_pause(); 
            if (timer3.getStatus() == STATUS_TIMER_PAUSE) statusAlarm = false;
            break;
        case 4: 
            timer4.play_pause(); 
            if (timer4.getStatus() == STATUS_TIMER_PAUSE) statusAlarm = false;
            break;
        default: break;
    }	
}

void evTempStopClick (int temp){
    // Stop timer
    // Stop alarm. It will be activated again on checkTimers() if some timer is overflowed and running
    statusAlarm = false;

    switch(temp){
        case 1: 
            timer1.stop();
            lv_obj_add_flag(ui_imgTempTimer1Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_remove_flag(ui_panTempTemp1Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_panTempTemp1Control, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_state(ui_imgTempTemp1Play, LV_STATE_CHECKED);
            ui_object_set_themeable_style_property(ui_contTempTemp1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                                _ui_theme_color_colorTimerDef); //_ui_theme_color_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer1Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                    _ui_theme_alpha_colorTimerDef); //_ui_theme_alpha_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer1Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                                _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer1Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                _ui_theme_alpha_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer1Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                                    _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer1Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                                    _ui_theme_alpha_colorTimerDef);
            lv_label_set_text(ui_lblTempTimer1Count, "--:--");
            lv_label_set_text(ui_lblTempTimer1Time, "--:--");
            break;

        case 2: 
            timer2.stop();
            lv_obj_add_flag(ui_imgTempTimer2Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_remove_flag(ui_panTempTemp2Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_panTempTemp2Control, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_state(ui_imgTempTemp2Play, LV_STATE_CHECKED);
            ui_object_set_themeable_style_property(ui_contTempTemp2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                                _ui_theme_color_colorTimerDef); //_ui_theme_color_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer2Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                    _ui_theme_alpha_colorTimerDef); //_ui_theme_alpha_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer2Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                                _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer2Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                _ui_theme_alpha_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer2Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                                    _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer2Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                                    _ui_theme_alpha_colorTimerDef);
            lv_label_set_text(ui_lblTempTimer2Count, "--:--");
            lv_label_set_text(ui_lblTempTimer2Time, "--:--");
            break;

        case 3: 
            timer3.stop();
            lv_obj_add_flag(ui_imgTempTimer3Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_remove_flag(ui_panTempTemp3Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_panTempTemp3Control, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_state(ui_imgTempTemp3Play, LV_STATE_CHECKED);
            ui_object_set_themeable_style_property(ui_contTempTemp3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                                _ui_theme_color_colorTimerDef); //_ui_theme_color_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer3Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                    _ui_theme_alpha_colorTimerDef); //_ui_theme_alpha_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer3Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                                _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer3Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                _ui_theme_alpha_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer3Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                                    _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer3Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                                    _ui_theme_alpha_colorTimerDef);
            lv_label_set_text(ui_lblTempTimer3Count, "--:--");
            lv_label_set_text(ui_lblTempTimer3Time, "--:--");
            break;

        case 4: 
            timer4.stop();
            lv_obj_add_flag(ui_imgTempTimer4Chrono, LV_OBJ_FLAG_HIDDEN); 
            lv_obj_remove_flag(ui_panTempTemp4Add, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_panTempTemp4Control, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_state(ui_imgTempTemp4Play, LV_STATE_CHECKED);
            ui_object_set_themeable_style_property(ui_contTempTemp4, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                                _ui_theme_color_colorTimerDef); //_ui_theme_color_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer4Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                    _ui_theme_alpha_colorTimerDef); //_ui_theme_alpha_colorTimerOut
            ui_object_set_themeable_style_property(ui_lblTempTimer4Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                                _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer4Time, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                                _ui_theme_alpha_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer4Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                                    _ui_theme_color_colorTimerDef);
            ui_object_set_themeable_style_property(ui_lblTempTimer4Count, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                                    _ui_theme_alpha_colorTimerDef);
            lv_label_set_text(ui_lblTempTimer4Count, "--:--");
            lv_label_set_text(ui_lblTempTimer4Time, "--:--");
            break;
            
        default: break;
    }	
}

void evTempNewOKClick(){
    // Get data
	char *txtHeader = lv_label_get_text(ui_lblTempNewHeader);
	int minDec = lv_roller_get_selected(ui_rollTempNewMinDec) * 10;
    DEBUG_TFT_PRINT("MinDec: "); DEBUG_TFT_PRINTLN(minDec);
	int min = lv_roller_get_selected(ui_rollTempNewMin) + minDec;
    DEBUG_TFT_PRINT("Min: "); DEBUG_TFT_PRINTLN(min);

	// Start timer and change views
	if (strcmp(txtHeader, "TEMPORIZADOR 1") == 0){
        timer1.start(TIMER_MODE_TIMER, min);
		lv_label_set_text_fmt(ui_lblTempTimer1Count, "%d:00", min);
		lv_label_set_text_fmt(ui_lblTempTimer1Time, "%d:00", min);
		lv_obj_add_flag(ui_panTempTemp1Add, LV_OBJ_FLAG_HIDDEN);
		lv_obj_remove_flag(ui_panTempTemp1Control, LV_OBJ_FLAG_HIDDEN);

	} else if (strcmp(txtHeader, "TEMPORIZADOR 2") == 0){
        timer2.start(TIMER_MODE_TIMER, min);
		lv_label_set_text_fmt(ui_lblTempTimer2Count,  "%d:00", min);
		lv_label_set_text_fmt(ui_lblTempTimer2Time,  "%d:00", min);
		lv_obj_add_flag(ui_panTempTemp2Add, LV_OBJ_FLAG_HIDDEN);
		lv_obj_remove_flag(ui_panTempTemp2Control, LV_OBJ_FLAG_HIDDEN);
	
	} else if (strcmp(txtHeader, "TEMPORIZADOR 3") == 0){
        timer3.start(TIMER_MODE_TIMER, min);
		lv_label_set_text_fmt(ui_lblTempTimer3Count,  "%d:00", min);
		lv_label_set_text_fmt(ui_lblTempTimer3Time,  "%d:00", min);
		lv_obj_add_flag(ui_panTempTemp3Add, LV_OBJ_FLAG_HIDDEN);
		lv_obj_remove_flag(ui_panTempTemp3Control, LV_OBJ_FLAG_HIDDEN);

	} else if (strcmp(txtHeader, "TEMPORIZADOR 4") == 0){
        timer4.start(TIMER_MODE_TIMER, min);
		lv_label_set_text_fmt(ui_lblTempTimer4Count,  "%d:00", min);
		lv_label_set_text_fmt(ui_lblTempTimer4Time,  "%d:00", min);
		lv_obj_add_flag(ui_panTempTemp4Add, LV_OBJ_FLAG_HIDDEN);
		lv_obj_remove_flag(ui_panTempTemp4Control, LV_OBJ_FLAG_HIDDEN);
	
	}

	// Change screen
	_ui_screen_change(&ui_scrTimers, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, &ui_scrTimers_screen_init);

}

void evEntradaLightChange() {
    ledw = lv_arc_get_value(ui_arcHomeEntradaLight);
    bitSet(dataChanged,4);    
}

void evEntradaDishClick() {
    dishwasherOnOff = lv_obj_has_state(ui_swHomeEntradaDish, LV_STATE_CHECKED);
    bitSet(dataChanged,1);    
}

void evRiegoChange() {
    irrigationDuration = lv_arc_get_value(ui_arcHomeTerrazaRiego);
    bitSet(dataChanged,3);    
}

void evTerrazaRiegoClick() {
    irrigationOnOff = lv_obj_has_state(ui_swHomeTerrazaRiego, LV_STATE_CHECKED);
    bitSet(dataChanged,2);    
}

void evSoundThemeChange() {
    int themeid = lv_roller_get_selected(ui_rollSoundTheme);
    // Change theme
    setAudioTheme(themeid);
}

void evSoundVolumeChange() {
    int volumeid = lv_slider_get_value(ui_sldTempSoundVolume);
    
    // Change only label text
    setAudioVolumeLabel(volumeid);
}

void evSoundVolumeRelease() {
    int volumeid = lv_slider_get_value(ui_sldTempSoundVolume);
    // Change volume
    setAudioVolume(volumeid);
}