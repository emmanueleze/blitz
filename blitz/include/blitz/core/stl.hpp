#ifndef BLITZ_INCLUDE_BLITZ_CORE_STL_HPP
#define BLITZ_INCLUDE_BLITZ_CORE_STL_HPP

#include <iostream>
#include <deque>

#include "blitz/blitz.hpp"


namespace blitz {

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

class Name {
public:
  Name();
  explicit Name(const std::string &, const std::string &);

public:
  void setName(const Name &name) {
    f_name = name.f_name;
    s_name = name.s_name;
  }

  friend std::ostream &operator<<(std::ostream &strm, const Name &name) {
    return strm << name.f_name << " " << name.s_name;
  }
  friend class NameHash;
  friend class NameEqual;

private:
  std::string f_name;
  std::string s_name;
};

class NameHash {
public:
  std::size_t operator()(const Name &name) const {
    return std::hash<std::string>()(name.f_name) +
           std::hash<std::string>()(name.s_name);
  }
};

class NameEqual {
public:
  bool operator()(const Name &n0, const Name &n1) const {
    return (n0.f_name == n1.f_name) && (n0.s_name == n1.s_name);
  }
};

/* class User {
public:
  User();
  User(const Name &);

public:
  void setName(const Name&);
  void
}; */

} // namespace alpha

#endif