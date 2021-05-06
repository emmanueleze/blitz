// MIT License
//
// Copyright (c) 2021 Emmanuel Godwin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "alpha/alpha.h"

#include "alpha/core/alpha_stl.h"
#include "alpha/core/concurrent.h"

using namespace std;
using namespace blitz;
using namespace blitz::gen;
using namespace blitz::concurrent;

Name::Name(std::string fname, std::string lname)
  : firstName(fname), lastName(lname) {}

string Name::FirstName() const { return firstName; }
string Name::LastName() const { return lastName; }

bool Name::operator==(Name& n1) const {
  return ((this->firstName == n1.firstName) && (this->lastName == n1.lastName));
}
bool NameAscending::operator()(const Name& n1, const Name& n2) const {
  return n1.LastName() < n2.LastName() || ((n1.LastName() == n2.LastName()) &&
    (n1.FirstName() < n2.FirstName()));
}

bool NameDescending::operator()(const Name& n1, const Name& n2) const {
  return n1.LastName() > n2.LastName() || ((n1.LastName() == n2.LastName()) &&
    (n1.FirstName() > n2.FirstName()));
}

std::ostream& gen::operator<<(std::ostream& ost, const Name& name) {
  return ost << name.firstName << " " << name.lastName;
}

Name& Name::operator=(const Name& n1) {
  this->firstName = n1.firstName;
  this->lastName = n1.lastName;

  return *this;
}

Singleton* Singleton::_instance = 0;
bool Singleton::_destroyed = false;

void Singleton::KillPhoenixSingleton() {
  // Make all ashes again
  // - call the destructor by hand.
  // It will set pInstance_ to zero and destroyed_ to true
  _instance->~Singleton();
}


void Singleton::OnDeadReference() {
  /*  // Obtain the shell of the destroyed singleton
   Create();
   // Now pInstance_ points to the "ashes" of the singleton
   // - the raw memory that the singleton was seated in.
   // Create a new singleton at that address
   new(_instance) Singleton;
   // Queue this new object's destruction
   atexit(Singleton::KillPhoenixSingleton);
   // Reset destroyed_ because we're back in business
   _destroyed = false; */
}

void concurrent::wait_for_flag() {
  std::unique_lock<std::mutex> lk(concurrent::_m);
  while (!concurrent::flag) {
    lk.unlock();
    cout << "wait_for_flag(): sleeping for 100ms.\n";
    this_thread::sleep_for(chrono::seconds(5));
    cout << "wait_for_flag(): awake.\n";
    lk.lock();
  }
}

void concurrent::show_front(std::queue<gen::Name>& q) {
  cout << "Waiting thread --> show_front()\n";
  while (true) {
    std::unique_lock<mutex> lk(_m);
    concurrent::_Cv.wait(lk, [=] { return !q.empty(); });
    lk.unlock();
    std::cout << q.front() << '\n';
    this_thread::sleep_for(chrono::seconds(2));
    if(q.empty()) break;
  }
}

void concurrent::process_queue(std::queue<gen::Name>& q) {
  cout << "Processing thread --> process_queue()\n";
  try {
    if (q.empty()) throw runtime_error("Queue is empty.");
  }
  catch (const runtime_error& e) {
    cout << e.what() << '\n';
  }
  while (!q.empty()) {
    unique_lock<mutex> lk(_m);
    std::this_thread::sleep_for(chrono::seconds(5));
    //cout<<q.front()<<'\n';
    q.pop();
    lk.unlock();
    concurrent::_Cv.notify_one();
  }
}


int concurrent::random_generator(const int _min, const int _max) {

  static thread_local mt19937 generator(hash<thread::id>() (this_thread::get_id()));
  uniform_int_distribution<int> distribution(_min, _max);
  return distribution(generator);


}
long alg::factorial(int n) {
  if (n < 0) return 0;
  if ((n == 0) || (n == 1))
    return 1;
  else
    return n * factorial(n - 1);

}

file::Reader::Reader(std::string _filename) : filename{ _filename } {
  if (!file.is_open())
    this->OpenFile();
}
void file::Reader::OpenFile() {
  file.open(filename);
}

void file::Reader::Read() {

  char buf[512];
  if (file.is_open() && !file.fail()) {
    while (!file.eof()) {
      file.getline(buf, 512, '\n');
      std::cout << buf << '\n';
    }
  }
}
