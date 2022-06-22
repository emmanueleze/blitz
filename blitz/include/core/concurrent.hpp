#ifndef BLITZ_INCLUDE_CORE_CONCURRENT_HPP
#define BLITZ_INCLUDE_CORE_CONCURRENT_HPP

#include "blitz.hpp"
#include <atomic>
#include <condition_variable>
#include <deque>
#include <future>
#include <list>
#include <mutex>

std::atomic<bool> b(true);

namespace blitz {

namespace concurrent {

#ifndef __CPP11OM_SEMAPHORE_H__
#define __CPP11OM_SEMAPHORE_H__

#include <atomic>
#include <cassert>

#if defined(_WIN32)
//---------------------------------------------------------
// semaphore (Windows)
//---------------------------------------------------------

#include <windows.h>
#undef min
#undef max

class semaphore {
private:
  HANDLE m_hSema;

  semaphore(const semaphore &other) = delete;
  semaphore &operator=(const semaphore &other) = delete;

public:
  semaphore(int initial_count = 0) {
    assert(initial_count >= 0);
    m_hSema = Createsemaphore(NULL, initial_count, MAXLONG, NULL);
  }

  ~semaphore() { CloseHandle(m_hSema); }

  void wait() { WaitForSingleObject(m_hSema, INFINITE); }

  void signal(int count = 1) { Releasesemaphore(m_hSema, count, NULL); }
};

#elif defined(__MACH__)
//---------------------------------------------------------
// semaphore (Apple iOS and OSX)
// Can't use POSIX semaphores due to
// http://lists.apple.com/archives/darwin-kernel/2009/Apr/msg00010.html
//---------------------------------------------------------

#include <mach/mach.h>

class semaphore {
private:
  semaphore_t m_sema;

  semaphore(const semaphore &other) = delete;
  semaphore &operator=(const semaphore &other) = delete;

public:
  semaphore(int initial_count = 0) {
    assert(initial_count >= 0);
    semaphore_create(mach_task_self(), &m_sema, SYNC_POLICY_FIFO,
                     initial_count);
  }

  ~semaphore() { semaphore_destroy(mach_task_self(), m_sema); }

  void wait() { semaphore_wait(m_sema); }

  void signal() { semaphore_signal(m_sema); }

  void signal(int count) {
    while (count-- > 0) {
      semaphore_signal(m_sema);
    }
  }
};

#elif defined(__unix__)

/* semaphore - posix . linux
 */

#include <semaphore.h>

class semaphore {
private:
  sem_t m_sema;

  semaphore(const semaphore &other) = delete;
  semaphore &operator=(const semaphore &other) = delete;

public:
  semaphore(unsigned int initial_count = 0) {
    assert(initial_count >= 0);
    sem_init(&m_sema, 0, initial_count);
  }

  ~semaphore() { sem_destroy(&m_sema); }

  void wait() {
    int rc;
    do {
      rc = sem_wait(&m_sema);
    } while (rc == -1 && errno == EINTR);
  }

  void signal() { sem_post(&m_sema); }

  void signal(int count) {
    while (count-- > 0) {
      sem_post(&m_sema);
    }
  }
};

#else

#error Unsupported platform!

#endif

/* light_weight_semaphore
 */
class light_weight_semaphore {
private:
  std::atomic<int> m_count;
  semaphore m_sema;

  void wait_with_partial_spinning() {
    int oldCount;
    // Is there a better way to set the initial spin count?
    // If we lower it to 1000, testBenaphore becomes 15x slower on my Core
    // i7-5930K Windows PC, as threads start hitting the kernel semaphore.
    int spin = 10000;
    while (spin--) {
      oldCount = m_count.load(std::memory_order_relaxed);
      if ((oldCount > 0) &&
          m_count.compare_exchange_strong(oldCount, oldCount - 1,
                                          std::memory_order_acquire))
        return;
      std::atomic_signal_fence(
          std::memory_order_acquire); // Prevent the compiler from collapsing
                                      // the loop.
    }
    oldCount = m_count.fetch_sub(1, std::memory_order_acquire);
    if (oldCount <= 0) {
      m_sema.wait();
    }
  }

public:
  light_weight_semaphore(int initial_count = 0) : m_count(initial_count) {
    assert(initial_count >= 0);
  }

  bool tryWait() {
    int oldCount = m_count.load(std::memory_order_relaxed);
    return (oldCount > 0 &&
            m_count.compare_exchange_strong(oldCount, oldCount - 1,
                                            std::memory_order_acquire));
  }

  void wait() {
    if (!tryWait())
      wait_with_partial_spinning();
  }

  void signal(int count = 1) {
    int oldCount = m_count.fetch_add(count, std::memory_order_release);
    int toRelease = -oldCount < count ? -oldCount : count;
    if (toRelease > 0) {
      m_sema.signal(toRelease);
    }
  }
};

typedef light_weight_semaphore default_semaphore;

#endif // __CPP11OM_SEMAPHORE_H__

// ######################################################################

template <typename T> std::list<T> quick_sort(std::list<T> coll) {
  return coll;
}

class component_assembly {
public:
  component_assembly(const std::vector<std::string> &_data) : data(_data) {}
  void generate_components(){}
  void process_components(){}
private:
  std::mutex m_mutex;
  std::condition_variable m_cv;
  std::vector<std::string> data;
};

} // namespace concurrent

} // namespace blitz

#endif //  BLITZ_INCLUDE_BLITZ_CORE_CONCURRENT_HPP
