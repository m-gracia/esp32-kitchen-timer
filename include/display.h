/**
 * @file display.h
 *
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*UI_OUTER_H*/

void initTouch();
bool touch_has_signal();
bool touch_touched();
bool touch_released();
void my_log_cb(const char * buf);
void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap);
void my_touchpad_read (lv_indev_t *indev_driver, lv_indev_data_t *data);
static uint32_t my_tick_get_cb (void);
void initDisplay();