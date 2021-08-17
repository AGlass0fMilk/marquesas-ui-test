#include "MainScreen.h"

#include "lvgl/lvgl.h"
#include "SpeedPage.hpp"
#include "FadeBox.hpp"
#include "NavigableMenu.hpp"

///////////////////// VARIABLES ////////////////////
extern "C" {
lv_obj_t * screen;
lv_obj_t * background;
lv_obj_t * screen_title_lbl;
lv_obj_t * rh_top_lbl;
lv_obj_t * lh_top_lbl;
lv_obj_t * trans_selector;
lv_obj_t * trans_park_lbl;
lv_obj_t * trans_reverse_lbl;
lv_obj_t * trans_neutral_lbl;
lv_obj_t * trans_drive_lbl;
lv_obj_t * trans_super_lbl;
lv_obj_t * trans_low_lbl;
lv_obj_t * unleaded_lbl;
lv_obj_t * lh_indicators;
lv_obj_t * hi_beam_ind;
lv_obj_t * parking_lps_ind;
lv_obj_t * low_fuel_ind;
lv_obj_t * low_washer_ind;
lv_obj_t * low_tire_ind;
lv_obj_t * brake_cont;
lv_obj_t * brake_lbl;
lv_obj_t * parking_brake_ind;
lv_obj_t * brake_fail_ind;
lv_obj_t * air_susp_ind;
lv_obj_t * low_coolant_ind;
lv_obj_t * check_eng_ind;
lv_obj_t * rh_indicators;
lv_obj_t * oil_pressur_ind;
lv_obj_t * coolant_temp_ind;
lv_obj_t * Object3;
lv_obj_t * cc_set_ind;
lv_obj_t * cc_speed_lbl;
lv_obj_t * cc_units_lbl;
lv_obj_t * thermasan_ind;
lv_obj_t * Object5;

///////////////////// FUNCTIONS ////////////////////

lv_font_t * title_bar_font = &lv_font_montserrat_28;
lv_font_t * trans_prnd_font = &lv_font_montserrat_36;


extern lv_font_t summer_of_76;
extern lv_font_t enough_light_120;
extern lv_font_t enough_120;
extern lv_font_t enough_200;
extern lv_font_t enough_80;

///////////////////// IMAGES ////////////////////
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
}

///////////////////// FUNCTIONS ////////////////////
#define BAR_PROPERTY_VALUE 0
#define BAR_PROPERTY_VALUE_WITH_ANIM 1

static const char category_1_title[] = "Speedometer";
static const char category_2_title[] = "Vehicle Info";
static CircularArray<marq::Page*> category_1_pages(2);
static CircularArray<marq::Page*> category_2_pages(2);
static marq::NavigableMenu::CategoryCollection categories(2);
static marq::NavigableMenu *menu;

