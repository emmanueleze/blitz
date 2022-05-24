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

class nth {
  unsigned int n;
  unsigned int _count;

public:
  nth(int _n) : n(_n), _count(0) {}
  const bool operator()(int) { return ++_count == n; }
};

class IntSequence {
public:
  IntSequence(int initial) : initial_value(initial) {}
  int operator()() { return ++initial_value; }

private:
  int initial_value;
};

class MeanValue {

  int num;
  int sum;

public:
  MeanValue() : num(0), sum(0) {}

  void operator()(int _num) {
    ++num;
    sum += _num;
  }

  operator double() {
    return static_cast<double>(sum) / static_cast<double>(num);
  }
};

class name {
public:
  using nameset = std::multiset<std::string>;
  name();
  template <convertible_to_string... Str> name(Str &&..._names) {
    append(_names...);
  }

  name(const name &_name);
  name(name &&_name);

public:
  nameset names() const;

  friend std::ostream &operator<<(std::ostream &strm, const name &_name) {
    for (const auto &name : _name.m_names)
      strm << name << " ";
    return strm << std::endl;
  }
  friend class name_hash;
  friend class name_equal;

private:
  nameset m_names;
  template <convertible_to_string T> void append(const T &arg) {
    m_names.insert(arg);
  }
  template <convertible_to_string... Args> void append(const Args &...args) {
    append(args...);
  }
};

// class name_hash {
// public:
//   std::size_t operator()(const name &_name) const {
//     return std::hash<std::string>()(_name.f_name) +
//            std::hash<std::string>()(_name.s_name);
//   }
// };

// class name_equal {
// public:
//   bool operator()(const name &n0, const name &n1) const {
//     return (n0.f_name == n1.f_name) && (n0.s_name == n1.s_name);
//   }
// };

//****************************************************************************

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