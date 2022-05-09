
#include "alpha/alpha.h"


std::vector<int> twoSum(const std::vector<int> &array_, int target) {
  std::vector<int> ivec;
  auto sz = (int)array_.size();
  auto i1 = 0;
  auto i2 = sz - 1;
  for (int i = 0; i < sz; ++i) {
    if (array_[i1] + array_[i2] == target) {
      ivec.insert(ivec.begin(), {i1, i2});
      return ivec;
    }
    if (array_[i1] + array_[i2] > target)
      --i2;
    if (array_[i1] + array_[i2] < target)
      ++i1;
  }
  return ivec;
}

alpha::GenericComponent::GenericComponent(const std::string &_name) : m_name(_name) {}

alpha::GenericComponent::GenericComponent(const GenericComponent &component) {
  this->m_name = component.m_name;
  this->_type = component._type;
}

std::string alpha::GenericComponent::name() const { return m_name; }

void alpha::GenericComponent::setName(std::string _name) { m_name = _name; }

alpha::CType alpha::GenericComponent::type() const { return _type; }

void alpha::GenericComponent::setType(alpha::CType tp) { _type = tp; }

alpha::ComponentAssembly::ComponentAssembly(const std::vector<std::string> &_list)
    : cmp_list(_list) {

  coll = new alpha::ItemQueue<alpha::GenericComponent>(10);
  processIndex = 0;
  done = false;
}

alpha::ComponentAssembly::~ComponentAssembly() { delete coll; }

void alpha::ComponentAssembly::next() {

  if (processIndex < (int)cmp_list.size())
    ++processIndex;
  if (processIndex == (int)cmp_list.size())
    done = true;
}

void alpha::ComponentAssembly::generateComponents() {

  while (!done) {
    {
      auto data = alpha::cfactory::create(cmp_list[processIndex]);
      std::lock_guard<std::mutex> _lock(g_mutex);
      coll->insert(data);
      next();
      _cnd.notify_one();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void alpha::ComponentAssembly::processComponents() {
  while (true) {
    std::unique_lock<std::mutex> _lock(g_mutex);
    _cnd.wait(_lock, [this] { return !coll->empty(); });
    const auto item = coll->remove();
    std::cout << "Processing " << item.name() << ".\n";
    _lock.unlock();
    if (done) {
      std::cout << "Finished processing components.\n";
      break;
    }
  }
}

alpha::Name::Name() {
  f_name = "";
  s_name = "";
}

alpha::Name::Name(const std::string &fname, const std::string &sname)
    : f_name(fname), s_name(sname) {}


void alpha::alert() {
  std::cout << "ALERT!" << std::endl;
}