#ifndef BLITZ_INCLUDE_CORE_INTERNALS_HPP_
#define BLITZ_INCLUDE_CORE_INTERNALS_HPP_

namespace core {

template <typename _Tp> struct single_node {
  single_node(_Tp _data) : data(_data), next(nullptr) {}
  single_node<_Tp> *next;
  _Tp data;
};

template <typename _Tp> struct double_node {
  double_node(_Tp _data) : data(_data), next(nullptr), prev(nullptr) {}
  double_node<_Tp> *next;
  double_node<_Tp> *prev;
  _Tp data;
};


template <typename _Key, typename _Element> class binary_node {
public:
  binary_node(const _Key &_key, const _Element &_value)
      : m_key(_key), m_value(_value), left_child(nullptr), right_child(nullptr) {}

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

} // namespace core

#endif