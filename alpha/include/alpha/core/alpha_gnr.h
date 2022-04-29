#ifndef ALPHA_INCLUDE_ALPHA_CORE_ALPHA_GNR_H_
#define ALPHA_INCLUDE_ALPHA_CORE_ALPHA_GNR_H_

#include "alpha/alpha.h"

namespace alpha {

template <typename T> struct alpha_iterator_traits;

template <typename T> struct alpha_iterator_traits<T *> {
  typedef T::value_type value_type;
  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T *pointer;
  typedef T &reference;
};

template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
distance(Iterator begin, Iterator end) {
  return distance(begin, end,
                  typename std::iterator_traits<Iterator>::iterator_category());
}

template <typename RandomIterator>
typename std::iterator_traits<RandomIterator>::difference_type
distance(RandomIterator begin, RandomIterator end,
         std::random_access_iterator_tag) {

  return end - begin;
}

template <typename InIterator>
typename std::iterator_traits<InIterator>::difference_type
distance(InIterator begin, InIterator end, std::input_iterator_tag) {
  typename std::iterator_traits<InIterator>::difference_type diff = 0;
  while (begin != end) {
    ++begin;
    ++diff;
  }
  return diff;
}

template <typename Container>
class asso_insert_iterator : public std::iterator<std::output_iterator_tag,
                                       typename Container::value_type> {
public:
  explicit asso_insert_iterator(Container &_container) : container(_container) {}

  asso_insert_iterator<Container> &operator=(const typename Container::value_type &value) {
    container.insert(value);
    return *this;
  }

  asso_insert_iterator<Container> &operator*() { return *this; }

  asso_insert_iterator<Container> &operator++() { return *this; }

  asso_insert_iterator<Container> &operator++(int) { return *this; }

protected:
  Container &container;
};

template<typename Container>
inline asso_insert_iterator<Container> asso_inserter(Container& c) {
  return asso_insert_iterator<Container>(c);
}

template <typename T> struct AccumulatorTrait;

template <> struct AccumulatorTrait<int> { using Acct = int; };

template <> struct AccumulatorTrait<float> { using Acct = double; };

template <typename T> struct TypeSize {
  static std::size_t const value = sizeof(T);
};

template <typename C> struct ElementT { using Type = typename C::value_type; };

template <typename T> using ElementType = typename ElementT<T>::Type;

template <typename T> struct remove_refr { using type = T; };

template <typename T> struct remove_refr<T &> { using type = T; };

template <typename T> struct remove_refr<T &&> { using type = T; };

template <typename T> struct LTRPolicy {
  static void action(std::deque<T> &dq, const T &item, bool condition) {
    if (condition)
      dq.pop_back();
    dq.push_front(item);
  }

  static void remove(std::deque<T> &dq) { dq.pop_back(); }
};

template <typename T> class RTLPolicy {
public:
  static void action(std::deque<T> &dq, T item, bool condition) {
    if (condition)
      dq.pop_front();
    dq.push_back(item);
  }

  static void remove(std::deque<T> &dq) { dq.pop_front(); }
};

/* template<typename T>
class ascending {
  public:
    bool operator()(const T& val1, const T& val2){
      return va1 > val2;
    }
}; */

} //  namespace alpha

#endif
