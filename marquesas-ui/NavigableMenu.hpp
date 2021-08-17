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

#ifndef MARQUESAS_UI_NAVIGABLEMENU_HPP_
#define MARQUESAS_UI_NAVIGABLEMENU_HPP_

#include "CircularArray.hpp"
#include "Page.hpp"
#include "FadeBox.hpp"

#include "lvgl/lvgl.h"
#include <tuple>

namespace marq
{

/*
 * Class encapsulating the navigable menu in the center of the screen
 * The contents of this menu can be changed by the user
 */
class NavigableMenu
{
public:

    using CategoryCollection = CircularArray<std::tuple<const char*, CircularArray<Page*>*>>;

    /**
     * Create a navigable menu using the given container and collection of categories/pages
     */
    NavigableMenu(lv_obj_t *container, CategoryCollection *categories, int initial_category,
            int initial_page);

    void navigate_up();

    void navigate_down();

    void navigate_left();

    void navigate_right();

    /* Sets the absolute category/page (used for reloading) */
    void set_page_index(int category, int page);

    /* Gets the absolute category/page location */
    std::tuple<int, int> get_page_index();

    const char* get_current_title() const {
        return _current_title;
    }

protected:

    lv_obj_t *_container;

    /* Each category a circular array of pages */
    CategoryCollection *_categories;

    FadeBox _fadebox;

    const char *_current_title = nullptr;

};

} /* namespace marq */


#endif /* MARQUESAS_UI_NAVIGABLEMENU_HPP_ */
