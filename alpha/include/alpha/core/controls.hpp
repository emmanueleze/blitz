// MIT License
//
// Copyright (c) 2021 Emmanuel Godwin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_CORE_CONTROLS_HPP_
#define BLITZ_ALPHA_INCLUDE_ALPHA_CORE_CONTROLS_HPP_

#include <cmath>
#include <numeric>

#include "alpha/alpha.hpp"

namespace blitz {
  namespace alg {

    template <typename T>
    void i_sort(T* A, int sz) {
      int i, j;
      T key;
      for (j = 1; j < sz; ++j) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key) {
          A[i + 1] = A[i];
          i = i - 1;
        }
        A[i + 1] = key;
      }
    }
    /* template<typename T>
    void insertion_sort(T* arr, int sz) {
        T key;
        for (int j = 1; j <= sz; ++j) {
            int i = 0;
            while (arr[j] > arr[i]) {
                i = i + 1;
            }
            key = arr[j];
            for (int k = 0; k < (j - i - 1); ++k) {
                arr[j - k] = arr[j - k - 1];
            }
            arr[i] = key;
        }
    } */

    template <typename T>
    void print(T* arr, int sz) {
      std::cout << "[ ";
      for (int i = 0; i < sz; ++i) {
        std::cout << arr[i];
        if (i < sz - 1) std::cout << ", ";
      }
      std::cout << " ]" << '\n';
    }

    template <typename _Tp>
    _Tp Max(_Tp* arr, int sz) {
      _Tp max = arr[0];
      for (int i = 1; i <= sz; ++i) {
        if (max < arr[i]) max = arr[i];
      }
      return max;
    }

    template <typename T>
    int linear_search(T* arr, T val, int sz) {
      int pos = -1;
      for (int i = 0; i <= sz; ++i) {
        if (arr[i] == val) {
          pos = i;
          break;
        }
      }
      return pos;
    }

    template <typename T>
    int binary_search(T* arr, T key, int sz) {
      int loc = -1;
      int i = 0;
      int j = sz;

      while (i < j) {
        int mid = floor((i + j) / 2);
        if (key > arr[mid])
          i = mid + 1;
        else
          j = mid;
      }
      if (key == arr[i]) loc = i;
      return loc;
    }

    template <typename T>
    void bubble_sort(T* arr, int sz) {
      for (int i = 1; i < sz - 1; ++i) {
        for (int j = 0; j < sz - i; ++j) {
          if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
      }
    }

    template <typename T>
    void Swap(T&& t1, T&& t2) {
      std::swap(std::forward<T>(t1), std::forward<T>(t2));
    }

    /**
     * @brief Insertion Sort Algorithm
     * @tparam _Tp Array type
     * @tparam size number of elements to be sorted.
     *
     */
    template <typename _Tp, int size>
    void insertion_sort(_Tp* array) {
      for (int j = 1; j < size; j++) {  // Loop from 1 to end
        _Tp key = array[j];             // set current key for comparison
        int i = j - 1;                  //  i is set to one step behind index j
        while ((i >= 0) && array[i] > key) {
          array[i + 1] = array[i];
          i = i - 1;
        }
        array[i + 1] = key;
      }
    }


    long factorial(int n);

  }  // namespace alg

}  // namespace blitz

#endif