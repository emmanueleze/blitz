#ifndef ALPHA_INCLUDE_ALPHA_CORE_ALPHA_DATA_H_
#define ALPHA_INCLUDE_ALPHA_CORE_ALPHA_DATA_H_

#include "alpha/alpha.h"

namespace alpha {

template <typename T> struct DoubleNode {
  DoubleNode() {}
  DoubleNode(const T &_data) : data(_data), prev(0), next(0) {}
  DoubleNode<T> *next;
  DoubleNode<T> *prev;
  T data;
};

template <typename T> struct SingleNode {

  SingleNode() {}
  SingleNode(const T &_data) : data(_data) {}
  SingleNode<T> *next;
  T data;
};

template <typename T> class SinglyList {

  using node = SingleNode<T>;

public:
  SinglyList() : front_(0), back_(0), size_(0) {}
  ~SinglyList() {}

public:
  unsigned int size() const { return size_; }

  void insert(const T &_data) {
    auto _node = new node(_data);
    if (front_ == nullptr) {
      front_ = _node;
      ++size_;
    } else {
      _node->next = front_;
      front_ = _node;
      ++size_;
    }
  }

  void insert(int pos, const T &_data) {
    auto _node = new node(_data);

    auto t_node = front_;
    for (int i = 1; i < pos; ++i) {
      if (t_node)
        t_node = t_node->next;
    }
    _node->next = t_node->next;
    t_node->next = _node;
    ++size_;
  }

  bool empty() { return size_ > 0 ? false : true; }

  void remove(const node &_node, uint position) {
    /*

    */
  }

  void travese() {
    auto begin = front_;
    if (!empty()) {
      while (begin != nullptr) {
        std::cout << begin->data << " ";
        begin = begin->next;
      }
    }
  }

private:
  node *front_;
  node *back_;
  int size_;
};

template <typename T> class DoublyList {

  using node = DoubleNode<T>;

public:
  DoublyList() : head(0), tail(0) {}
  ~DoublyList() {}

public:
  int size() const { return size_; }
  void insert(const T &_data) {}
  void remove() {}
  void traverse() {}

private:
  node *head;
  node *tail;
  unsigned int size_{};
};

template <typename T, int _capacity> class Stack {
  using list = SinglyList<T>;

public:
  Stack() : capacity_(_capacity), top_(-1) { data = new list(); }

public:
  bool empty() const { return top_ < 0 ? true : false; }
  // T& top() const { return top_; }
  int size() const { return size_; }
  int capacity() const { return capacity_; }
  void resize(int _size) { capacity_ = _size; }
  void push(const T &_data) {
    if (top_ == capacity_ - 1) {
    } else {
      ++top_;
      ++size_;
      data->insert(_data);
    }
  }

  void traverse() const {
    if (!(empty())) {
      data->travese();
    }
  }

private:
  list *data;
  int top_{};
  int size_{};
  int capacity_{};
};

// Queue internally uses C-style array.
template <typename T, int N> class Queue {
public:
  Queue() {
    data = new T[N];
    front_ = 0;
    back_ = N - 1;
  }

private:
  T *data;
  T front_;
  T back_;
};

} // namespace alpha

#endif