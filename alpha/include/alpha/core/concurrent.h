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

#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_CORE_CONCURRENT_H
#define BLITZ_ALPHA_INCLUDE_ALPHA_CORE_CONCURRENT_H


#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <random>
#include <shared_mutex>

#include "alpha/alpha.h"



namespace blitz {

  namespace concurrent {

    bool flag;
    std::mutex _m;
    std::condition_variable _Cv;


    void wait_for_flag();

    void show_front(std::queue<gen::Name>&);
    void process_queue(std::queue<gen::Name>&);
    int random_generator(const int, const int);
  } // namespace concurrent

} // namespace blitz

#endif // BLITZ_ALPHA_INCLUDE_CORE_CONCURRENT_H_