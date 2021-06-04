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

  namespace gen{
    template<typename T, typename Cont = std::vector<T>>
    class Stack;
  }
  namespace stream{
    template<typename T>
    std::ostream& operator<<(std::ostream& os, gen::Stack<T> const& _st);
  }
  namespace gen {

    //  Function Templates
    //  **********************************************

    template<typename _Tp>
    constexpr auto  max(_Tp const& a, _Tp const& b)->std::decay_t<decltype(b < a ? a : b)> {
      return b < a ? a : b;
    }

    //  Class Templates
    //  **********************************************

      template<typename _Tp, typename Cont >
      class Stack{
        public:
          void push(_Tp const&);
          void pop();
          _Tp const& top()const;
          bool  empty () const {
            return elems.empty();
          }

          friend std::ostream& stream::operator<< <_Tp> (std::ostream& os, Stack<_Tp> const& _stack);

        private:
          Cont elems;
      };
    
      template<typename _Tp, typename Cont>
      void Stack<_Tp, Cont>::push(_Tp const& elem){
        elems.push_back(elem);
      }

      template<typename _Tp, typename Cont>
      void gen::Stack<_Tp, Cont>::pop() {
        assert (!elems.empty());
        elems.pop_back();
      }

      template<typename _Tp, typename Cont>
      _Tp const& Stack<_Tp, Cont>::top() const {
        assert(!elems.empty());
        return elems.back();
      }



  } // namespace gen

} // namespace blitz

#endif  // BLITZ_ALPHA_INCLUDE_ALPHA_CORE_GENERIC_HPP_