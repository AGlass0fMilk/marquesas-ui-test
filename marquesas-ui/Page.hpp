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

#ifndef MARQUESAS_UI_PAGE_HPP_
#define MARQUESAS_UI_PAGE_HPP_

#include "lvgl/lvgl.h"

namespace marq
{

class Page {

public:

    Page() { }

    virtual ~Page() {
        undraw();
    }

    /* Draw the page to the given parent */
    void draw(lv_obj_t *parent) {
        if(_drawn) {
            LV_LOG_WARN("attempted to draw an already drawn Page");
            return;
        }

        _parent = parent;
        _draw(parent);
        _drawn = true;

    }

    /* Undraw the Page and clear the parent provided with draw of children
     * This releases all graphical assets allocated by this Page
     */
    void undraw() {
        if(!_drawn) {
            LV_LOG_WARN("attempted to undraw an undrawn Page");
            return;
        }

        _undraw();
        _drawn = false;
        _parent = nullptr;
    }

    bool is_drawn() const {
        return _drawn;
    }

protected:

    /* Internal draw function implemented by subclass */
    virtual void _draw(lv_obj_t *parent) = 0;

    /* Internal undraw function implemented by subclass */
    virtual void _undraw() = 0;

protected:

    lv_obj_t *_parent = nullptr;

    bool _drawn = false;

};

} /* namespace marq */

#endif /* MARQUESAS_UI_PAGE_HPP_ */
