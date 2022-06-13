
#include "blitz.hpp"

std::vector<int> core::two_sum(const std::vector<int> &array_, int target) {
  std::vector<int> ivec;
  auto sz = (int)blitz::len(array_);
  auto i1 = 0;
  auto i2 = sz - 1;
  for (int i = 0; i < sz; ++i) {
    if (array_[i1] + array_[i2] == target) {
      ivec.insert(ivec.begin(), {i1, i2});
      return ivec;
    }
    if (array_[i1] + array_[i2] > target)
      --i2;
    if (array_[i1] + array_[i2] < target)
      ++i1;
  }
  return ivec;
}


uint32_t core::gcd(uint32_t m, uint32_t n) {
  if (m < n)
    std::swap(m, n);
  auto r = m % n;
  if (r == 0) {
    return n;
  }
  m = n;
  n = r;
  return gcd(m, n);
}
