#ifndef ALPHA_INCLUDE_ALPHA_ALPHA_H_
#define ALPHA_INCLUDE_ALPHA_ALPHA_H_

#include <cassert>
#include <cstring>
#include <deque>
#include <iostream>
#include <memory>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include "alpha/atypes.h"
#include "alpha/core/alpha_alg.h"
#include "alpha/core/alpha_data.h"
#include "alpha/core/alpha_gnr.h"
#include "alpha/core/alpha_mt.h"
#include "alpha/core/alpha_stl.h"
#include "alpha/core/arch.h"

namespace alpha {


inline void Init() {
  std::cout.precision(4);
  std::cout.setf(std::ios::fixed);
}

// Writes input to output stream.
// fix to accept multiple messages.
template <typename _MsgType>
void message(const _MsgType _message, const char *delim_ = "\n",
             std::ostream &os = std::cout) {
  os << _message << delim_;
  if (!strcmp(delim_, "\n"))
    os << "\n";
}

template<typename T>
void sort(T& coll) {
  std::sort(coll.begin(), coll.end());
}

template <typename T> void isEmpty(const T &collection) {
  std::cout << (collection.empty() ? "true" : "false") << std::endl;
}

template<typename Iter>
typename std::iterator_traits<Iter>::value_type
print(Iter begin, Iter end){

}

template <typename T> void print(const T &coll, const char *delim_ = " ") {
  using value_type = T::value_type;
  std::copy(coll.cbegin(), coll.cend(),
            std::ostream_iterator<value_type>(std::cout, delim_));
  if (strcmp(delim_, "\n"))
    std::cout << "\n";
}

enum class Interval { Open, Closed, OpenClosed, ClosedOpen };

template <typename T>
bool in_interval(const T &x, const T &a, const T &b,
                 Interval interval = Interval::Closed) {
  switch (interval) {
  case Interval::Closed:
    if (a <= x && x <= b)
      return true;
    break;

  default:
    break;
  }
  return false;
}

template <typename T> void swap(T *first, T *second) {
  T temp = *first;
  *first = *second;
  *second = temp;
}

class Logger {
public:
  Logger();
};

} // namespace alpha

#endif