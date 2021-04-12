/**
 *  MIT License

 *  Copyright (c) 2021 Emmanuel Godwin

 *  Permission is hereby granted, free of charge, to any person obtaining a copy of 
 *  this software and associated documentation files (the "Software"), to deal in 
 *  the Software without restriction, including without limitation the rights to use, 
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 *  Software, and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions:

 *  The above copyright notice and this permission notice shall be included in all 
 *  copies or substantial portions of the Software.

 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 *  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef ALPHA_INCLUDE_UTIL_EXCEPTIONAL_H
#define ALPHA_INCLUDE_UTIL_EXCEPTIONAL_H

#include "alpha.h"
#include <exception>
#include <stdexcept>

namespace except{

class overflow{

    public:
        overflow(std::string msg) :message{msg}{}
        std::string what()const{return "error: "+message;}
        
    private:
        std::string message;
};

class empty_stack{
     public:
        empty_stack(std::string msg) :message{msg}{}
        std::string what()const{return "error: "+message;}
        
    private:
        std::string message;
};

class underflow{};
class illegal_arg{};
class null_error{};

}

class file_error : std::exception{
    public:
        const char* what()const throw();
};

#endif