extern "C" {

void SetBarProperty(lv_obj_t * target, int id, int val)
{
    if(id == BAR_PROPERTY_VALUE_WITH_ANIM) lv_bar_set_value(target, val, LV_ANIM_ON);
    if(id == BAR_PROPERTY_VALUE) lv_bar_set_value(target, val, LV_ANIM_OFF);
}

#define BASIC_PROPERTY_POSITION_X 0
#define BASIC_PROPERTY_POSITION_Y 1
#define BASIC_PROPERTY_WIDTH 2
#define BASIC_PROPERTY_HEIGHT 3
#define BASIC_PROPERTY_CLICKABLE 4
#define BASIC_PROPERTY_HIDDEN 5
#define BASIC_PROPERTY_DRAGABLE 6
#define BASIC_PROPERTY_DISABLED 7

void SetBasicProperty(lv_obj_t * target, int id, int val)
{
    if(id == BASIC_PROPERTY_POSITION_X) lv_obj_set_x(target, val);
    if(id == BASIC_PROPERTY_POSITION_Y) lv_obj_set_y(target, val);
    if(id == BASIC_PROPERTY_WIDTH) lv_obj_set_width(target, val);
    if(id == BASIC_PROPERTY_HEIGHT) lv_obj_set_height(target, val);
}

void SetBasicPropertyB(lv_obj_t * target, int id, bool val)
{
    if(id == BASIC_PROPERTY_CLICKABLE) lv_obj_set_click(target, val);
    if(id == BASIC_PROPERTY_HIDDEN) lv_obj_set_hidden(target, val);
    if(id == BASIC_PROPERTY_DRAGABLE) lv_obj_set_drag(target, val);
    if(id == BASIC_PROPERTY_DISABLED) {
        if(val) lv_obj_add_state(target, LV_STATE_DISABLED);
        else lv_obj_clear_state(target, LV_STATE_DISABLED);
    }
}

#define BUTTON_PROPERTY_TOGGLE 0
#define BUTTON_PROPERTY_CHECKED 1

void SetButtonProperty(lv_obj_t * target, int id, bool val)
{
    if(id == BUTTON_PROPERTY_TOGGLE) lv_btn_toggle(target);
    if(id == BUTTON_PROPERTY_CHECKED) lv_btn_set_state(target, val ? LV_BTN_STATE_CHECKED_RELEASED : LV_BTN_STATE_RELEASED);
}

#define DROPDOWN_PROPERTY_SELECTED 0

void SetDropdownProperty(lv_obj_t * target, int id, int val)
{
    if(id == DROPDOWN_PROPERTY_SELECTED) lv_dropdown_set_selected(target, val);
}

#define IMAGE_PROPERTY_IMAGE 0

void SetImageProperty(lv_obj_t * target, int id, uint8_t * val)
{
    if(id == IMAGE_PROPERTY_IMAGE) lv_img_set_src(target, val);
}

#define LABEL_PROPERTY_TEXT 0

void SetLabelProperty(lv_obj_t * target, int id, char * val)
{
    if(id == LABEL_PROPERTY_TEXT) lv_label_set_text(target, val);
}

#define ROLLER_PROPERTY_SELECTED 0
#define ROLLER_PROPERTY_SELECTED_WITH_ANIM 1

void SetRollerProperty(lv_obj_t * target, int id, int val)
{
    if(id == ROLLER_PROPERTY_SELECTED_WITH_ANIM) lv_roller_set_selected(target, val, LV_ANIM_ON);
    if(id == ROLLER_PROPERTY_SELECTED) lv_roller_set_selected(target, val, LV_ANIM_OFF);
}

#define SLIDER_PROPERTY_VALUE 0
#define SLIDER_PROPERTY_VALUE_WITH_ANIM 1

void SetSliderProperty(lv_obj_t * target, int id, int val)
{
    if(id == SLIDER_PROPERTY_VALUE_WITH_ANIM) lv_slider_set_value(target, val, LV_ANIM_ON);
    if(id == SLIDER_PROPERTY_VALUE) lv_slider_set_value(target, val, LV_ANIM_OFF);
}

//void ChangeScreen(lv_obj_t * target, int fademode, int spd, int delay)
//{
//    lv_scr_load_anim(target, fademode, spd, delay, false);
//}

void SetOpacity(lv_obj_t * target, int val)
{
    lv_obj_set_style_local_opa_scale(target, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, val);
}

//void anim_callback_set_x(lv_anim_t * a, lv_anim_value_t v)
//{
//    lv_obj_set_x(a->user_data, v);
//}
//
//void anim_callback_set_y(lv_anim_t * a, lv_anim_value_t v)
//{
//    lv_obj_set_y(a->user_data, v);
//}

//void anim_callback_set_width(lv_anim_t * a, lv_anim_value_t v)
//{
//    lv_obj_set_width(a->user_data, v);
//}
//
//void anim_callback_set_height(lv_anim_t * a, lv_anim_value_t v)
//{
//    lv_obj_set_height(a->user_data, v);
//}

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS2 ////////////////////
static void Object3_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void Object5_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}

