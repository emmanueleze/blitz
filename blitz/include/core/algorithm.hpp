#ifndef BLITZ_INCLUDE_CORE_ALGORITHM_HPP
#define BLITZ_INCLUDE_CORE_ALGORITHM_HPP

#include "blitz.hpp"
#include "data.hpp"

#include <array>
#include <functional>
#include <list>
#include <numeric>
#include <random>

namespace core {


template<typename T, unsigned N>
int binary_search(const T(&_array)[N], const int&  _key) {
  int lower = 0;
  int upper = N - 1;

  while (lower <= upper) {
    int mid = ((lower + upper) / 2);
    auto mid_value = _array[mid];
    if (mid_value == _key) {
      return mid;
    } else if (mid_value < _key) {
      lower = mid + 1;
    } else if (mid_value > _key) {
      upper = mid - 1;
    }
  }
  return -1;
  
}

template<typename T>
int binary_search(const T& _array, const typename T::value_type& _key){
  int lower = 0;
  int upper = static_cast<int>(_array.size());

  while (lower <= upper) {
    int mid = ((lower + upper) / 2);
    auto mid_value = _array[mid];
    if (mid_value == _key) {
      return mid;
    } else if (mid_value < _key) {
      lower = mid + 1;
    } else if (mid_value > _key) {
      upper = mid - 1;
    }
  }
  return -1;
}



// Euclid's greatest common divisor.
uint32_t gcd(uint32_t m, uint32_t n);

std::vector<int> two_sum(const std::vector<int> &array_, int target);

uint32_t factorial(uint32_t N);

template <typename T> void traverse(const double_list<T> &_list) {
  if (_list.head == nullptr)
    return;

  auto *_node = _list.head;
  while (_node != nullptr) {
    std::cout << _node->data << " ";
    _node = _node->next;
  }
  std::cout << "\n";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const double_list<T> &_list) {
  os << _list._size << std::endl;
  return os;
}

} // namespace core

namespace blitz {

template <typename T> void isort(T *array_, int size_) {
  for (int i = 0; i < size_; ++i) {
    auto key = array_[i];
    int j = i - 1;
    while (j >= 0 && array_[j] > key) {
      array_[j + 1] = array_[j];
      --j;
    }
    array_[j + 1] = key;
  }
}

template <typename T> int linear_search(const T *seq_, int size, const T &key) {
  for (int pos = 0; pos < size; ++pos) {
    if (seq_[pos] == key)
      return pos;
  }
  return -1;
}

/* @brief Return a vector of containing indicies where the sum of the values
 * at both index equals the target. This algorithm runs in O(n).
 * @param array_ Vector of sorted integers.
 * @param target Target
 */
// std::vector<int> twoSum(const std::vector<int> &array_, int target);

// template <typename K, typename E>
// void tree_preorder(core::binary_node<K, E> *_node) {
//   if (!_node)
//     return;
//   std::cout << _node->value() << " ";
//   tree_preorder(_node->left());
//   tree_preorder(_node->right());
// }

// template <typename K, typename E>
// void tree_inorder(core::binary_node<K, E> *_node) {
//   if (!_node)
//     return;
//   tree_inorder(_node->left());
//   std::cout << _node->key() << " ";
//   tree_inorder(_node->right());
// }

// template <typename K, typename E>
// void tree_postorder(core::binary_node<K, E> *_node) {
//   if (!_node)
//     return;
//   tree_postorder(_node->left());
//   tree_postorder(_node->right());
//   std::cout << _node->value() << " ";
// }

template <typename T> std::list<T> quick_sort(std::list<int> coll) {
  return coll;
}

std::vector<int> twoSum(const std::vector<int> &array_, int target);

} // namespace blitz

/* template <typename T> class List {
public:
  List() : head(0), tail(0), _size(0) {}
  int size() { return _size; }
  void insert(Node<T> *data, int position) {
    auto _node = new Node<T>();
    _node->data = data->data;
    _node->next = nullptr;
    _node->prev = nullptr;
    // Check position value.
    if (position < 1) {
      std::cout << "Position should be greater than 1." << std::endl;
    } else if (position == 1) {
      _node->next = head;
      head = _node;
      ++_size;
    } else {
      auto t__node = head;
      for (int i = 1; i < position - 1; ++i) {
        if (t__node != nullptr) {
          t__node = t__node->next;
        }
      }
      if (t__node != nullptr) {
        _node->next = t__node->next;
        _node->prev = t__node;
        t__node->next = _node;
        if (_node->next != nullptr)
          _node->next->prev = _node;
        ++_size;
      } else {
        std::cout << "The previous _node is null." << std::endl;
      }
    }
  }
  List<T> &operator=(const List &_list) {
    if (&_list != this) {
      Node<T> *t__node = head;

      while (t__node->next) {
        head = head->next;
        delete t__node;
        t__node = head;
      }

      t__node = _list.head;
      while (t__node) {
        append(t__node);
        t__node = t__node->next;
      }
    }

    return *this;
  }

  void append(const Node<T>* _node ){

    if (NULL == head) {
        auto __node = new Node<T>(_node->data);
        head = __node;
    } else {
        auto current = head;
        while (current->next) {
            current = current->next;
        }
        auto __node = new Node<T>(_node->data);
        current->next = __node;
    }
}

  void traverse() {
    Node<T> *begin = head;
    while (begin != nullptr) {
      std::cout << begin->data << std::endl;
      begin = begin->next;
    }
  }

private:
  Node<T> *head;
  Node<T> *tail;
  int _size;
}; */

#endif