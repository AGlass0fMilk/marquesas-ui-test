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

#include "FadeBox.hpp"

#include "lvgl/lvgl.h"

using namespace marq;

/* Static C interface functions */
extern "C" {

static void fadebox_exec_cb(lv_anim_t *obj, lv_anim_value_t value) {
    ((FadeBox*)obj->user_data)->_fade(value);
}

static void fadebox_fade_out_done_cb(struct _lv_anim_t *a) {
    ((FadeBox*)a->user_data)->_on_fade_out_done(a);
}

static void fadebox_fade_in_done_cb(struct _lv_anim_t *a) {
    ((FadeBox*)a->user_data)->_on_fade_in_done(a);
}

}

FadeBox::FadeBox(lv_obj_t *box) : _box(box) {

    /* Start the container transparent */
    lv_obj_set_style_local_opa_scale(_box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

    lv_anim_init(&_anim);
    lv_anim_set_custom_exec_cb(&_anim, fadebox_exec_cb);

    /* User data is a pointer to the specific FadeBox instance for use by static C interface */
    _anim.user_data = this;

}

FadeBox::~FadeBox() {

}

void FadeBox::fade_to(Page *page, unsigned int speed_ms) {
    if(_fading) {
        LV_LOG_WARN("tried to fade while already fading");
        return;
    }

    /* If there is no current page, just fade in */
    if(!_current) {
        _next = page;
        _on_fade_out_done(&_anim);
    } else {
        /* Start the fade out animation */
        _next = page;
        lv_anim_set_time(&_anim, speed_ms);
        lv_anim_set_values(&_anim, 255, 0);
        _anim.ready_cb = fadebox_fade_out_done_cb;
        _fading = true;
        lv_anim_start(&_anim);
    }
}

void FadeBox::_fade(lv_anim_value_t value) {
//    LV_LOG_USER("Fade: %d", value);
    lv_obj_set_style_local_opa_scale(_box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, value);
}

void FadeBox::_on_fade_out_done(struct _lv_anim_t *anim) {
    LV_LOG_USER("fade out done");

    if(_current) {
        _current->undraw();
    }
    _current = _next;
    _current->draw(_box);
    lv_anim_set_values(&_anim, 0, 255);
    _anim.ready_cb = fadebox_fade_in_done_cb;
    lv_anim_start(&_anim);
}

void marq::FadeBox::set_page(Page *page) {
    if(_current) {
        _current->undraw();
    }
    _current = page;
    _current->draw(_box);
}

void FadeBox::_on_fade_in_done(struct _lv_anim_t *anim) {
    LV_LOG_USER("fade in done");
    _fading = false;
}
