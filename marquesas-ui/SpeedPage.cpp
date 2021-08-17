/*
 * Copyright (c) 2021 George Beckstein
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 */

#include "SpeedPage.hpp"
#include <stdio.h>
#include <math.h>

using namespace marq;

// TODO add a gradient behind the text to make it look better?

void SpeedPage::_draw(lv_obj_t *parent) {

    if(_drawn) {
        LV_LOG_WARN("attempted to draw an already drawn Page")
        return;
    }

    _mask_map = new lv_opa_t[SPEEDPAGE_MAX_MASK_WIDTH*SPEEDPAGE_MAX_MASK_HEIGHT];

    _units_lbl = lv_label_create(parent, NULL);
    lv_label_set_long_mode(_units_lbl, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(_units_lbl, LV_LABEL_ALIGN_CENTER);
    lv_obj_set_size(_units_lbl, 101, 26);  // force: 0
    lv_obj_set_click(_units_lbl, false);
    lv_obj_set_hidden(_units_lbl, false);
    lv_obj_clear_state(_units_lbl, LV_STATE_DISABLED);
    lv_obj_set_drag(_units_lbl, false);
    lv_obj_set_style_local_text_color(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, _color);
    lv_obj_set_style_local_text_opa(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_pad_left(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_top(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_bottom(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_text_font(_units_lbl, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, _units_font);

    lv_obj_align(_units_lbl, parent, LV_ALIGN_CENTER, 0, 100); // force: 101

    /* Set this here because update display won't work without it */
    _drawn = true;

    update_display();

}

void SpeedPage::_undraw() {
    delete[] _mask_map;
    lv_obj_del(_units_lbl);
    if(_bg) {
        lv_obj_del(_bg);
        _bg = nullptr;
    }
    if(_om) {
        lv_obj_del(_om);
        _om = nullptr;
    }
}

void SpeedPage::set_speed(float speed_kmph) {
    _current_speed_kmph = speed_kmph;
    update_display();
}

void SpeedPage::toggle_units() {
    _imperial_units = !_imperial_units;
    update_display();
}

void SpeedPage::update_display() {
    if(_drawn) {
        char speed_str[8];
        // TODO add hysteresis (maybe even more complex processing?)

        /* Limit speed to three digits
         * (this code will hopefully be updated by the time standard street cars can go 1000 kmph)*/
        if(_current_speed_kmph > 999) {
            _current_speed_kmph = 999;
        }

        /* Update the speed label */
        sprintf(speed_str, "%d", calc_speed());

        /*Create a "8 bit alpha" canvas and clear it*/
        lv_obj_t * canvas = lv_canvas_create(_parent, NULL);
        lv_canvas_set_buffer(canvas, _mask_map, SPEEDPAGE_MAX_MASK_WIDTH,
                SPEEDPAGE_MAX_MASK_HEIGHT, LV_IMG_CF_ALPHA_8BIT);
        lv_canvas_fill_bg(canvas, LV_COLOR_BLACK, LV_OPA_TRANSP);

        /*Draw a label to the canvas. The result "image" will be used as mask*/
        lv_draw_label_dsc_t label_dsc;
        lv_draw_label_dsc_init(&label_dsc);
        label_dsc.color = LV_COLOR_WHITE;
        label_dsc.font = _font;
        lv_canvas_draw_text(canvas, 0, 0, SPEEDPAGE_MAX_MASK_WIDTH, &label_dsc, speed_str, LV_LABEL_ALIGN_CENTER);

        /*The mask is reads the canvas is not required anymore*/
        lv_obj_del(canvas);

        /*Create an object mask which will use the created mask*/
        if(_om) {
            lv_obj_del(_om);
            _om = nullptr;
        }

        _om = lv_objmask_create(_parent, NULL);
        lv_obj_set_size(_om, SPEEDPAGE_MAX_MASK_WIDTH, SPEEDPAGE_MAX_MASK_HEIGHT);
        lv_obj_align(_om, NULL, LV_ALIGN_CENTER, 0, 0);

        /*Add the created mask map to the object mask*/
        lv_draw_mask_map_param_t m;
        lv_area_t a;
        a.x1 = 0;
        a.y1 = 0;
        a.x2 = SPEEDPAGE_MAX_MASK_WIDTH - 1;
        a.y2 = SPEEDPAGE_MAX_MASK_HEIGHT - 1;
        lv_draw_mask_map_init(&m, &a, _mask_map);
        lv_objmask_add_mask(_om, &m);

        /*Create a style with gradient*/
        lv_style_init(&_grad_style_bg);
        lv_style_set_bg_opa(&_grad_style_bg, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_color(&_grad_style_bg, LV_STATE_DEFAULT, lv_color_hex(0xd6d1c3));
        lv_style_set_bg_grad_color(&_grad_style_bg, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_bg_grad_dir(&_grad_style_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

        /* Create and object with the gradient style on the object mask.
         * The text will be masked from the gradient*/
        if(_bg) {
            lv_obj_del(_bg);
            _bg = nullptr;
        }

        _bg = lv_obj_create(_om, NULL);
        lv_obj_reset_style_list(_bg, LV_OBJ_PART_MAIN);
        lv_obj_add_style(_bg, LV_OBJ_PART_MAIN, &_grad_style_bg);
        lv_obj_set_size(_bg, SPEEDPAGE_MAX_MASK_WIDTH, SPEEDPAGE_MAX_MASK_HEIGHT);

        /* Update the units label */
        lv_obj_set_style_local_text_color(_units_lbl, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, _color);
        lv_obj_set_style_local_text_font(_units_lbl, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, _units_font);
        if(_imperial_units) {
            lv_label_set_text(_units_lbl, "MPH");
        } else {
            lv_label_set_text(_units_lbl, "KMPH");
        }
        lv_obj_align(_units_lbl, NULL, LV_ALIGN_CENTER, 0, 75); // force: 101

    }
}

int SpeedPage::calc_speed() {

    float out = _current_speed_kmph;
    int retval = 0;

    /* First, determine if we must convert the output from KMPH to MPH */
    if(_imperial_units) {
        out /= 1.609f;
    }

    return roundf(out);

    /* TODO Apply hysteresis */
//    float last_speed = (float) _last_speed;
//    /* If the change was greater than 1, round the new value */
//    if(std::abs(last_speed - out) > 1.0f) {
//        retval = roundf(out);
//    } else {
//        float fractional, intpart;
//        fractional = std::modf(out, &intpart);
//
//        if(fractional >= 0.66f) {
//            out = intpart + 1.0f;
//        } else if(fractional <= 0.33f) {
//            out = intpart;
//        }
//    }
//
//    _last_speed = retval;
//    return retval;

}
