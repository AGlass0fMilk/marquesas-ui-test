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

#ifndef MARQUESAS_UI_SPEEDPAGE_HPP_
#define MARQUESAS_UI_SPEEDPAGE_HPP_

#include "Page.hpp"

namespace marq
{

/**
 * Page showing Speed in both miles/hour and km/hour
 */
class SpeedPage : public Page
{
public:

    /* Create a SpeedPage using the given font and text color */
    SpeedPage(lv_font_t *font, lv_font_t *units_font, lv_color_t color) : _font(font),
    _units_font(units_font), _color(color){ }

    virtual ~SpeedPage() { }

    /* Sets the speed in km/h. The speed will be displayed with the configured units */
    void set_speed(float speed_kmph);

    void toggle_units();

    void set_font(lv_font_t *font) {
        _font = font;
        update_display();
    }

    void set_text_color(lv_color_t color) {
        _color = color;
        update_display();
    }

protected:

    virtual void _draw(lv_obj_t *parent) override;

    virtual void _undraw() override;

    void update_display();

    /*
     * Calculate the speed (in imperial or SI) and apply filters
     * like hysteresis
     */
    int calc_speed();

protected:

    /* True if imperial units should be displayed, false if SI */
    bool _imperial_units = true;

    int _last_speed = 0;
    float _current_speed_kmph = 0.0f;

    lv_obj_t *_speed_lbl = nullptr;
    lv_obj_t *_units_lbl = nullptr;

    lv_font_t *_font;
    lv_font_t *_units_font;
    lv_color_t _color = LV_COLOR_BLACK;

};

} /* namespace marq */

#endif /* MARQUESAS_UI_SPEEDPAGE_HPP_ */
