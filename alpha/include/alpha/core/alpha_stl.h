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

#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_CORE_ALPHA_STL_H_
#define BLITZ_ALPHA_INCLUDE_ALPHA_CORE_ALPHA_STL_H_

#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <set>
#include <type_traits>
#include <unordered_set>

#include "alpha/alpha.h"

using namespace std::placeholders;

namespace blitz {
namespace gen {
class Name {
 public:
  Name() {}
  Name(std::string, std::string);

 public:
  std::string FirstName() const;
  std::string LastName() const;
  Name& operator=(const Name&);
  bool operator==(Name& n1) const;
  friend std::ostream& operator<<(std::ostream& ost, const Name& name);

 private:
  std::string firstName;
  std::string lastName;
};

std::ostream& operator<<(std::ostream& ost, const Name& name);

class NameAscending {
 public:
  bool operator()(const Name&, const Name&) const;
};

class NameDescending {
 public:
  bool operator()(const Name&, const Name&) const;
};

template <typename T, typename SortCriterion>
using NameSet = std::set<T, SortCriterion>;

class IntSequence {
 public:
  friend int GetIntValue();
  IntSequence(int init) : value(init) {}
  int operator()() { return ++value; }

 private:
  int value;
};

class MeanValue {
 public:
  MeanValue() : num(0), sum(0) {}

  void operator()(long int elem) {
    ++num;
    sum += elem;
  }

  double value() { return static_cast<double>(sum) / static_cast<double>(num); }

 private:
  long int num;
  long int sum;
};

}  // namespace gen
}  // namespace blitz

#endif