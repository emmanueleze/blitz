#ifndef BLITZ_INCLUDE_BLITZ_BLITZ_HPP
#define BLITZ_INCLUDE_BLITZ_BLITZ_HPP

#include "blitz-std.hpp"

#include "core/algorithm.hpp"
#include "core/arch.hpp"
#include "core/asio.hpp"
#include "core/concurrent.hpp"
#include "core/data.hpp"
#include "core/generic.hpp"
#include "core/stl.hpp"

namespace blitz {

constexpr bool is_prime(unsigned int p) {
  for (unsigned int i = 2; i <= p / 2; ++i) {
    if (p % i == 0)
      return false; // Found divisor without remainder.
  }
  return p > 1; // No divisor without remeainder.
}

template <typename T, std::size_t N>
constexpr std::size_t len(T (&)[N]) noexcept {
  return N;
}

template <typename T> typename T::size_type len(const T &t) noexcept {
  return t.size();
}

template <typename T> void print_type_of(const T &);

template <typename T, unsigned N> void array_sz(const T (&)[N]) {
  std::cout << N << "\n";
}

// Writes input to output stream.
// fix to accept multiple messages.
template <typename _MsgType>
void message(const _MsgType _message, const char *sep = " ",
             const char *delim_ = "\n", std::ostream &os = std::cout) {
  os << _message << sep << delim_;
  if (strcmp(delim_, "\n"))
    os << "\n";
}

template <typename... Args> void message(const Args &...args) {
  message(args...);
}

template <typename T> void sort(T &coll) {
  std::sort(coll.begin(), coll.end());
}

template <typename T> void isEmpty(const T &collection) {
  std::cout << std::boolalpha << (collection.empty() ? true : false)
            << std::endl;
}

template <typename Iter>
typename std::iterator_traits<Iter>::value_type print(Iter begin, Iter end) {}

template <typename T> void print(const T &coll, const char *delim_ = " ") {
  using value_type = typename T::value_type;
  std::copy(coll.cbegin(), coll.cend(),
            std::ostream_iterator<value_type>(std::cout, delim_));
  if (strcmp(delim_, "\n"))
    std::cout << "\n";
}

enum class Interval { Open, Closed, OpenClosed, ClosedOpen };

template <typename T>
bool in_range(const T &x, const T &a, const T &b,
              Interval interval = Interval::Closed) {
  switch (interval) {
  case Interval::Closed:
    if (a <= x && x <= b)
      return true;
    break;
  case Interval::ClosedOpen:
    if (a <= x && x < b)
      return true;
  case Interval::OpenClosed:
    if (a < x && x <= b)
      return true;
  case Interval::Open:
    if (a < x && x < b)
      return true;
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

class SqlHandler {
public:
  SqlHandler();
  SqlHandler(const std::string &filename);
  SqlHandler(const std::string &filename, int open_flag);
  ~SqlHandler();

public:
  void set_file_name();
  std::string filename() const;
  int open(const std::string&);
  int open(const std::string&, int flags);
  int close();

private:
  sqlite3 *db;
};

} // namespace blitz

#endif