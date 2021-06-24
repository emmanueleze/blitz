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

#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_CORE_GENERIC_HPP_
#define BLITZ_ALPHA_INCLUDE_ALPHA_CORE_GENERIC_HPP_

#pragma once

#include "alpha/alpha.hpp"

#include <array>
#include <functional>
#include <iterator>
#include <map>
#include <ostream>
#include <queue>
#include <type_traits>
#include <utility>

namespace blitz {

  namespace gen {
    template <typename T, typename Cont = std::deque<T>>
    class Stack;
    }
    namespace stream {
    template <typename T>
    std::ostream& operator<<(std::ostream& os, gen::Stack<T> const& _st);
    }
    namespace gen {

    //  Function Templates
    //  **********************************************

    template <typename _Tp>
    constexpr auto max(_Tp const& a, _Tp const& b)
      -> std::decay_t<decltype(b < a ? a : b)> {
      return b < a ? a : b;
    }

    //  Class Templates
    //  **********************************************

    template <typename _Tp, typename Cont>
    class Stack {
    public:
      void push(_Tp const&);
      void pop();
      _Tp const top() const;
      bool empty() const { return elems.empty(); }
      size_t size() const { return elems.size(); }
      friend std::ostream& stream::operator<<<_Tp>(std::ostream& os,
                                                  Stack<_Tp> const& _stack);

    private:
      Cont elems;
      std::mutex _stack_mutex;
      size_t sz;
    };

    template <typename _Tp, typename Cont>
    void Stack<_Tp, Cont>::push(_Tp const& elem) {
      std::lock_guard<std::mutex> lk(_stack_mutex);
      elems.push_back(elem);
      ++sz;
    }

    template <typename _Tp, typename Cont>
    void gen::Stack<_Tp, Cont>::pop() {
      std::lock_guard<std::mutex> lk(_stack_mutex);
      assert(!elems.empty());
      elems.pop_back();
      --sz;
    }

    template <typename _Tp, typename Cont>
    _Tp const Stack<_Tp, Cont>::top() const {
      std::lock_guard<std::mutex> lk(_stack_mutex);
      assert(!elems.empty());
      return elems.back();
    }

    template <typename T,typename Policy = SumPolicy, typename Traits = AccumulatorTraits<T> >
    auto accumulate(T const* p1, T const* p2) {
    
      using AccT = typename Traits::AccT;
      AccT total = Traits::zero;
      while (p1 != p2) {
        Policy::accum(total, *p1);
        ++p1;
      }
      return total;
    }

  }  // namespace gen

}  // namespace blitz

#endif  // BLITZ_ALPHA_INCLUDE_ALPHA_CORE_GENERIC_HPP_