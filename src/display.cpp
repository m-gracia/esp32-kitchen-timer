#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include "display.h"
#include "ui.h"
#include "my_def.h"
#include "my_debug.h"

void initTouch() {
  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);
}

bool touch_has_signal() {
  return true;
}

bool touch_touched() {
  ts.read();
  if (ts.isTouched) {
#if defined(TOUCH_SWAP_XY)
    touch_last_x = map(ts.points[0].y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(ts.points[0].x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#else
    touch_last_x = map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#endif
    return true;
  } else {
    return false;
  }
}

bool touch_released() {
  return true;
}

void my_log_cb(lv_log_level_t level, const char * buf) {
  DEBUG_TFT_PRINTLN(buf);
}

/* Display flushing */
void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap) {
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    //if (LV_COLOR_16_SWAP) {
    //    size_t len = lv_area_get_size( area );
    //    lv_draw_sw_rgb565_swap( pixelmap, len );
    //}

    gfx->draw16bitRGBBitmap( area->x1, area->y1, (uint16_t*) pixelmap, w, h );

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read (lv_indev_t *indev_driver, lv_indev_data_t *data) {
    if ( touch_has_signal() ) {
        if ( touch_touched() ) {
            data->state = LV_INDEV_STATE_PR;
            /*Set the coordinates*/
            data->point.x = touch_last_x;
            data->point.y = touch_last_y;
        }
        else if ( touch_released() ) {
            data->state = LV_INDEV_STATE_REL;
        }
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
    delay(15);
}

/*Set tick routine needed for LVGL internal timings*/
static uint32_t my_tick_get_cb (void) { return millis(); }

void initDisplay(){
    // Init touch device
    initTouch();
    DEBUG_TFT_PRINTLN("TOUCH SETUP DONE");


    // Init Display
    gfx->begin(); //16000000
    DEBUG_TFT_PRINTLN("TFT SETUP DONE");
    gfx->fillScreen(BLACK);

    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);

    lv_init();
    DEBUG_TFT_PRINTLN("LV_INIT DONE");
    buf = (lv_color_t*) heap_caps_malloc( sizeof(lv_color_t) * screenWidth * screenHeight / LVGL_BUFFER_RATIO, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT );
    
    if (!buf) {
        DEBUG_TFT_PRINTLN("LVGL buf allocate failed!");
    } else {
        static lv_disp_t* disp;
        disp = lv_display_create( screenWidth, screenHeight );
        lv_display_set_buffers( disp, buf, NULL, SCREENBUFFER_SIZE_PIXELS * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL );
        lv_display_set_flush_cb( disp, my_disp_flush );

        static lv_indev_t* indev;
        indev = lv_indev_create();
        lv_indev_set_type( indev, LV_INDEV_TYPE_POINTER );
        lv_indev_set_read_cb( indev, my_touchpad_read );

        lv_tick_set_cb( my_tick_get_cb );

        lv_log_register_print_cb( my_log_cb );

        // lv_fs_file_t f;
        // lv_fs_res_t res = lv_fs_open(&f, "S:assets/ui_img_sun_png.bin", LV_FS_MODE_RD);
        // if(res == LV_FS_RES_OK) {
        //     Serial.println("LVGL puede abrir el archivo correctamente");
        //     lv_fs_close(&f);
        // } else {
        //     Serial.printf("LVGL NO puede abrir el archivo. Error: %d\n", res);
        // }

        DEBUG_TFT_PRINTLN("UI INIT START");
        ui_init();
        DEBUG_TFT_PRINTLN("UI INIT DONE");

        // Crear teclado personalizado
        // static const char * kb_map[] = {
        //   "1", "2", "3", LV_SYMBOL_BACKSPACE, "\n",
        //   "4", "5", "6", LV_SYMBOL_CLOSE, "\n",
        //   "7", "8", "9", NULL, "\n",
        //   ";", "0", LV_SYMBOL_OK
        // };
        // static const lv_buttonmatrix_ctrl_t kb_ctrl[] = {
        //   LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4,
        //   LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4,
        //   LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4,
        //   LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_2
        // };
        // lv_keyboard_set_map(ui_kbHomeTerraza, LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
        // lv_keyboard_set_mode(ui_kbHomeTerraza, LV_KEYBOARD_MODE_USER_1);

    }
}