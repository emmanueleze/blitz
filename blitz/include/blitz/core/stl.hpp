#ifndef BLITZ_INCLUDE_BLITZ_CORE_STL_HPP
#define BLITZ_INCLUDE_BLITZ_CORE_STL_HPP

#include <deque>
#include <iostream>
#include <set>
#include <random>
#include <cmath>
#include <map>

#include "blitz/blitz.hpp"

namespace blitz {

template <typename Str>
concept convertible_to_string = std::is_convertible_v<Str, std::string>;

template <typename T> class allocator {
public:
  typedef T value_type;
  allocator() noexcept {}

  template <typename E> allocator(const allocator<E> &) noexcept {}

  T *allocate(std::size_t num) {
      return static_cast<T*>(::operator new(num * sizeof(T)));
  }

  void deallocate(T *s, std::size_t num) { ::operator delete(s); }
};

template <typename R1, typename R2>
bool operator==(const allocator<R1> &, const allocator<R2> &) noexcept {
  return true;
}

template <typename R1, typename R2>
bool operator!=(const allocator<R1> &, const allocator<R2> &) noexcept {
  return false;
}


template <typename Distr, typename Engine>
void distr(Distr _dist, Engine e, const std::string &name) {
  std::cout << name << ":" << std::endl;
  std::cout << "-min(): " << _dist.min() << std::endl;
  std::cout << "-max(): " << _dist.max() << std::endl;
  std::cout << "-values: " << _dist(e) << " " << _dist(e) << " " << _dist(e) << " "
       << _dist(e) << std::endl;

  std::map<long long, int> vcounter;
  for (int i = 0; i < 200000; ++i) {
    vcounter[_dist(e)]++;
  }
  std::cout << "====" << std::endl;
  for (auto elem : vcounter) {
    std::cout << std::setw(3) << elem.first << ": " << elem.second << std::endl;
  }
  std::cout << "====" << std::endl;
  std::cout << std::endl;
}

} // namespace blitz

#endif