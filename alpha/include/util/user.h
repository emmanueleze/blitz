
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


#ifndef ALPHA_INCLUDE_UTIL_USER_H
#define ALPHA_INCLUDE_UTIL_USER_H

#include "alpha.h"
#include "core/groups.h"

namespace user{

class User{
    public:
        User(){}
        User(std::string _name) :name{_name}{}
        std::string get_name() {return name;}
        void show(){std::cout<<name<<'\n';}
        friend std::ostream& operator<<(std::ostream&& os, User _user){
                return os << _user.get_name() << ' ';
            }
    private:
        std::string name;
};

/* template<typename T>
class AdapterClient{
    public:
        AdapterClient(){}
        AdapterClient(T& _wrapper) :wrapper{_wrapper}{
            std::cout<<wrapper.displayPath()<<'\n';
        }

        
        ~AdapterClient(){}

    public:
        int open(){}
        void read()const{}
        bool eof()const{}


    private:
        T wrapper;
}; */




}   //user namespace




#endif