///*
// * Copyright (c) 2021 George Beckstein
// * SPDX-License-Identifier: Apache-2.0
// *
// * Licensed under the Apache License, Version 2.0 (the "License");
// * you may not use this file except in compliance with the License.
// * You may obtain a copy of the License at
// *
// *     http://www.apache.org/licenses/LICENSE-2.0
// *
// * Unless required by applicable law or agreed to in writing, software
// * distributed under the License is distributed on an "AS IS" BASIS,
// * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// * See the License for the specific language governing permissions and
// * limitations under the License
// */
//
//#ifndef MARQUESAS_UI_MARQMENUCATEGORY_H_
//#define MARQUESAS_UI_MARQMENUCATEGORY_H_
//
//#include "MarqMenu.hpp"
//
///**
// * Encapsulates a category of MarqMenus that can be swapped between
// * The last selected menu is cached
// */
//class MarqMenuCategory : public MarqMenu
//{
//
//public:
//
//    /**
//     * Initialize a MarqMenuCategory. A pre-populated list of length len must be
//     * provided during initialization. This sets up the menu navigation order
//     */
//    MarqMenuCategory(const char *name, MarqMenu **menus, unsigned int len) : _name(name), _menus(menus),
//    _len(len) {
//
//    }
//
//    /** Navigate to the next MarqMenu on the left.
//     * @note If the index is at the extreme, it will roll over like a circular buffer
//     */
//    void navigate_left();
//
//    /** Navigate to the next MarqMenu on the right.
//     * @note If the index is at the extreme, it will roll over like a circular buffer
//     */
//    void navigate_right();
//
//    unsigned int get_current_index() const {
//        return _idx;
//    }
//
//    MarqMenu** get_menus() const {
//        return _menus;
//    }
//
//    const char* get_name() const {
//        return _name;
//    }
//
//protected:
//
//    /* Name of the category */
//    const char *_name;
//
//    /* List of pointers to MarqMenu instances of length len */
//    MarqMenu **_menus;
//
//    unsigned int _len;
//
//    int _idx = 0;
//
//};
//
//#endif /* MARQUESAS_UI_MARQMENUCATEGORY_H_ */
