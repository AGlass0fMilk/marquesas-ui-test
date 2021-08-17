#ifndef TACH_UI_H
#define TACH_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

extern lv_obj_t * screen;
extern lv_obj_t * background;
extern lv_obj_t * screen_title_lbl;
extern lv_obj_t * rh_top_lbl;
extern lv_obj_t * lh_top_lbl;
extern lv_obj_t * trans_selector;
extern lv_obj_t * trans_park_lbl;
extern lv_obj_t * trans_reverse_lbl;
extern lv_obj_t * trans_neutral_lbl;
extern lv_obj_t * trans_drive_lbl;
extern lv_obj_t * trans_super_lbl;
extern lv_obj_t * trans_low_lbl;
extern lv_obj_t * trans_gears_lbl;
extern lv_obj_t * unleaded_lbl;
extern lv_obj_t * lh_indicators;
extern lv_obj_t * hi_beam_ind;
extern lv_obj_t * parking_lps_ind;
extern lv_obj_t * low_fuel_ind;
extern lv_obj_t * low_washer_ind;
extern lv_obj_t * low_tire_ind;
extern lv_obj_t * brake_cont;
extern lv_obj_t * brake_lbl;
extern lv_obj_t * parking_brake_ind;
extern lv_obj_t * brake_fail_ind;
extern lv_obj_t * air_susp_ind;
extern lv_obj_t * low_coolant_ind;
extern lv_obj_t * check_eng_ind;
extern lv_obj_t * rh_indicators;
extern lv_obj_t * oil_pressur_ind;
extern lv_obj_t * coolant_temp_ind;
extern lv_obj_t * Object3;
extern lv_obj_t * cc_set_ind;
extern lv_obj_t * cc_speed_lbl;
extern lv_obj_t * cc_units_lbl;
extern lv_obj_t * thermasan_ind;
extern lv_obj_t * Object5;


LV_IMG_DECLARE(img555923884);   // assets/high-beams-36.png
LV_IMG_DECLARE(img1626470228);   // assets/side-markers-32.png
LV_IMG_DECLARE(img_low_fuel_28_png);   // assets/low_fuel_28.png
LV_IMG_DECLARE(img1153826049);   // assets/washer-fluid-level-32.png
LV_IMG_DECLARE(img1653399208);   // assets/low-tire-pressure-32.png
LV_IMG_DECLARE(img_parking_brake_32_png);   // assets/parking_brake_32.png
LV_IMG_DECLARE(img1333670817);   // assets/brake-failure-32.png
LV_IMG_DECLARE(img759983515);   // assets/air-susp-32.png
LV_IMG_DECLARE(img195333120);   // assets/low-coolant-32.png
LV_IMG_DECLARE(img2134269875);   // assets/check-engine-no-exc-36.png
LV_IMG_DECLARE(img1349087550);   // assets/engine-oil-32.png
LV_IMG_DECLARE(img2089094994);   // assets/coolant-temp-32.png
LV_IMG_DECLARE(img_cruise_control_32_png);   // assets/cruise_control_32.png
LV_IMG_DECLARE(img871289747);   // assets/poop-32.png

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
