#ifndef BLITZ_INCLUDE_BLITZ_CORE_DATA_HPP
#define BLITZ_INCLUDE_BLITZ_CORE_DATA_HPP


#include <iomanip>
#include <iostream>

#include "blitz/blitz.hpp"

namespace blitz {

template <typename _Key, typename _Element> class binary_node {
public:
  binary_node(const _Key &_key, const _Element &_value)
      : m_key(_key), m_value(_value), left_child(0), right_child(0) {}

  // Returns the value of the node.
  _Element value() const { return m_value; }
  // Sets th value of the node.
  void value(const _Element &_value) { m_value = _value; }
  // Returns the key value
  _Key key() const { return m_key; }
  // Sets the key value
  void key(const _Key &_key) { m_key = _key; }

  inline binary_node *left() const { return left_child; }
  void set_left(binary_node *node) { left_child = node; }
  inline binary_node *right() const { return right_child; }
  void set_right(binary_node *node) { right_child = node; }

  bool is_leaf() const {
    return (left_child == nullptr) && (right_child == nullptr);
  }

private:
  binary_node<_Key, _Element> *left_child;
  binary_node<_Key, _Element> *right_child;
  _Key m_key;
  _Element m_value;
};

template <typename T> struct DoubleNode {
  DoubleNode() {}
  DoubleNode(const T &_data) : m_data(_data), prev(0), next(0) {}
  DoubleNode<T> *next;
  DoubleNode<T> *prev;
  T m_data;
};

template <typename T> class single_node {
public:
  single_node() : next(0), m_data({}) {}
  single_node(const T &_data) : next(0), m_data(_data) {}
  single_node(const single_node<T> &_node)
      : next(_node.next), m_data(_node.m_data) {}
  single_node(single_node<T> &&_node)
      : next(std::move(_node.next)), m_data(std::move(_node.m_data)) {}
  single_node<T> *next;
  T data() const { return m_data; }

private:
  T m_data;
};

template <typename T> class SinglyList {
  using node = single_node<T>;

public:
  SinglyList() {}

public:
  void insert(const T &_data) {
    auto _node = new node(_data);
    if (front == nullptr)
      front = _node;
    else {
      _node->next = front;
      front = _node;
    }
  }
  void insert(const T &_data, unsigned int position) {
    if (front == nullptr)
      insert(_data);
    else {
      auto _node = new node(_data);
      auto t_node = front;

      for (int i = 0; i < position; ++i) {
        t_node = t_node->next;
      }
      _node->next = t_node->next;
      t_node->next = _node;
    }
  }
  void remove(unsigned int position) {
    auto t_node = front;
    auto prev_node = t_node;
    for (int i = 0; i < position; ++i) {
      t_node = t_node->next;
    }
  }

  friend std::ostream &operator<<(std::ostream &strm,
                                  const SinglyList<T> &_list) {
    auto begin = _list.front;
    while (begin != nullptr) {
      strm << begin->data() << " ";
    }
    return strm << "\n";
  }

private:
  node *front;
  node *back;
  std::size_t m_size;
};

template <> class SinglyList<int> {

  using node = single_node<int>;

public:
  SinglyList() : front_(0), back_(0), size_(0) {}

public:
  unsigned int size() const { return size_; }

  void insert(const int &_data) {
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

  void insert(const int &_data, uint pos) {
    auto _node = new node(_data);
    auto t_node = front_;

    for (uint i = 1; i < pos; ++i) {
      if (t_node)
        t_node = t_node->next;
    }
    _node->next = t_node->next;
    t_node->next = _node;
    ++size_;
  }

  bool empty() { return size_ > 0 ? false : true; }

  void remove(const node &_node, uint position) {
    // auto _node = new no
  }

  void traverse() {
    auto begin = front_;
    if (!empty()) {
      while (begin != nullptr) {
        std::cout << begin->data() << " ";
        begin = begin->next;
      }
    }
  }

private:
  node *front_;
  node *back_;
  unsigned int size_;
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
  Stack() : capacity_(_capacity), top_(-1) { m_data = new list(); }

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
      m_data->insert(_data);
    }
  }

