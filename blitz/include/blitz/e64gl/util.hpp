#ifndef BLITZ_INCLUDE_BLITZ_E64GL_UTIL_HPP
#define BLITZ_INCLUDE_BLITZ_E64GL_UTIL_HPP

#include <exception>



class window_error : public std::exception {
  public:
  window_error();
  window_error(const std::string&);
};


#endif