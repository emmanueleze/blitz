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

#ifndef BLITZ_ALPHA_INCLUDE_ALPHA_CORE_BSTRUCTS_H_
#define BLITZ_ALPHA_INCLUDE_ALPHA_CORE_BSTRUCTS_H_

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <mutex>
#include <stack>

#include "alpha/alpha.h"
#include "alpha/core/policy.h"

namespace blitz {

namespace alg {

template <typename _Tp>
class Node {
 public:
  Node() {}
  Node(_Tp _data) : data(_data) {}
  Node(const Node& n);
  Node(Node&& n);
  Node& operator=(const Node& n0){
    this->data = n0.data;
    return  *this;
  }

 public:
  _Tp data;
};

template <typename T, int sz>
class naive_stack {
 public:
  naive_stack() = default;
  naive_stack(T* a) { arr = a; }
  bool is_empty() const {
    if (top < 0)
      return true;
    else
      return false;
  }

  void push(T x) {
    try {
      top = top + 1;
      if (top == sz)
        throw std::overflow_error{"buffer overflowed."};
      else {
        arr[top] = x;
      }
    } catch (std::overflow_error o) {
      std::cout << o.what() << '\n';
    }
  }
  void pop() {
    if (top < 0) std::cout << "buffer underflow.\n";
    top = top - 1;
  }
  void show() const {
    std::cout << "[ ";
    for (int i = 0; i <= top; ++i) {
      std::cout << arr[i] << ' ';
      if (i < top - 1) std::cout << ", ";
    }
    std::cout << " ]" << '\n';
  }

 private:
  int top = -1;
  T* arr = nullptr;
};
/** @brief Stack
 * Thread-Safe implementation of a stack
 * @param T type of element in the stack
 */
template <typename T>
class Stack {
 public:
  Stack() {}
  Stack(const Stack& _stack) {
    std::lock_guard<std::mutex> lock(_stack.m);
    data = _stack.data;
  }
  Stack& operator=(const Stack&) = delete;

  void push(T _entry) {
    std::lock_guard<std::mutex> lock(m);
    data.push(_entry);
    ++sz;
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw std::runtime_error("empty structure.");
    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    --sz;
    return res;
  }

  T top() {
    std::lock_guard<std::mutex> lock(m);
    // std::cout<<data.top()<<'\n';
    return data.top();
  }

  void pop(T& _entry) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw std::runtime_error("empty structure.");
    _entry = data.top();
    data.pop();
    --sz;
  }
  unsigned int size() { return sz; }
  bool is_empty() {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }

 private:
  std::stack<T> data;
  mutable std::mutex m;
  unsigned int sz;
};

template <typename T, int sz>
class Queue {
 public:
  Queue() {}
  Queue(T* a) : arr{a} {}

  void enqueue(T t) {
    if (tail == (sz))
      tail = 0;
    else {
      if (head == -1) head = 0;
      ++tail;
      printf("%d\n", tail);
      arr[tail] = t;
    }
  }
  T dequeue() {}
  bool isempty() const {
    if ((head == -1) && (tail == -1))
      return true;
    else
      return false;
  }

  void showfront() const { std::cout << arr[head] << '\n'; }

 private:
  int head = -1;
  int tail = -1;
  T* arr = nullptr;
};

/**
 * @brief LinkedList implements a doubly linked list data structure.
 * @tparam _Node
 */
template <typename T, template <typename> class _Node = Node>
class LinkedList {

 public:
  LinkedList() {
    head = nullptr;
    
  }
  void insert(T _data){
    auto _node = new _Node(_data);
    _node->data = _data;
    _node->next = nullptr;

    if(head == nullptr){
      head = _node;
    }
    else{
      //  Critical section.!
      _node->next = head;
      head = _node;
    }
  
  }
  void remove();
  void traverse()const{
    auto begin = head;
    while(begin != nullptr){
      std::cout << begin->data << " ";
      begin = begin->next;
    }
    std::cout<<"\n";
  }

  bool search(T _data) const{
    auto begin = head;
    
    while(begin != nullptr){
      if(begin->data == _data)
        return true;
    }
    return false;
    
  }
 
 private:
  _Node<T>* head;
  std::mutex _mutex;
};
 

  template <typename _Tp, typename NodeTp = alg::Node<_Tp>>
  class SingleNode : public NodeTp {
  friend class LinkedList<_Tp,SingleNode>;
  public:
    SingleNode() {}
    SingleNode(_Tp _data) : NodeTp(_data){}
  private:
    SingleNode *next;
  };

  template <typename _Tp, typename NodeTp = alg::Node<_Tp>>
  class DoubleNode : public NodeTp {
  friend class LinkedList<_Tp, DoubleNode>;
  public:
    DoubleNode() {}
    DoubleNode(_Tp _data) : NodeTp(_data){}

  private:
    DoubleNode *prev;
    DoubleNode *next;
  };

  template <typename _Tp, typename NodeType = alg::Node<_Tp>>
  class CircularNode : public NodeType {
  friend class LinkedList<_Tp, CircularNode>;
  
  public:
    CircularNode() = default;
    CircularNode(_Tp _data) : NodeType(_data){}

  private:
    CircularNode *first;  
  };


template<>
class LinkedList<int> {
  public:
    LinkedList(){std::cout << "LinkedList<int>\n";}
};


// general distance
template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type Distance(
  Iterator pos1, Iterator pos2) {
  using category = typename std::iterator_traits<Iterator>::iterator_category;
  static_assert(std::is_base_of_v<std::input_iterator_tag, category>);

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, category>)
    return pos2 - pos1;
  else {
    typename std::iterator_traits<Iterator>::difference_type _distance = 0;
    while (pos1 != pos2) {
      ++pos1;
      ++_distance;
    }
    return _distance;
  }
}

void display(){std::cout << "structures" <<std::endl;}

}  // namespace alg

template <typename _Tp>
using SingleList = alg::LinkedList<_Tp, alg::SingleNode>;

template <typename _Tp>
using DoubleList = alg::LinkedList<_Tp, alg::DoubleNode>;

template<typename _Tp>
using CircularList = alg::LinkedList<_Tp, alg::DoubleNode>;



}  // namespace blitz
#endif
