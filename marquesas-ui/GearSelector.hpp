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

#ifndef MARQUESAS_UI_GEARSELECTOR_HPP_
#define MARQUESAS_UI_GEARSELECTOR_HPP_

#include "lvgl/lvgl.h"

class GearSelector {

public:

    GearSelector(lv_obj_t* label, const char *gears, lv_color_t highlight_color) :
        _label(label), _gears(gears), _highlight_color(highlight_color) {
        set_selected_gear(_gears[0]);

    }

    void set_selected_gear(char gear) {

        lv_label_set_recolor(_label, true);

        /* Allow length for recolor directive */
        char *gear_str = new char[strlen(_gears)+16];

        /* Find the selected gear character */
        int index = 0;
        const char *selected_gear = strchr(_gears, gear);

        if(!selected_gear) {
            LV_LOG_ERROR("tried to select a gear that is unavailable");
            return;
        }

        index = (int)(selected_gear-_gears);
        memcpy(gear_str, _gears, index);
        sprintf(&gear_str[index], "#%06x %c#%s", (_highlight_color.full & 0xFFFFFF), gear, &_gears[index+1]);

        lv_label_set_text(_label, gear_str);

        delete[] gear_str;
    }

protected:

    /* Label to use for display */
    lv_obj_t *_label;

    /* String of gears that can be selected from */
    const char *_gears;

    /* Color to highlight the selected gear with */
    lv_color_t _highlight_color;

};

#endif /* MARQUESAS_UI_GEARSELECTOR_HPP_ */
