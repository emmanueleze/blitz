#ifndef ALPHA_INCLUDE_ALPHA_ALPHA_H_
#define ALPHA_INCLUDE_ALPHA_ALPHA_H_

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>




// Writes input to output stream.
// fix to accept multiple messages.
template<typename _MsgType>
void message(const _MsgType _message, std::ostream& os = std::cout){

    os << _message << std::endl;
    
  }





#endif