  void traverse() const {
    if (!(empty())) {
      m_data->travese();
    }
  }

private:
  list *m_data;
  int top_{};
  int size_{};
  int capacity_{};
};

// Queue internally uses C-style array.
template <typename T, int N> class Queue {
public:
  Queue() {
    m_data = new T[N];
    front_ = 0;
    back_ = N - 1;
  }

private:
  T *m_data;
  T front_;
  T back_;
};

template <typename BufferValueType> class ring_buffer {
  using T = BufferValueType;

public:
  ring_buffer() = delete;
  ring_buffer(unsigned int size) : m_begin(0), m_end(0), m_size(size) {
    m_buffer = std::make_unique<T[]>(m_size);
  }

  T read() {
    T m_data = m_buffer[m_begin++];
    m_begin %= m_size;
    return m_data;
  }

  void write(const T &m_data) {
    m_buffer[m_end++] = m_data;
    m_end %= m_size;
  }

  unsigned int size() const { return m_size; }

private:
  std::unique_ptr<T[]> m_buffer;
  unsigned int m_size;
  int m_end;
  int m_begin;
};

class HashTable;

template <typename K, typename E> class binary_search_tree {
public:
  using key_type = K;
  using value_type = E;
  using node = binary_node<key_type, value_type>;

  binary_search_tree() : root(0), node_count(0) {}
  ~binary_search_tree() { bst_clear(root); }

public:
  node *tree_root() const { return root; }

  // Resets the binary search tree
  void clear() {
    bst_clear(root);
    root = nullptr;
    node_count = 0;
  }

  void insert(const K &key, const E &value) {
    bst_insert(root, key, value);
    ++node_count;
  }
  E remove(const K &key) {
    auto tmp = bst_find(root, key);
    if (!tmp) {
      root = bst_remove(root, key);
      --node_count;
    }
    return tmp;
  }

  bool search(const K &key) { return bst_search(root, key); }

  unsigned int count() const { return node_count; }

private:
  void bst_clear(node *);
  node *bst_insert(node *, const K &, const E &);
  node *bst_delete_min(node *);
  node *bst_get_min(node *);
  node *bst_remove(node *, const K &);
  E bst_find(node *, const K &) const;
  void bst_print(node *, int) const;
  bool bst_search(node *, const K &);

  node *root;
  unsigned int node_count;
};

template <typename K, typename E>
bool binary_search_tree<K, E>::bst_search(node *_node, const K &_key) {
  if(!_node)
    return false;
  if (_node->key() == _key)
    return true;
  if (_key < _node->key())
    return bst_search(_node->left(), _key);
  else
    return bst_search(_node->right(), _key);
}

template <typename K, typename E>
E binary_search_tree<K, E>::bst_find(node *_node, const K &key) const {
  if (!_node)
    return nullptr;
  if (key < _node->key())
    return bst_find(_node->left(), key);
  else if (key > _node->key()) {
    return bst_find(_node->right(), key);
  } else
    return _node->key();
}

template <typename K, typename E>
binary_node<K, E> *binary_search_tree<K, E>::bst_insert(node *_node,
                                                        const K &key,
                                                        const E &value) {
  if (!_node)
    return new node(key, value);
  if (key < _node->key())
    _node->set_left(bst_insert(_node->left(), key, value));
  if (key > _node->key())
    _node->set_right(bst_insert(_node->right(), key, value));
  return _node;
}

template <typename K, typename E>
void binary_search_tree<K, E>::bst_clear(node *_node) {
  if (!_node)
    return;
  bst_clear(_node->left());
  bst_clear(_node->right());
  delete _node;
}

} // namespace blitz

#endif