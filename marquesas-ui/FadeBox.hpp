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

#ifndef MARQUESAS_UI_FADEBOX_HPP_
#define MARQUESAS_UI_FADEBOX_HPP_

#include "Page.hpp"

namespace marq
{

/** Container that fades from one Page to another */
class FadeBox
{
public:

    /* Create a FadeBox using the given container object */
    FadeBox(lv_obj_t *box);

    ~FadeBox();

    /**
     * Display a page immediately (typically used after initialization)
     */
    void set_page(Page *page);

    void fade_to(Page *page, unsigned int speed_ms);

//protected:

    /* Function called by animation
     * @note I could not figure out a good way to not make this public as it
     * is called by the C interface.
     *
     * A good solution to this would be Mbed's Callbacks but that would complicate
     * compatibility with the simulator.
     *
     * C++ Functors are another possible solution
     *
     * For now, note that this should not be called by the application!
     */
    void _fade(lv_anim_value_t value);

    /**
     * Called when the fade out animation is done
     * @note see the comments on _fade, this should not be called directly
     */
    void _on_fade_out_done(struct _lv_anim_t *anim);

    /**
     * Called when the fade in animation is done
     * @note see the comments on _fade, this should not be called directly
     */
    void _on_fade_in_done(struct _lv_anim_t *anim);

    bool is_fading() const {
        return _fading;
    }

protected:

    Page *_current = nullptr;
    Page *_next = nullptr;

    lv_obj_t *_box;
    lv_anim_t _anim;

    bool _fading = false;

};

} /* namespace marq */

#endif /* MARQUESAS_UI_FADEBOX_HPP_ */
