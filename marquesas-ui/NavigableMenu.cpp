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

#include "NavigableMenu.hpp"

#define FADE_SPEED_MS 100

using namespace marq;

NavigableMenu::NavigableMenu(lv_obj_t *container, CategoryCollection *categories,
        int initial_category, int initial_page) : _container(container), _categories(categories),
                _fadebox(container) {
    set_page_index(initial_category, initial_page);
}

void NavigableMenu::navigate_up() {
    auto [ title, pages ] = _categories->previous();
    _current_title = title;
    _fadebox.fade_to(pages->current(), FADE_SPEED_MS);
}

void NavigableMenu::navigate_down() {
    auto [ title, pages ] = _categories->next();
    _current_title = title;
    _fadebox.fade_to(pages->current(), FADE_SPEED_MS);
}

void NavigableMenu::navigate_left() {
    auto [ title, pages ] = _categories->current();
    if(pages->size() > 1) {
        _fadebox.fade_to(pages->next(), FADE_SPEED_MS);
    }
}

void NavigableMenu::navigate_right() {
    auto [ title, pages ] = _categories->current();
    if(pages->size() > 1) {
        _fadebox.fade_to(pages->previous(), FADE_SPEED_MS);
    }
}

void NavigableMenu::set_page_index(int category, int page) {
    _categories->set_index(category);
    auto [ title, pages ] = _categories->current();
    _current_title = title;
    pages->set_index(page);
    _fadebox.fade_to(pages->current(), FADE_SPEED_MS);
}

std::tuple<int, int> NavigableMenu::get_page_index() {
    auto [ title, pages ] = _categories->current();
    return std::make_tuple(_categories->get_current_index(), pages->get_current_index());
}

