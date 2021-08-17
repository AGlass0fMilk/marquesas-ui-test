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

#ifndef MARQUESAS_UI_CIRCULARARRAY_HPP_
#define MARQUESAS_UI_CIRCULARARRAY_HPP_

template<typename T>
class CircularArray
{
public:

    CircularArray(int len) : _len(len) {
        _array = new T[len];
    }

    CircularArray(int len, T *array) : _len(len) {
        for(int i = 0; i < len; i++) {
            _array[i] = array[i];
        }
    }

    ~CircularArray() {
        delete[] _array;
    }

    T get(int index) {
        return _array[index];
    }

    void set(int index, T val) {
        _array[index] = val;
    }

    T operator [](int i) const { return _array[i%_len]; }

    T &operator [](int i) { return _array[i%_len]; }

    int get_current_index() {
        return _index;
    }

    void set_index(int index) {
        _index = index;
    }

    T next() {
        _index++;
        if(_index >= _len) {
            _index = 0;
        }
        return _array[_index];
    }

    T previous() {
        _index--;
        if(_index < 0) {
            _index = _len-1;
        }
        return _array[_index];
    }

    T current() {
        return _array[_index];
    }

    int size() const {
        return _len;
    }

protected:

    T *_array;

    int _len;

    int _index = 0;

};


#endif /* MARQUESAS_UI_CIRCULARARRAY_HPP_ */