///////////////////// SCREENS ////////////////////
void BuildPages(void)
{
    screen = lv_obj_create(NULL, NULL);
//    lv_obj_set_signal_cb(screen, on_key_pad_input);

    background = lv_obj_create(screen, NULL);
    lv_obj_set_click(background, false);
    lv_obj_set_hidden(background, false);
    lv_obj_clear_state(background, LV_STATE_DISABLED);
    lv_obj_set_size(background, LV_HOR_RES, LV_VER_RES);  // force: 0
    lv_obj_align(background, screen, LV_ALIGN_IN_TOP_LEFT, 0, 0); // force: 480
    lv_obj_set_drag(background, false);
    lv_obj_set_style_local_bg_color(background, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(29 * 256 * 256 + 29 * 256 + 29));
    lv_obj_set_style_local_bg_opa(background, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);

    screen_title_lbl = lv_label_create(screen, NULL);
    lv_label_set_long_mode(screen_title_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(screen_title_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(screen_title_lbl, "VEHICLE INFO");
    lv_obj_set_size(screen_title_lbl, 101, 26);  // force: 0
    lv_obj_set_click(screen_title_lbl, false);
    lv_obj_set_hidden(screen_title_lbl, false);
    lv_obj_clear_state(screen_title_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(screen_title_lbl, false);
    lv_obj_set_style_local_text_color(screen_title_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(243 * 256 * 256 + 243 * 256 + 243));
    lv_obj_set_style_local_text_opa(screen_title_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_pad_left(screen_title_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(screen_title_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_top(screen_title_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_bottom(screen_title_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_text_font(screen_title_lbl, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_28);

    lv_obj_align(screen_title_lbl, screen, LV_ALIGN_IN_TOP_MID, 0, 0); // force: 101

    rh_top_lbl = lv_label_create(screen, NULL);
    lv_label_set_long_mode(rh_top_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(rh_top_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(rh_top_lbl, "12:00 AM");
    lv_obj_set_size(rh_top_lbl, 71, 26);  // force: 0
    lv_obj_set_click(rh_top_lbl, false);
    lv_obj_set_hidden(rh_top_lbl, false);
    lv_obj_clear_state(rh_top_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(rh_top_lbl, false);
    lv_obj_set_style_local_text_color(rh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(243 * 256 * 256 + 243 * 256 + 243));
    lv_obj_set_style_local_text_opa(rh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_pad_left(rh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(rh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_top(rh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_bottom(rh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    lv_obj_align(rh_top_lbl, screen, LV_ALIGN_IN_TOP_RIGHT, 0, 0); // force: 71

    lh_top_lbl = lv_label_create(screen, NULL);
    lv_label_set_long_mode(lh_top_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(lh_top_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(lh_top_lbl, "73 °F");
    lv_obj_set_size(lh_top_lbl, 46, 26);  // force: 0
    lv_obj_set_click(lh_top_lbl, false);
    lv_obj_set_hidden(lh_top_lbl, false);
    lv_obj_clear_state(lh_top_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(lh_top_lbl, false);
    lv_obj_set_style_local_text_color(lh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(243 * 256 * 256 + 243 * 256 + 243));
    lv_obj_set_style_local_text_opa(lh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_pad_left(lh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_right(lh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_pad_top(lh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_bottom(lh_top_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    lv_obj_align(lh_top_lbl, screen, LV_ALIGN_IN_TOP_LEFT, 0, 0); // force: 46

    trans_selector = lv_obj_create(screen, NULL);
    lv_obj_set_click(trans_selector, false);
    lv_obj_set_hidden(trans_selector, false);
    lv_obj_clear_state(trans_selector, LV_STATE_DISABLED);
    lv_obj_set_size(trans_selector, 163, 31);  // force: 0
    lv_obj_align(trans_selector, screen, LV_ALIGN_IN_BOTTOM_MID, 0, -12); // force: 163
    lv_obj_set_drag(trans_selector, false);
    lv_obj_set_style_local_bg_color(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_bg_opa(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 2);
    lv_obj_set_style_local_border_color(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_border_opa(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_left(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_top(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_bottom(trans_selector, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    trans_park_lbl = lv_label_create(trans_selector, NULL);
    lv_label_set_long_mode(trans_park_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(trans_park_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(trans_park_lbl, "P");
    lv_obj_set_size(trans_park_lbl, 19, 29);  // force: 0
    lv_obj_set_click(trans_park_lbl, false);
    lv_obj_set_hidden(trans_park_lbl, false);
    lv_obj_clear_state(trans_park_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(trans_park_lbl, false);
    lv_obj_set_style_local_text_font(trans_park_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    lv_obj_align(trans_park_lbl, trans_selector, LV_ALIGN_IN_LEFT_MID, 0, 0); // force: 19

    trans_reverse_lbl = lv_label_create(trans_selector, NULL);
    lv_label_set_long_mode(trans_reverse_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(trans_reverse_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(trans_reverse_lbl, "R");
    lv_obj_set_size(trans_reverse_lbl, 19, 29);  // force: 30
    lv_obj_set_click(trans_reverse_lbl, false);
    lv_obj_set_hidden(trans_reverse_lbl, false);
    lv_obj_clear_state(trans_reverse_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(trans_reverse_lbl, false);
    lv_obj_set_style_local_text_color(trans_reverse_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(219 * 256 * 256 + 219 * 256 + 219));
    lv_obj_set_style_local_text_opa(trans_reverse_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(trans_reverse_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    lv_obj_align(trans_reverse_lbl, trans_selector, LV_ALIGN_IN_LEFT_MID, 30, 0); // force: 19

    trans_neutral_lbl = lv_label_create(trans_selector, NULL);
    lv_label_set_long_mode(trans_neutral_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(trans_neutral_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(trans_neutral_lbl, "N");
    lv_obj_set_size(trans_neutral_lbl, 21, 29);  // force: 60
    lv_obj_set_click(trans_neutral_lbl, false);
    lv_obj_set_hidden(trans_neutral_lbl, false);
    lv_obj_clear_state(trans_neutral_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(trans_neutral_lbl, false);
    lv_obj_set_style_local_text_font(trans_neutral_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    lv_obj_align(trans_neutral_lbl, trans_selector, LV_ALIGN_IN_LEFT_MID, 60, 0); // force: 21

    trans_drive_lbl = lv_label_create(trans_selector, NULL);
    lv_label_set_long_mode(trans_drive_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(trans_drive_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(trans_drive_lbl, "D");
    lv_obj_set_size(trans_drive_lbl, 22, 29);  // force: 90
    lv_obj_set_click(trans_drive_lbl, false);
    lv_obj_set_hidden(trans_drive_lbl, false);
    lv_obj_clear_state(trans_drive_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(trans_drive_lbl, false);
    lv_obj_set_style_local_text_font(trans_drive_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    lv_obj_align(trans_drive_lbl, trans_selector, LV_ALIGN_IN_LEFT_MID, 90, 0); // force: 22

    trans_super_lbl = lv_label_create(trans_selector, NULL);
    lv_label_set_long_mode(trans_super_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(trans_super_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(trans_super_lbl, "S");
    lv_obj_set_size(trans_super_lbl, 16, 29);  // force: 120
    lv_obj_set_click(trans_super_lbl, false);
    lv_obj_set_hidden(trans_super_lbl, false);
    lv_obj_clear_state(trans_super_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(trans_super_lbl, false);
    lv_obj_set_style_local_text_font(trans_super_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    lv_obj_align(trans_super_lbl, trans_selector, LV_ALIGN_IN_LEFT_MID, 120, 0); // force: 16

    trans_low_lbl = lv_label_create(trans_selector, NULL);
    lv_label_set_long_mode(trans_low_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(trans_low_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(trans_low_lbl, "L");
    lv_obj_set_size(trans_low_lbl, 15, 29);  // force: 150
    lv_obj_set_click(trans_low_lbl, false);
    lv_obj_set_hidden(trans_low_lbl, false);
    lv_obj_clear_state(trans_low_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(trans_low_lbl, false);
    lv_obj_set_style_local_text_font(trans_low_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_26);

    lv_obj_align(trans_low_lbl, trans_selector, LV_ALIGN_IN_LEFT_MID, 150, 0); // force: 15

    unleaded_lbl = lv_label_create(screen, NULL);
    lv_label_set_long_mode(unleaded_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(unleaded_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(unleaded_lbl, "UNLEADED FUEL ONLY");
    lv_obj_set_size(unleaded_lbl, 166, 16);  // force: 0
    lv_obj_set_click(unleaded_lbl, false);
    lv_obj_set_hidden(unleaded_lbl, false);
    lv_obj_clear_state(unleaded_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(unleaded_lbl, false);
    lv_obj_set_style_local_text_color(unleaded_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(132 * 256 * 256 + 132 * 256 + 132));
    lv_obj_set_style_local_text_opa(unleaded_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_align(unleaded_lbl, screen, LV_ALIGN_CENTER, 0, 100); // force: 166

    lh_indicators = lv_obj_create(screen, NULL);
    lv_obj_set_click(lh_indicators, false);
    lv_obj_set_hidden(lh_indicators, false);
    lv_obj_clear_state(lh_indicators, LV_STATE_DISABLED);
    lv_obj_set_size(lh_indicators, 76, 272);  // force: 10
    lv_obj_align(lh_indicators, screen, LV_ALIGN_IN_LEFT_MID, 10, 15); // force: 76
    lv_obj_set_drag(lh_indicators, false);
    lv_obj_set_style_local_bg_color(lh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_bg_opa(lh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_color(lh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_border_opa(lh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    hi_beam_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(hi_beam_ind, &img555923884);
    lv_obj_set_click(hi_beam_ind, false);
    lv_obj_set_hidden(hi_beam_ind, false);
    lv_obj_set_size(hi_beam_ind, 36, 22);
    lv_obj_align(hi_beam_ind, lh_indicators, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
    lv_obj_set_drag(hi_beam_ind, false);
    lv_obj_set_style_local_image_recolor(hi_beam_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(0 * 256 * 256 + 76 * 256 + 255));
    lv_obj_set_style_local_image_recolor_opa(hi_beam_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(hi_beam_ind, LV_STATE_DISABLED);

    parking_lps_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(parking_lps_ind, &img1626470228);
    lv_obj_set_click(parking_lps_ind, false);
    lv_obj_set_hidden(parking_lps_ind, false);
    lv_obj_set_size(parking_lps_ind, 32, 17);
    lv_obj_align(parking_lps_ind, lh_indicators, LV_ALIGN_IN_TOP_LEFT, 0, 30);
    lv_obj_set_drag(parking_lps_ind, false);
    lv_obj_set_style_local_image_recolor(parking_lps_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(47 * 256 * 256 + 214 * 256 + 22));
    lv_obj_set_style_local_image_recolor_opa(parking_lps_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(parking_lps_ind, LV_STATE_DISABLED);

    low_fuel_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(low_fuel_ind, &img_low_fuel_28_png);
    lv_obj_set_click(low_fuel_ind, false);
    lv_obj_set_hidden(low_fuel_ind, false);
    lv_obj_set_size(low_fuel_ind, 28, 29);
    lv_obj_align(low_fuel_ind, lh_indicators, LV_ALIGN_IN_TOP_RIGHT, 0, 50);
    lv_obj_set_drag(low_fuel_ind, false);
    lv_obj_set_style_local_image_recolor(low_fuel_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(255 * 256 * 256 + 192 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(low_fuel_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(low_fuel_ind, LV_STATE_DISABLED);

    low_washer_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(low_washer_ind, &img1153826049);
    lv_obj_set_click(low_washer_ind, false);
    lv_obj_set_hidden(low_washer_ind, false);
    lv_obj_set_size(low_washer_ind, 32, 25);
    lv_obj_align(low_washer_ind, lh_indicators, LV_ALIGN_IN_TOP_LEFT, 0, 80);
    lv_obj_set_drag(low_washer_ind, false);
    lv_obj_set_style_local_image_recolor(low_washer_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(255 * 256 * 256 + 192 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(low_washer_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(low_washer_ind, LV_STATE_DISABLED);

    low_tire_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(low_tire_ind, &img1653399208);
    lv_obj_set_click(low_tire_ind, false);
    lv_obj_set_hidden(low_tire_ind, false);
    lv_obj_set_size(low_tire_ind, 32, 31);
    lv_obj_align(low_tire_ind, lh_indicators, LV_ALIGN_IN_TOP_RIGHT, 0, 100);
    lv_obj_set_drag(low_tire_ind, false);
    lv_obj_set_style_local_image_recolor(low_tire_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(255 * 256 * 256 + 192 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(low_tire_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(low_tire_ind, LV_STATE_DISABLED);

    brake_cont = lv_obj_create(lh_indicators, NULL);
    lv_obj_set_click(brake_cont, false);
    lv_obj_set_hidden(brake_cont, false);
    lv_obj_clear_state(brake_cont, LV_STATE_DISABLED);
    lv_obj_set_size(brake_cont, 73, 50);  // force: 0
    lv_obj_align(brake_cont, lh_indicators, LV_ALIGN_IN_BOTTOM_MID, 0, 1); // force: 73
    lv_obj_set_drag(brake_cont, false);
    lv_obj_set_style_local_bg_color(brake_cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_bg_opa(brake_cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_color(brake_cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_border_opa(brake_cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    brake_lbl = lv_label_create(brake_cont, NULL);
    lv_label_set_long_mode(brake_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(brake_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(brake_lbl, "BRAKE");
    lv_obj_set_size(brake_lbl, 50, 16);  // force: 0
    lv_obj_set_click(brake_lbl, false);
    lv_obj_set_hidden(brake_lbl, false);
    lv_obj_clear_state(brake_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(brake_lbl, false);
    lv_obj_set_style_local_text_color(brake_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(249 * 256 * 256 + 4 * 256 + 1));
    lv_obj_set_style_local_text_opa(brake_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(brake_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_14);

    lv_obj_align(brake_lbl, brake_cont, LV_ALIGN_CENTER, 0, 19); // force: 50

    parking_brake_ind = lv_img_create(brake_cont, NULL);
    lv_img_set_src(parking_brake_ind, &img_parking_brake_32_png);
    lv_obj_set_click(parking_brake_ind, false);
    lv_obj_set_hidden(parking_brake_ind, false);
    lv_obj_set_size(parking_brake_ind, 32, 25);
    lv_obj_align(parking_brake_ind, brake_cont, LV_ALIGN_IN_TOP_MID, -20, 10);
    lv_obj_set_drag(parking_brake_ind, true);
    lv_obj_set_style_local_image_recolor(parking_brake_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(249 * 256 * 256 + 4 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(parking_brake_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(parking_brake_ind, LV_STATE_DISABLED);

    brake_fail_ind = lv_img_create(brake_cont, NULL);
    lv_img_set_src(brake_fail_ind, &img1333670817);
    lv_obj_set_click(brake_fail_ind, false);
    lv_obj_set_hidden(brake_fail_ind, false);
    lv_obj_set_size(brake_fail_ind, 32, 25);
    lv_obj_align(brake_fail_ind, brake_cont, LV_ALIGN_IN_TOP_MID, 20, 10);
    lv_obj_set_drag(brake_fail_ind, false);
    lv_obj_set_style_local_image_recolor(brake_fail_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(249 * 256 * 256 + 4 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(brake_fail_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(brake_fail_ind, LV_STATE_DISABLED);

    air_susp_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(air_susp_ind, &img759983515);
    lv_obj_set_click(air_susp_ind, false);
    lv_obj_set_hidden(air_susp_ind, false);
    lv_obj_set_size(air_susp_ind, 32, 22);
    lv_obj_align(air_susp_ind, lh_indicators, LV_ALIGN_IN_TOP_LEFT, 0, 130);
    lv_obj_set_drag(air_susp_ind, false);
    lv_obj_set_style_local_image_recolor(air_susp_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(255 * 256 * 256 + 192 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(air_susp_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(air_susp_ind, LV_STATE_DISABLED);

    low_coolant_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(low_coolant_ind, &img195333120);
    lv_obj_set_click(low_coolant_ind, false);
    lv_obj_set_hidden(low_coolant_ind, false);
    lv_obj_set_size(low_coolant_ind, 32, 34);
    lv_obj_align(low_coolant_ind, lh_indicators, LV_ALIGN_IN_TOP_RIGHT, 0, 150);
    lv_obj_set_drag(low_coolant_ind, false);
    lv_obj_set_style_local_image_recolor(low_coolant_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(255 * 256 * 256 + 192 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(low_coolant_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(low_coolant_ind, LV_STATE_DISABLED);

    check_eng_ind = lv_img_create(lh_indicators, NULL);
    lv_img_set_src(check_eng_ind, &img2134269875);
    lv_obj_set_click(check_eng_ind, false);
    lv_obj_set_hidden(check_eng_ind, false);
    lv_obj_set_size(check_eng_ind, 36, 24);
    lv_obj_align(check_eng_ind, lh_indicators, LV_ALIGN_IN_TOP_LEFT, 0, 180);
    lv_obj_set_drag(check_eng_ind, false);
    lv_obj_set_style_local_image_recolor(check_eng_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(255 * 256 * 256 + 192 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(check_eng_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(check_eng_ind, LV_STATE_DISABLED);

    rh_indicators = lv_obj_create(screen, NULL);
    lv_obj_set_click(rh_indicators, false);
    lv_obj_set_hidden(rh_indicators, false);
    lv_obj_clear_state(rh_indicators, LV_STATE_DISABLED);
    lv_obj_set_size(rh_indicators, 95, 259);  // force: -3
    lv_obj_align(rh_indicators, screen, LV_ALIGN_IN_RIGHT_MID, -3, 12); // force: 95
    lv_obj_set_drag(rh_indicators, false);
    lv_obj_set_style_local_bg_color(rh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_bg_opa(rh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_color(rh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_border_opa(rh_indicators, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    oil_pressur_ind = lv_img_create(rh_indicators, NULL);
    lv_img_set_src(oil_pressur_ind, &img1349087550);
    lv_obj_set_click(oil_pressur_ind, false);
    lv_obj_set_hidden(oil_pressur_ind, false);
    lv_obj_set_size(oil_pressur_ind, 32, 12);
    lv_obj_align(oil_pressur_ind, rh_indicators, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_drag(oil_pressur_ind, false);
    lv_obj_set_style_local_image_recolor(oil_pressur_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(249 * 256 * 256 + 4 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(oil_pressur_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(oil_pressur_ind, LV_STATE_DISABLED);

    coolant_temp_ind = lv_img_create(rh_indicators, NULL);
    lv_img_set_src(coolant_temp_ind, &img2089094994);
    lv_obj_set_click(coolant_temp_ind, false);
    lv_obj_set_hidden(coolant_temp_ind, false);
    lv_obj_set_size(coolant_temp_ind, 32, 29);
    lv_obj_align(coolant_temp_ind, rh_indicators, LV_ALIGN_CENTER, 0, 50);
    lv_obj_set_drag(coolant_temp_ind, false);
    lv_obj_set_style_local_image_recolor(coolant_temp_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(249 * 256 * 256 + 4 * 256 + 1));
    lv_obj_set_style_local_image_recolor_opa(coolant_temp_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(coolant_temp_ind, LV_STATE_DISABLED);

    Object3 = lv_obj_create(rh_indicators, NULL);
    lv_obj_set_click(Object3, true);
    lv_obj_set_hidden(Object3, false);
    lv_obj_clear_state(Object3, LV_STATE_DISABLED);
    lv_obj_set_size(Object3, 99, 59);  // force: -10
    lv_obj_align(Object3, rh_indicators, LV_ALIGN_IN_TOP_LEFT, -10, 10); // force: 99
    lv_obj_set_drag(Object3, false);
    lv_obj_set_event_cb(Object3, Object3_eventhandler);
    lv_obj_set_style_local_bg_color(Object3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_bg_opa(Object3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_color(Object3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_border_opa(Object3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    cc_set_ind = lv_img_create(Object3, NULL);
    lv_img_set_src(cc_set_ind, &img_cruise_control_32_png);
    lv_obj_set_click(cc_set_ind, false);
    lv_obj_set_hidden(cc_set_ind, false);
    lv_obj_set_size(cc_set_ind, 32, 29);
    lv_obj_align(cc_set_ind, Object3, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_drag(cc_set_ind, false);
    lv_obj_set_style_local_image_recolor(cc_set_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(47 * 256 * 256 + 214 * 256 + 22));
    lv_obj_set_style_local_image_recolor_opa(cc_set_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

    lv_obj_clear_state(cc_set_ind, LV_STATE_DISABLED);

    cc_speed_lbl = lv_label_create(Object3, NULL);
    lv_label_set_long_mode(cc_speed_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(cc_speed_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(cc_speed_lbl, "72");
    lv_obj_set_size(cc_speed_lbl, 24, 22);  // force: -5
    lv_obj_set_click(cc_speed_lbl, false);
    lv_obj_set_hidden(cc_speed_lbl, false);
    lv_obj_clear_state(cc_speed_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(cc_speed_lbl, false);
    lv_obj_set_style_local_text_color(cc_speed_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(215 * 256 * 256 + 215 * 256 + 215));
    lv_obj_set_style_local_text_opa(cc_speed_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(cc_speed_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    lv_obj_align(cc_speed_lbl, Object3, LV_ALIGN_IN_RIGHT_MID, -5, -4); // force: 24

    cc_units_lbl = lv_label_create(Object3, NULL);
    lv_label_set_long_mode(cc_units_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(cc_units_lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(cc_units_lbl, "MPH");
    lv_obj_set_size(cc_units_lbl, 30, 15);  // force: -2
    lv_obj_set_click(cc_units_lbl, false);
    lv_obj_set_hidden(cc_units_lbl, false);
    lv_obj_clear_state(cc_units_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(cc_units_lbl, false);
    lv_obj_set_style_local_text_color(cc_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(215 * 256 * 256 + 215 * 256 + 215));
    lv_obj_set_style_local_text_opa(cc_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(cc_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_12);

    lv_obj_align(cc_units_lbl, Object3, LV_ALIGN_IN_RIGHT_MID, -2, 10); // force: 30

//    thermasan_ind = lv_img_create(rh_indicators, NULL);
//    lv_img_set_src(thermasan_ind, &img871289747);
//    lv_obj_set_click(thermasan_ind, false);
//    lv_obj_set_hidden(thermasan_ind, false);
//    lv_obj_set_size(thermasan_ind, 32, 31);
//    lv_obj_align(thermasan_ind, rh_indicators, LV_ALIGN_CENTER, 0, 100);
//    lv_obj_set_drag(thermasan_ind, false);
//    lv_obj_set_style_local_image_recolor(thermasan_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
//                                         lv_color_hex(96 * 256 * 256 + 69 * 256 + 4));
//    lv_obj_set_style_local_image_recolor_opa(thermasan_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);
//
//    lv_obj_clear_state(thermasan_ind, LV_STATE_DISABLED);

    Object5 = lv_obj_create(screen, NULL);
    lv_obj_set_click(Object5, true);
    lv_obj_set_hidden(Object5, false);
    lv_obj_clear_state(Object5, LV_STATE_DISABLED);
    lv_obj_set_size(Object5, 480, 300);  // force: 0
    lv_obj_align(Object5, screen, LV_ALIGN_CENTER, 0, -25); // force: 252
    lv_obj_set_drag(Object5, false);
    lv_obj_set_event_cb(Object5, Object5_eventhandler);
    lv_obj_set_style_local_border_opa(Object5, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_opa(Object5, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

//    thermasan_ind = lv_img_create(Object5, NULL);
//    lv_img_set_src(thermasan_ind, &img871289747);
//    lv_obj_set_click(thermasan_ind, false);
//    lv_obj_set_hidden(thermasan_ind, false);
//    lv_obj_set_size(thermasan_ind, 32, 31);
//    lv_obj_align(thermasan_ind, Object5, LV_ALIGN_CENTER, 0, 0);
//    lv_obj_set_drag(thermasan_ind, false);
//    lv_obj_set_style_local_image_recolor(thermasan_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
//                                         lv_color_hex(96 * 256 * 256 + 69 * 256 + 4));
//    lv_obj_set_style_local_image_recolor_opa(thermasan_ind, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);
//
//    lv_obj_clear_state(thermasan_ind, LV_STATE_DISABLED);

//    page1 = new marq::SpeedPage();
//    page2 = new marq::SpeedPage();
//    page2->toggle_units();
//
//    fade_box = new marq::FadeBox(Object5);

    categories[0] = std::make_tuple(category_1_title, &category_1_pages);
    categories[1] = std::make_tuple(category_2_title, &category_2_pages);

    lv_color_t speed_text_color = lv_color_hex(0xE8E8E8E8);
    lv_color_t speed_text_color_2 = lv_color_hex(0xFF00FFFF);

    marq::SpeedPage *page1 = new marq::SpeedPage(&enough_200, &lv_font_montserrat_46, speed_text_color);
    page1->set_speed(0.0f);
    marq::SpeedPage *page2 = new marq::SpeedPage(&enough_200, &lv_font_montserrat_46, speed_text_color);
    page2->set_speed(10.0f);
    marq::SpeedPage *page3 = new marq::SpeedPage(&enough_200, &lv_font_montserrat_46, speed_text_color);
    page3->set_speed(100.0f);
    marq::SpeedPage *page4 = new marq::SpeedPage(&enough_200, &lv_font_montserrat_46, speed_text_color);
    page4->set_speed(250.0f);

    category_1_pages[0] = page1;
    category_1_pages[1] = page2;
    category_2_pages[0] = page3;
    category_2_pages[1] = page4;

    menu = new marq::NavigableMenu(Object5, &categories, 0, 0);


}

void navigate_up() {
    menu->navigate_up();
}

void navigate_down() {
    menu->navigate_down();
}

void navigate_left() {
    menu->navigate_left();
}

void navigate_right() {
    menu->navigate_right();
}

}

