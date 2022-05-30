
#include "blitz/blitz.hpp"

std::vector<int> blitz::twoSum(const std::vector<int> &array_, int target) {
  std::vector<int> ivec;
  auto sz = static_cast<int>(array_.size());
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
