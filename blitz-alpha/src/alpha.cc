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



#include "alpha.h"


using namespace std;
using namespace blitz;
using namespace blitz::gen;
using namespace blitz::concurrent;


Name::Name(std::string fname, std::string lname) :firstName(fname),
lastName(lname) {}

string Name::FirstName() const { return firstName; }
string Name::LastName()const { return lastName; }


bool NameAscending::operator()(const Name& n1, const Name& n2)const {
    return n1.LastName() < n2.LastName() ||
        ((n1.LastName() == n2.LastName()) &&
            (n1.FirstName() < n2.FirstName()));
}

bool NameDescending::operator()(const Name& n1, const Name& n2)const {
    return n1.LastName() > n2.LastName() ||
        ((n1.LastName() == n2.LastName()) &&
            (n1.FirstName() > n2.FirstName()));
}

Name& Name::operator=(const Name& n1) {
    this->firstName = n1.firstName;
    this->lastName = n1.lastName;

    return *this;
}


Singleton* Singleton::_instance = 0;
bool Singleton::_destroyed = false;










