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

#ifndef MARQUESAS_UI_GRADIENTMASK_HPP_
#define MARQUESAS_UI_GRADIENTMASK_HPP_

#include "lvgl/lvgl.h"

class GradientMask {

public:

    /**
     * Create a gradient that is masked
     * @param[in] area Area to put the masked gradient
     * @param[in]
     */
    GradientMask(lv_obj_t *area, lv_color_t color_1, lv_color_t color_2, lv_grad_dir_t grad_dir) : _area(area){
        _mask_map = new lv_opa_t[lv_obj_get_width(area) * lv_obj_get_height(area)];
        _om = lv_objmask_create(area, NULL);
        lv_obj_set_size(_om, lv_obj_get_width(area), lv_obj_get_height(area));
        lv_obj_align(_om, NULL, LV_ALIGN_CENTER, 0, 0);

        /*Create a style with gradient*/
        _grad_style = new lv_style_t;
        lv_style_init(_grad_style);
        lv_style_set_bg_opa(_grad_style, LV_STATE_DEFAULT, LV_OPA_COVER);
        lv_style_set_bg_color(_grad_style, LV_STATE_DEFAULT, color_1);
        lv_style_set_bg_grad_color(_grad_style, LV_STATE_DEFAULT, color_2);
        lv_style_set_bg_grad_dir(_grad_style, LV_STATE_DEFAULT, grad_dir);

    }

    ~GradientMask() {
        lv_obj_del(_om);
        delete[] _mask_map;
        delete _grad_style;
        lv_obj_del(_bg);
    }

    void set_mask_text(lv_coord_t x, lv_coord_t y, lv_coord_t max_w, const char * txt, lv_label_align_t align) {
        lv_draw_label_dsc_t label_draw_dsc;
        lv_draw_label_dsc_init(&label_draw_dsc);
        label_draw_dsc.color = LV_COLOR_WHITE;
        lv_obj_t *canvas = init_canvas();
        lv_canvas_draw_text(canvas, x, y, max_w, &label_draw_dsc, txt, align);
        lv_obj_del(canvas);
        update_mask();
    }

    void set_mask_image(lv_coord_t x, lv_coord_t y, const void *img, const lv_draw_img_dsc_t * img_desc) {
        lv_obj_t *canvas = init_canvas();
        lv_canvas_draw_img(canvas, x, y, img, img_desc);
        lv_obj_del(canvas);
        update_mask();
    }

protected:

    lv_obj_t *init_canvas() {
        /*Create a "8 bit alpha" canvas and clear it*/
        lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
        lv_canvas_set_buffer(canvas, _mask_map, lv_obj_get_width(_area), lv_obj_get_height(_area), LV_IMG_CF_ALPHA_8BIT);
        lv_canvas_fill_bg(canvas, LV_COLOR_BLACK, LV_OPA_TRANSP);
        return canvas;
    }

    void update_mask() {

        /*Add the created mask map to the object mask*/
        lv_draw_mask_map_param_t m;
        lv_area_t a;
        a.x1 = 0;
        a.y1 = 0;
        a.x2 = lv_obj_get_width(_area) - 1;
        a.y2 = lv_obj_get_height(_area) - 1;
        lv_draw_mask_map_init(&m, &a, _mask_map);
        lv_objmask_add_mask(_om, &m);

        /* Create and object with the gradient style on the object mask.
         * The text will be masked from the gradient*/
        if(_bg) {
            delete _bg;
        }
        _bg = lv_obj_create(_om, NULL);
        lv_obj_reset_style_list(_bg, LV_OBJ_PART_MAIN);
        lv_obj_add_style(_bg, LV_OBJ_PART_MAIN, _grad_style);
        lv_obj_set_size(_bg, lv_obj_get_width(_area), lv_obj_get_height(_area));
    }

protected:

    lv_obj_t *_area;
    lv_opa_t *_mask_map;
    lv_obj_t *_om;
    lv_style_t *_grad_style;
    lv_obj_t * _bg = nullptr;

};



#endif /* MARQUESAS_UI_GRADIENTMASK_HPP_ */
