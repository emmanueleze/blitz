#ifndef BLITZ_INCLUDE_BLITZ_CORE_CONCURRENT_HPP
#define BLITZ_INCLUDE_BLITZ_CORE_CONCURRENT_HPP

#include "blitz/blitz.hpp"
#include <condition_variable>
#include <deque>
#include <future>
#include <list>
#include <mutex>

namespace blitz {

namespace concurrent {

template<typename T>
std::list<T> quick_sort(std::list<T> coll) {
  return coll;
}





} // namespace concurrent

} // namespace blitz

#endif //  BLITZ_INCLUDE_BLITZ_CORE_CONCURRENT_HPP
