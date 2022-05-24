#ifndef BLITZ_INCLUDE_BLITZ_CORE_ALGORITHM_HPP
#define BLITZ_INCLUDE_BLITZ_CORE_ALGORITHM_HPP

#include "blitz/blitz.hpp"
#include "blitz/core/data.hpp"

#include <array>
#include <functional>
#include <numeric>
#include <random>

namespace blitz {

template <typename T> SinglyList<T> *reverse_list(SinglyList<T> *list) {
  if (!list)
    return nullptr;
}

template <typename T> SinglyList<T> *sort(SinglyList<T> *list) {
  if (!list)
    return nullptr;
}

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
  int pos = 0;
  for (pos; pos < size; ++pos) {
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
std::vector<int> twoSum(const std::vector<int> &array_, int target);

double random_generator(const double &min, const double &max);

template <typename T> std::list<T> quicksort(std::list<T> coll) {
  if (coll.empty()) {
    return coll;
  }
  std::list<T> result;
  result.splice(result.begin(), coll, coll.begin());
  auto pivot = *(coll.begin());
  auto divide_point = std::partition(coll.begin(), coll.end(),
                                     [&](const T &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), coll, coll.begin(), divide_point);
  auto new_lower(quicksort(std::move(lower_part)));
  auto new_upper(quicksort(std::move(coll)));

  result.splice(result.end(), new_upper);
  result.splice(result.begin(), new_lower);

  return result;
}

template <typename K, typename E> void tree_preorder(binary_node<K,E> *node) {
  if (!node)
    return;
  std::cout << node->value() << " ";
  tree_preorder(node->left());
  tree_preorder(node->right());
}

template <typename K, typename E> void tree_inorder(binary_node<K,E> *node) {
  if (!node)
    return;
  tree_inorder(node->left());
  std::cout << node->key() << " ";
  tree_inorder(node->right());
}

template <typename K, typename E> void tree_postorder(binary_node<K,E> *node) {
  if (!node)
    return;
  tree_postorder(node->left());
  tree_postorder(node->right());
  std::cout << node->value() << " ";
}

} // namespace blitz

/* template <typename T> class List {
public:
  List() : head(0), tail(0), _size(0) {}
  int size() { return _size; }
  void insert(Node<T> *data, int position) {
    auto node = new Node<T>();
    node->data = data->data;
    node->next = nullptr;
    node->prev = nullptr;
    // Check position value.
    if (position < 1) {
      std::cout << "Position should be greater than 1." << std::endl;
    } else if (position == 1) {
      node->next = head;
      head = node;
      ++_size;
    } else {
      auto t_node = head;
      for (int i = 1; i < position - 1; ++i) {
        if (t_node != nullptr) {
          t_node = t_node->next;
        }
      }
      if (t_node != nullptr) {
        node->next = t_node->next;
        node->prev = t_node;
        t_node->next = node;
        if (node->next != nullptr)
          node->next->prev = node;
        ++_size;
      } else {
        std::cout << "The previous node is null." << std::endl;
      }
    }
  }
  List<T> &operator=(const List &_list) {
    if (&_list != this) {
      Node<T> *t_node = head;

      while (t_node->next) {
        head = head->next;
        delete t_node;
        t_node = head;
      }

      t_node = _list.head;
      while (t_node) {
        append(t_node);
        t_node = t_node->next;
      }
    }

    return *this;
  }

  void append(const Node<T>* node ){

    if (NULL == head) {
        auto _node = new Node<T>(node->data);
        head = _node;
    } else {
        auto current = head;
        while (current->next) {
            current = current->next;
        }
        auto _node = new Node<T>(node->data);
        current->next = _node;
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