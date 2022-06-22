
#include "blitz.hpp"


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

uint32_t core::factorial(uint32_t N) {
  if(N == 0)
  return 1;
  else
    return N * factorial(N - 1);
}




