#ifndef BLITZ_INCLUDE_MAT_HPP
#define BLITZ_INCLUDE_MAT_HPP

#include <utility>

namespace math {

template <typename T, unsigned N, unsigned M> class mat {
public:
  mat() : _data(new T(N * M)) {}
  auto size() const { return std::pair<uint, uint>(N, M); }

  T *_data;
};

} // namespace math

#endif