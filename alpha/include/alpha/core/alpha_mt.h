#ifndef ALPHA_INCLUDE_ALPHA_CORE_ALPHA_MT_H_
#define ALPHA_INCLUDE_ALPHA_CORE_ALPHA_MT_H_

#include "alpha/alpha.h"
#include "alpha/core/arch.h"
#include <condition_variable>
#include <deque>
#include <future>
#include <mutex>

namespace alpha {

/* Item Queue
 * @brief A simple double ended queue. Elements are inserted
 * from the back and deleted from the front.
 * @tparam T Type of element.
 * @tparam Policy Policy type, defaults to RTLPolicy<T>. The policy determines
 * the flow of insertion and deletion.
 */
template <typename T, template <typename> class Policy = RTLPolicy>
class ItemQueue {
public:
  ItemQueue(uint maxsize = 8) : maxsize_(maxsize) {}

  ItemQueue(const ItemQueue<T, Policy> &iq2) {
    this->maxsize_ = iq2.maxsize_;
    this->deque_ = iq2.deque_;
  }

  void insert(const T &item) {
    std::lock_guard guard(mutex_);
    Policy<T>::action(deque_, item, deque_.size() == maxsize_);
  }

  std::vector<T> items() {
    std::lock_guard guard(mutex_);
    std::vector<T> hvec(deque_.begin(), deque_.end());
    return hvec;
  }

  T remove() {
    if (deque_.empty()) {
      throw std::logic_error("Cannot remove item from empty ItemQueue");
    }
    std::lock_guard guard(mutex_);
    auto _front = deque_.front();
    Policy<T>::remove(deque_);
    return _front;
  }

  uint max_size() const { return maxsize_; }

  size_t size() const {
    std::lock_guard<std::mutex> guard(mutex_);
    return deque_.size();
  }

  bool empty() { return deque_.empty(); }

private:
  uint maxsize_;
  std::deque<T> deque_;
  std::mutex mutex_;
};

class ComponentAssembly {
public:
  ComponentAssembly(const std::vector<std::string> &);
  ~ComponentAssembly();
  void generateComponents();
  void processComponents();

public:
  ComponentAssembly(const ComponentAssembly &) = delete;
  ComponentAssembly(ComponentAssembly &&) = delete;
  ComponentAssembly &operator=(const ComponentAssembly &) = delete;
  ComponentAssembly &operator=(ComponentAssembly &&) = delete;

private:
  void next();

private:
  ItemQueue<GenericComponent> *coll;
  std::mutex g_mutex;
  bool done;
  bool processed;
  std::condition_variable _cnd;
  int processIndex;
  std::vector<std::string> cmp_list;
};

} // namespace alpha

#endif //  ALPHA_INCLUDE_ALPHA_CORE_ALPHA_MT_H_
