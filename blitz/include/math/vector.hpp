#ifndef BLITZ_INCLUDE_MATH_VECTOR_HPP
#define BLITZ_INCLUDE_MATH_VECTOR_HPP


namespace math {

template<typename T>
class vec{
public:
  vec(const T& _x, const T&_y) : x(_x), y(_y){}
  void operator+ (const vec& _vec) {
    x += _vec.x;
    y += _vec.y;
  }
private:
  T x, y;
};



}



#endif